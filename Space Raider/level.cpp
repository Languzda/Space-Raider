#include "level.h"
#include <SFML/Graphics.hpp>

Level::Level()
{

}

Level::~Level() {
    //player_shots_.erase(player_shots_.begin(), player_shots_.end());
    for (auto& actor : actors_) {
        delete actor;
    }
}

void Level::generate(const sf::RenderWindow* window, int lvl_nr) {
    window_size_ = sf::Vector2f(window->getSize().x,window->getSize().y);
    
    scene_texture.loadFromFile("Textures/PlainCosmos2.png");
    for (int i = 0; i < 2; i++) {
        scene_plain.emplace_back(sf::Sprite(scene_texture));
        scene_plain[scene_plain.size() - 1].setPosition(0, -798 * i);
    }

    if (lvl_nr == 1) {
        player_ = new Hero("Textures/spaceShip.png", 0.4, sf::IntRect(0, 0, 465, 380), window->getSize().x / 2, window->getSize().y - 150, false, 4);
        actors_.emplace_back(player_);
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 6; i++) {
                enemies_.emplace_back(new  Enemy("Textures/enemy1.png", 1, sf::IntRect(0, 0, 216, 63), 100 * i + 25, window->getSize().y - (400 + 100 * j), false, 3, -75));
                actors_.emplace_back(enemies_[enemies_.size()-1]);
            }
        }
  
        scoreboads_.emplace_back(new Score("ad_mono.ttf", sf::Vector2f(700, 50), sf::Color::White, 0));
        scoreboads_.emplace_back(new Score("ad_mono.ttf", sf::Vector2f(50, 50), sf::Color::Red, player_->getHP()));
    }
    if (lvl_nr == 2) {
        clear_actors();

        for (int i = 0; i < 10; i++) {
            asteroids_.emplace_back(new Asteroid("Textures/asteroid.png", 0.2, sf::IntRect(0, 0, 320, 320), rand() % 700, 20, false));
            actors_.emplace_back(asteroids_[asteroids_.size() - 1]);
        }
    }
    if (lvl_nr == 3) {
        Enemy* chicken;
        clear_actors();
        chicken = new  Enemy("Textures/enemy.png", 0.5, sf::IntRect(0, 0, 600, 1300), window->getSize().x / 2, 100, false, 20, -75,4);
        enemies_.emplace_back(chicken);
        actors_.emplace_back(chicken);

    }
}

void Level::clear_actors() {
    enemy_shots_.erase(enemy_shots_.begin(), enemy_shots_.end());
    player_shots_.erase(player_shots_.begin(), player_shots_.end());

     /* for (auto it = enemy_shots_.begin(); it != enemy_shots_.end(); ) { delete* it; it = enemy_shots_.erase(it); it++; }
    for (auto it = player_shots_.begin(); it != player_shots_.end(); ) { delete* it; it = player_shots_.erase(it); it++; }*/
    /*for (auto it = actors_.begin() + 1; it != actors_.end(); ) {
        delete* it;
        it = actors_.erase(it);
        it++;
    }*/
    
     //for (auto& b : player_shots_) { delete b; }
     //enemy_shots_.erase(enemy_shots_.begin(), enemy_shots_.end());
     //player_shots_.erase(player_shots_.begin(), player_shots_.end());
    reload_actors();
}

