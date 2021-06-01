#include "player.h"

Hero::Hero(std::string texture_path, float scale, sf::IntRect rect,
    int x, int y, bool is_Repeated = false, int hp = 0) : Character(texture_path, scale, rect, x, y, is_Repeated, hp) {
    this->setTextureRect(sf::IntRect(0, 0, 155, 380));
    for (int i = 1; i < 4; i++) animationFrame_.emplace_back(sf::IntRect(155 * (i - 1), 0, 155, 380));
}

Hero::~Hero() {}

void Hero::dmgUP() { this->power_++; }

int Hero::getPower() { return this->power_; }