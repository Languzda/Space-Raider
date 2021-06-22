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
    for (auto& score : scoreboads_) {
        delete score;
    }
}

void Level::generate(const sf::RenderWindow* window, int lvl_nr) {
    window_size_ = sf::Vector2f(window->getSize().x,window->getSize().y);
    
    scene_texture.loadFromFile("Textures/PlainCosmos2.png");
    for (int i = 0; i < 2; i++) {
        scene_plain.emplace_back(sf::Sprite(scene_texture));
        scene_plain[scene_plain.size() - 1].setPosition(0, -(window_size_.y * i));
    }

    if (lvl_nr == 1) {
        player_ = new Hero("Textures/spaceShip.png", 0.4, sf::IntRect(0, 0, 465, 380), window->getSize().x / 2, window->getSize().y - 150, false, 5);
        actors_.emplace_back(player_);
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 6; i++) {
                enemies_.emplace_back(new  Enemy("Textures/enemy1.png", 1, sf::IntRect(0, 0, 216, 63), 100 * i + 25, window->getSize().y - (400 + 100 * j), false, 3, -75));
                actors_.emplace_back(enemies_[enemies_.size()-1]);
            }
        }
  
        scoreboads_.emplace_back(new Score("ad_mono.ttf", sf::Vector2f(700, 50), sf::Color::White, 0000));
        scoreboads_.emplace_back(new Score("ad_mono.ttf", sf::Vector2f(50, 50), sf::Color::Red, player_->getHP()));
    }
    if (lvl_nr == 2) {
        clear_actors();
        scoreboads_[0]->update_score(100);
        for (int i = 0; i < 10; i++) {
            asteroids_.emplace_back(new Asteroid("Textures/asteroid.png", 0.2, sf::IntRect(0, 0, 320, 320), rand() % 700, -50, false));
            actors_.emplace_back(asteroids_[asteroids_.size() - 1]);
        }
    }
    if (lvl_nr == 3) {
        clear_actors();
        scoreboads_[0]->update_score(100);
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 7; i++) {
                enemies_.emplace_back(new  Enemy("Textures/enemy1.png", 1, sf::IntRect(0, 0, 216, 63), 100 * i + 25, window->getSize().y - (400 + 100 * j), false, 4, -75));
                actors_.emplace_back(enemies_[enemies_.size() - 1]);
            }
        }
    }
    if (lvl_nr == 4) {
        clear_actors();
        scoreboads_[0]->update_score(100);
        for (int i = 0; i < 13; i++) {
            asteroids_.emplace_back(new Asteroid("Textures/asteroid.png", 0.2, sf::IntRect(0, 0, 320, 320), rand() % 700, -50, false));
            actors_.emplace_back(asteroids_[asteroids_.size() - 1]);
        }
    }
    if (lvl_nr == 5) {
        clear_actors();
        scoreboads_[0]->update_score(100);
        for (int j = 0; j < 5; j++) {
            for (int i = 0; i < 6; i++) {
                enemies_.emplace_back(new  Enemy("Textures/enemy1.png", 1, sf::IntRect(0, 0, 216, 63), 100 * i + 25, window->getSize().y - (400 + 75 * j), false, 5, -65));
                actors_.emplace_back(enemies_[enemies_.size() - 1]);
            }
        }
    }
    if (lvl_nr == 6) {
        clear_actors();
        scoreboads_[0]->update_score(100);
        for (int j = 0; j < 3; j++) {
            for (int i = 0; i < 5; i++) {
                enemies_.emplace_back(new  Enemy("Textures/enemy1.png", 1, sf::IntRect(0, 0, 216, 63), 100 * i + 25, window->getSize().y - (400 + 100 * j), false, 8, -115));
                actors_.emplace_back(enemies_[enemies_.size() - 1]);
            }
        }
    }
    if (lvl_nr == 7) {
        clear_actors();
        scoreboads_[0]->update_score(100);
        enemies_.emplace_back(new  Enemy("Textures/enemy.png", 0.4, sf::IntRect(0, 0, 590, 1180), window->getSize().x / 2, 100, false, 100, -90, 4));
        actors_.emplace_back(enemies_[enemies_.size()-1]);

    }
    if (lvl_nr == 8) {
        clear_actors();
        scoreboads_[0]->update_score(300);
        Messege  = new Score("ad_mono.ttf", sf::Vector2f(window_size_.x / 2 - 100, window_size_.y / 2), sf::Color::White, "\tVictory\npress escape to quit");
        victory_flag_ = true;
        Messege->setScale(1.5, 1.5);
        Messege->setPosition(window_size_.x / 2 - Messege->getGlobalBounds().width / 2, window_size_.y / 2 - Messege->getGlobalBounds().height);
    }
}

void Level::clear_actors() {
    for (auto it = enemy_shots_.begin(); it != enemy_shots_.end(); ) { delete* it; it++; }
    enemy_shots_.erase(enemy_shots_.begin(), enemy_shots_.end());

    /*for (auto it = player_shots_.begin(); it != player_shots_.end(); ) { delete* it; it++; }
    player_shots_.erase(player_shots_.begin(), player_shots_.end());*/

    reload_actors();
}

