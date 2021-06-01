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

void Level::generate(const sf::RenderWindow* window) {
    player_ = new Hero("spaceShip.png", 0.4, sf::IntRect(0, 0, 465, 380), window->getSize().x / 2, window->getSize().y - 150, false, 2);
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
    scoreboad_ = new Score("ad_mono.ttf");
}

void Level::check_colision() {
    bool exit = false;
    for (auto& el : enemies_) {
        if (el->getGlobalBounds().left <= 0) { for (auto& ell : enemies_) ell->change_velocity(Direction::Right); break; }
        if (el->getGlobalBounds().left + el->getGlobalBounds().width > 800) { for (auto& ell : enemies_) ell->change_velocity(Direction::Left); break; }
    }

    for (auto it = player_shots_.begin(); it != player_shots_.end();) { //check that bullet is out of window
        sf::FloatRect bullet_bounds = (*it)->getGlobalBounds();
        if (bullet_bounds.top <= 0) {
            it = player_shots_.erase(it);
            reload_actors();
            break;
        }
        for (auto itt = enemies_.begin(); itt != enemies_.end(); itt++) { //check that enemy was hitten
            if ((*itt)->getGlobalBounds().intersects((*it)->getGlobalBounds())) {
                if ((*itt)->getHP() <= player_->getPower()) {
                    itt = enemies_.erase(itt);
                    it = player_shots_.erase(it);
                    reload_actors();
                    it++;
                    enemy_counter--;
                    scoreboad_->update_score(10);
                    exit = true;
                    break;
                }
                else {
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
    for (auto& e : enemies_) {
        actors_.emplace_back(e);
    }
    for (auto& b : player_shots_) {
        actors_.emplace_back(b);
    }
} //erase actors vector, then emplace back all actors back

void Level::update_actors() {
    check_colision();
    for (auto& bullet : player_shots_) {
        bullet->rotate(1080 * 1 / 30);
        bullet->move_bullet();
    }
    for (auto& enemy : enemies_) {
        enemy->move_e();
    }
}   //update location & rotation of actors, its checking colision too

void Level::draw(sf::RenderWindow* window) {
    update_actors();
    for (auto& obj : actors_) {
        window->draw(*obj);
    }
    window -> draw(*scoreboad_);
}

void Level::move_player(float x, float y) {
    if (x > 0)player_->change_direction_texture(Direction::Right);
    if (x < 0)player_->change_direction_texture(Direction::Left);
    if (x == 0)player_->change_direction_texture(Direction::None);
    player_->move(x, y);
}

void Level::create_player_bullet() {
    PlayerProjectile* bullet = new PlayerProjectile("ball.png", 1, sf::IntRect(0, 0, 25, 25),
        player_->getPosition().x + player_->getGlobalBounds().width / 2, player_->getPosition().y, false, 0, -150,player_->getPower());
    player_shots_.emplace_back(bullet);
    actors_.emplace_back(bullet);
}

void Level::create_enemy_bullet() {

}
