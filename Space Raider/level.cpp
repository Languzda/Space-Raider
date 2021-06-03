#include "level.h"
#include <SFML/Graphics.hpp>

Level::Level()
{

}

Level::~Level() {
    player_shots_.erase(player_shots_.begin(), player_shots_.end());
    for (auto& actor : actors_) {
        delete actor;
    }
}

void Level::generate(const sf::RenderWindow* window, int lvl_nr) {
    if (lvl_nr == 1) {
        player_ = new Hero("spaceShip.png", 0.4, sf::IntRect(0, 0, 465, 380), window->getSize().x / 2, window->getSize().y - 150, false, 4);
        actors_.emplace_back(player_);
        Enemy* chicken;
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 6; i++) {
                chicken = new  Enemy("enemy.png", 0.1, sf::IntRect(0, 0, 600, 650), 100 * i + 25, window->getSize().y - (400 + 100 * j), false, 3, -75);
                enemies_.emplace_back(chicken);
                actors_.emplace_back(chicken);
            }
        }
        enemy_counter = 24;
        scoreboads_.emplace_back(new Score("ad_mono.ttf", sf::Vector2f(700, 50), sf::Color::White, 0));
        scoreboads_.emplace_back(new Score("ad_mono.ttf", sf::Vector2f(50, 50), sf::Color::Red, player_->getHP()));
    }
}

void Level::check_colision() {
    bool exit = false;

    //sprawdzenie kolizji przeciwników
    for (auto it = enemies_.begin(); it != enemies_.end();) {
        if ((*it)->getGlobalBounds().left <= 0) { for (auto& ell : enemies_) ell->change_velocity(Direction::Right); break; }
        if ((*it)->getGlobalBounds().left + (*it)->getGlobalBounds().width > 800) { for (auto& ell : enemies_) ell->change_velocity(Direction::Left); break; }
        if ((*it)->getGlobalBounds().top + (*it)->getGlobalBounds().height > 800) { delete* it; it = enemies_.erase(it); reload_actors(); break; }
        if ((*it)->getGlobalBounds().intersects(player_->getGlobalBounds())) { delete* it; it = enemies_.erase(it); player_->setHP(player_->getHP() - 1); scoreboads_[1]->update(player_->getHP()); reload_actors(); break; }
        it++;
    }

    for (auto it = power_ups_.begin(); it != power_ups_.end();) {
        if ((*it)->getGlobalBounds().top + (*it)->getGlobalBounds().height > 800) { delete* it; it = power_ups_.erase(it); reload_actors(); break; }
        if ((*it)->getGlobalBounds().intersects(player_->getGlobalBounds())) { (*it)->power_up(player_); delete* it; it = power_ups_.erase(it);   /*reload_actors();*/ break; }
        it++;
    }
    
    for (auto it = enemy_shots_.begin(); it != enemy_shots_.end();) {
        if ((*it)->getGlobalBounds().top + (*it)->getGlobalBounds().height >= 800) {
            delete* it;
            it = enemy_shots_.erase(it);
            reload_actors();
            break;
        }
        if (player_->getGlobalBounds().intersects((*it)->getGlobalBounds())) {
            player_->setHP(player_->getHP() - (*it)->getDmg());
            delete* it;
            it = enemy_shots_.erase(it);
            scoreboads_[1]->update(player_->getHP());
            reload_actors();
            break;
        }
        it++;
    }

    for (auto it = player_shots_.begin(); it != player_shots_.end();) { //check that bullet is out of window
        sf::FloatRect bullet_bounds = (*it)->getGlobalBounds();
        if (bullet_bounds.top <= 0) {
            delete* it;
            it = player_shots_.erase(it);
            reload_actors();
            break;
        }
        for (auto itt = enemies_.begin(); itt != enemies_.end(); itt++) { //check that enemy was hitten
            if ((*itt)->getGlobalBounds().intersects((*it)->getGlobalBounds())) {
                if ((*itt)->getHP() <= player_->getPower()) {
                    create_bonus(*itt);
                    delete* itt;

                    itt = enemies_.erase(itt);
                    delete* it;
                    it = player_shots_.erase(it);
                    reload_actors();
                    it++;
                    enemy_counter--;
                    scoreboads_[0]->update_score(10);
                    exit = true;
                    break;
                }
                else {
                    delete* it;
                    (*itt)->setHP((*itt)->getHP() - player_->getPower());
                    it = player_shots_.erase(it);
                    reload_actors();
                    exit = true;
                    break;
                }
            }
        }
        if (exit == true)break;
        it++;
    }
}

void Level::reload_actors() {
    actors_.erase(actors_.begin(), actors_.end());
    actors_.emplace_back(player_);
    for (auto& eb : enemy_shots_) {
        actors_.emplace_back(eb);
    }
    for (auto& e : enemies_) {
        actors_.emplace_back(e);
    }
    for (auto& b : player_shots_) {
        actors_.emplace_back(b);
    }
    //for (auto& b : power_ups_) {
    //    actors_.emplace_back();
    //}
    
} //erase actors vector, then emplace back all actors back

void Level::update_actors() {
    check_colision();

    for (auto& bullet : player_shots_) {
        bullet->rotate(1080 * 1 / 30);
        bullet->move_bullet();
    }
    for (auto& bullet : enemy_shots_) {
        bullet->move_bullet();
    }
    for (auto& enemy : enemies_) {
        enemy->move_e();
    }
    for (auto& bonus : power_ups_) {
        bonus->move_b();
    }
}   //update location & rotation of actors, its checking colision too

void Level::draw(sf::RenderWindow* window) {
    update_actors();
    for (auto& obj : actors_) {
        window->draw(*obj);
    }
    for (auto &score :scoreboads_)
    {
        window->draw(*score);
    }
    for (auto& b : power_ups_) {
        window->draw(*b);
    }
}

void Level::move_player(float x, float y) {
    if (x > 0)player_->change_direction_texture(Direction::Right);
    if (x < 0)player_->change_direction_texture(Direction::Left);
    if (x == 0)player_->change_direction_texture(Direction::Mid);
    player_->move(x, y);
}

void Level::create_player_bullet() {
    std::vector<PlayerProjectile*> buff = player_->getBullet();
    for (auto it = buff.begin(); it != buff.end();it++) {
        player_shots_.emplace_back((*it));
        actors_.emplace_back((*it));  
    }
    buff.erase(buff.begin(), buff.end());
}

void Level::create_enemy_bullet() {
    if (!enemies_.empty()) {
        int random = rand() % enemies_.size();
        enemy_shots_.emplace_back(new EnemyProjectile("ball.png", 1, sf::IntRect(0, 0, 25, 25),
            enemies_[random]->getPosition().x + enemies_[random]->getGlobalBounds().width / 2, enemies_[random]->getPosition().y, false, 0, 150, 1, 1));
        actors_.emplace_back(enemy_shots_[enemy_shots_.size() - 1]);
        reload_actors();
    }
}

void Level::attack_player() { 
    if (!enemies_.empty()) {
        int random = rand() % enemies_.size();
        enemies_[random]->change_velocity(Direction::Mid);
    }
}

void Level::create_bonus(Enemy* &enemy) {
    if (rand() % 5 == 0) {
        PowerUpMultishot* buff = new PowerUpMultishot("ball_bonus.png", 1, sf::IntRect(0, 0, 25, 25), enemy->getPosition().x, enemy->getPosition().y, false);
        power_ups_.emplace_back(buff);
        //actors_.emplace_back(buff);
    }
}