void Level::check_colision() {
    bool exit = false;

    if (player_->getGlobalBounds().left < 0) player_->setPosition(window_size_.x - player_->getGlobalBounds().width, player_->getPosition().y);
    if (player_->getGlobalBounds().left + player_->getGlobalBounds().width > window_size_.x) player_->setPosition(player_->getGlobalBounds().width, player_->getPosition().y);

    //sprawdzenie kolizji przeciwników
    for (auto it = enemies_.begin(); it != enemies_.end();) {
        if ((*it)->getGlobalBounds().left <= 0) {
            for (auto& ell : enemies_) {
                ell->change_velocity(Direction::Right); 
                ell->change_direction_texture(Direction::Right); 
            }
            break; 
        }
        if ((*it)->getGlobalBounds().left + (*it)->getGlobalBounds().width > 800) 
        { 
            for (auto& ell : enemies_) { 
                ell->change_velocity(Direction::Left); 
                ell->change_direction_texture(Direction::Left);
            } 
            break; 
        }
        if ((*it)->getGlobalBounds().top + (*it)->getGlobalBounds().height > 800) { 
            delete* it; 
            it = enemies_.erase(it); 
            reload_actors(); 
            break; 
        }
        if (player_->exist()) {
            if ((*it)->getGlobalBounds().intersects(player_->getGlobalBounds())) {
                delete* it;
                it = enemies_.erase(it); 
                player_->setHP(player_->getHP() - 1);  
                reload_actors(); 
                break; 
            } 
        }
        it++;
    }
    //sprawdzanie kolizji asteroid
    for (auto it = asteroids_.begin(); it != asteroids_.end(); it++) {
        if (((*it)->getGlobalBounds().left <= -(*it)->getGlobalBounds().width+2) or ((*it)->getGlobalBounds().left> window_size_.x) or ((*it)->getGlobalBounds().top > window_size_.y)) {
            if ((*it)->remake()) {
                delete* it;
                it = asteroids_.erase(it);
                reload_actors();
                break;
            }
        }
        if (player_->exist()) { //jesl gracz istnieje sprawdŸ kolizje z graczem
            if ((*it)->getGlobalBounds().intersects(player_->getGlobalBounds())) { 
                delete* it; 
                it = asteroids_.erase(it); 
                player_->setHP(player_->getHP() - 1); 
                reload_actors(); 
                break; 
            }
        }
    }
    //sprawdzenie kolizji powerUpów
    for (auto it = power_ups_.begin(); it != power_ups_.end();) {
        if ((*it)->getGlobalBounds().top + (*it)->getGlobalBounds().height > 800) { 
            delete* it; 
            it = power_ups_.erase(it); 
            reload_actors(); 
            break; 
        }
        if ((*it)->getGlobalBounds().intersects(player_->getGlobalBounds())) { 
            (*it)->power_up(player_); 
            delete* it; 
            it = power_ups_.erase(it);   
            reload_actors();
            break; 
        }
        it++;
    }
    //sprawdzenie kolizji pocisków przeciwników
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
    //sprawdzanie kolizji pocisków gracza
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
    for (auto& b : player_shots_) {
        actors_.emplace_back(b);
    }
    if (player_ ->exist()) {
        actors_.emplace_back(player_);
    }
    for (auto& eb : enemy_shots_) {
        actors_.emplace_back(eb);
    }
    for (auto& powerUp : power_ups_) {
        actors_.emplace_back(powerUp);
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
    for (auto& plain : scene_plain) {
        if (plain.getGlobalBounds().top >= window_size_.y) plain.setPosition(0, -window_size_.y);
        plain.move(0, 90 * 1.f / 30);
    }

    if (player_->getHP() <= 0 && player_->exist()==true) {
        Messege = new Score("ad_mono.ttf", sf::Vector2f(window_size_.x/2-100, window_size_.y/2), sf::Color::White, "\tYou Lose\npress escape to quit");
        Messege->setScale(1.5, 1.5);
        Messege->setPosition(window_size_.x / 2 - Messege->getGlobalBounds().width/2, window_size_.y / 2- Messege->getGlobalBounds().height);  
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

    if (!player_->exist() or victory_flag_) {
        window->draw(*Messege);
    }
    if (victory_flag_) return 1;
    else {
        if (enemies_.size() > asteroids_.size())
            return enemies_.size();
        else {
            return asteroids_.size();
        }
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
        player_->getBullet(player_shots_);
        reload_actors();
    }
}

void Level::create_enemy_bullet() {
    if (!enemies_.empty()) {
        int random = rand() % enemies_.size();
        enemies_[random]->getBullet(enemy_shots_);
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
        if (rand() % 10 == 0) {
            int random = rand() % 3;
            if (random % 3 == 0) {
                power_ups_.emplace_back(new PowerUpMultishot("Textures/MultiShot.png", 0.9, sf::IntRect(0, 0, 50, 50), enemy->getPosition().x-enemy->getGlobalBounds().width/2, enemy->getPosition().y, false));
            }
            else if (random % 3 == 1) {
                power_ups_.emplace_back(new PowerUpDmg("Textures/DmgUp.png", 1, sf::IntRect(0, 0, 40, 25), enemy->getPosition().x - enemy->getGlobalBounds().width / 2, enemy->getPosition().y, false));
            }
            else {
                power_ups_.emplace_back(new PowerUpHealth("Textures/BonusLife.png", 0.04, sf::IntRect(0, 0, 920, 901), enemy->getPosition().x - enemy->getGlobalBounds().width / 2, enemy->getPosition().y, false));
            }
            reload_actors();
        }
    }
}
