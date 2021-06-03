#include "player.h"

Hero::Hero(std::string texture_path, float scale, sf::IntRect rect,
    int x, int y, bool is_Repeated = false, int hp = 0) : Character(texture_path, scale, rect, x, y, is_Repeated, hp) {
    this->setTextureRect(sf::IntRect(155, 0, 155, 380));
    for (int i = 1; i < 4; i++) animationFrame_.emplace_back(sf::IntRect(155 * (i - 1), 0, 155, 380));
}

Hero::~Hero() {}

void Hero::dmgUP() { this->power_++; }

int Hero::getPower() { return this->power_; }

void Hero::set_bounce() { this->bounce = true; }

void Hero::setMultishot() {
    this->multishot_++;
}

std::vector<PlayerProjectile*> Hero::getBullet() {
    std::vector<PlayerProjectile*> buff_vector;
    int znak;
    for (int i = 0; i < multishot_; i++) {
        if (i % 2 == 0) { znak = -1; } else{  znak = 1;}
        buff_vector.emplace_back(new PlayerProjectile("ball.png", 1, sf::IntRect(0, 0, 25, 25),
            this->getPosition().x + this->getGlobalBounds().width / 2, this->getPosition().y,
            false,(i*40)%200*znak, -350, this->power_, true));
    }

    return buff_vector;
}