void Level::check_colision() {
    bool exit = false;

    if (player_->getGlobalBounds().left < 0) player_->setPosition(window_size_.x - player_->getGlobalBounds().width, player_->getPosition().y);
    if (player_->getGlobalBounds().left + player_->getGlobalBounds().width > window_size_.x) player_->setPosition(player_->getGlobalBounds().width, player_->getPosition().y);

    //sprawdzenie kolizji przeciwników
    for (auto it = enemies_.begin(); it != enemies_.end();) {
        if ((*it)->getGlobalBounds().left <= 0) { for (auto& ell : enemies_) { ell->change_velocity(Direction::Right); ell->change_direction_texture(Direction::Right); } break; }
        if ((*it)->getGlobalBounds().left + (*it)->getGlobalBounds().width > 800) 
        { for (auto& ell : enemies_) { ell->change_velocity(Direction::Left); ell->change_direction_texture(Direction::Left);} break; }
        if ((*it)->getGlobalBounds().top + (*it)->getGlobalBounds().height > 800) { delete* it; it = enemies_.erase(it); reload_actors(); break; }
        if (player_->exist()) { if ((*it)->getGlobalBounds().intersects(player_->getGlobalBounds())) { delete* it; it = enemies_.erase(it); player_->setHP(player_->getHP() - 1);  reload_actors(); break; } }
        it++;
    }

    for (auto it = asteroids_.begin(); it != asteroids_.end(); it++) {
        if (((*it)->getGlobalBounds().left <= 0) or ((*it)->getGlobalBounds().left + (*it)->getGlobalBounds().width > 800) or ((*it)->getGlobalBounds().top + (*it)->getGlobalBounds().height > 800)) {
            if ((*it)->remake()) {
                delete* it;
                it = asteroids_.erase(it);
                reload_actors();
                break;
            }
        }
        if (player_->exist()) {
            if ((*it)->getGlobalBounds().intersects(player_->getGlobalBounds())) { delete* it; it = asteroids_.erase(it); player_->setHP(player_->getHP() - 1);  reload_actors(); break; }
        }
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
        if (player_->exist()) {
            if (player_->getGlobalBounds().intersects((*it)->getGlobalBounds())) {
                player_->setHP(player_->getHP() - (*it)->getDmg());
                delete* it;
                it = enemy_shots_.erase(it);
                scoreboads_[1]->update(player_->getHP());
                reload_actors();
                break;
            }
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
                    //enemy_counter--;
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
        for (auto itt = asteroids_.begin(); itt != asteroids_.end(); itt++) { //check that enemy was hitten
            if ((*itt)->getGlobalBounds().intersects((*it)->getGlobalBounds())) {
                delete* it;
                it = player_shots_.erase(it);
                reload_actors();
                exit = true;
                break;
            }
        }
        if (exit == true)break;
        it++;
    }
}

void Level::reload_actors() {
    actors_.erase(actors_.begin(), actors_.end());
    if (player_ ->exist()) {
        actors_.emplace_back(player_);
    }
    for (auto& b : player_shots_) {
        actors_.emplace_back(b);
    }
    for (auto& eb : enemy_shots_) {
        actors_.emplace_back(eb);
    }
    for (auto& e : enemies_) {
        actors_.emplace_back(e);
    }
 
    for (auto& a : asteroids_) {
        actors_.emplace_back(a);
    }
    
} //erase actors vector, then emplace back all actors back

void Level::update_actors() {
    check_colision();
    scoreboads_[1]->update(player_->getHP());

    for (auto& actor : actors_) {
        actor->moveA();
    }
    
    for (auto& bonus : power_ups_) {
        bonus->moveA();
    }

    for (auto& plain : scene_plain) {
        if (plain.getGlobalBounds().top >= window_size_.y-2) plain.setPosition(0, -window_size_.y);
        plain.move(0, 90 * 1.f / 30);
    }

    if (player_->getHP() <= 0 && player_->exist()==true) {
        Messege = new Score("ad_mono.ttf", sf::Vector2f(window_size_.x/2-100, window_size_.y/2), sf::Color::White, "\tYou Lose\npress escape to quit");
        Messege->setPosition(window_size_.x / 2 - Messege->getGlobalBounds().width, window_size_.y / 2);
        Messege->setScale(2, 2);
        player_->exist(false);
        reload_actors();
    }
}   //update location & rotation of actors, its checking colision too

int Level::draw(sf::RenderWindow* window) {
    update_actors();
    
    for (auto& obj : scene_plain) {
        window->draw(obj);
    }
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
    //if (player_->getHP() <= 0) {
    //    return -1;
    //}

    if (!player_->exist()) {
        window->draw(*Messege);
    }

    if (enemies_.size() > asteroids_.size())
        return enemies_.size();
    else {
        return asteroids_.size();
    }
}

void Level::move_player(float x, float y) {
    player_->set_velocity(x);
    if (0 < x)    player_->change_direction_texture(Direction::Right);
    if (0 > x)    player_->change_direction_texture(Direction::Left);
    if (0 == x)   player_->change_direction_texture(Direction::Mid);
}

void Level::create_player_bullet() {
    if (player_->exist()) {
        std::vector<PlayerProjectile*> buff = player_->getBullet();
        for (auto it = buff.begin(); it != buff.end(); it++) {
            player_shots_.emplace_back((*it));
            actors_.emplace_back((*it));
        }
        buff.erase(buff.begin(), buff.end());
    }
}

void Level::create_enemy_bullet() {
    if (!enemies_.empty()) {
        int random = rand() % enemies_.size();
        std::vector<EnemyProjectile*> buff = enemies_[random]->getBullet();
        for (auto it = buff.begin(); it != buff.end(); it++) {
            enemy_shots_.emplace_back((*it));
            actors_.emplace_back((*it));
        }
        buff.erase(buff.begin(), buff.end());
        reload_actors();
    }
}

void Level::attack_player() { 
    if (player_->exist()) {
        if (enemies_.size() > 1) {
            int random = rand() % enemies_.size();
            enemies_[random]->change_velocity(Direction::Mid);
        }
    }
}

void Level::create_bonus(Enemy* &enemy) {
    if (player_->exist()) {
        if (rand() % 5 == 0) {
            int random = rand() % 3;
            if (random % 3 == 0) {
                PowerUp* buff = new PowerUpMultishot("Textures/MultiShot.png", 0.05, sf::IntRect(0, 0, 530, 570), enemy->getPosition().x, enemy->getPosition().y, false);
                power_ups_.emplace_back(buff);
            }
            else if (random % 3 == 1) {
                PowerUp* buff = new PowerUpDmg("Textures/DmgUp.png", 0.05, sf::IntRect(0, 0, 530, 570), enemy->getPosition().x, enemy->getPosition().y, false);
                power_ups_.emplace_back(buff);
            }
            else {
                PowerUp* buff = new PowerUpHealth("Textures/BonusLife.png", 0.04, sf::IntRect(0, 0, 920, 901), enemy->getPosition().x, enemy->getPosition().y, false);
                power_ups_.emplace_back(buff);
            }
        }
    }
}
