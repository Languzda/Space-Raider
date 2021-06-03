#include "character.h"
#include <iostream>

Actor::Actor(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated = false) {
    if (texture_.loadFromFile(texture_path)) {
        this->setTexture(texture_);
        this->setScale(scale, scale);
        this->setTextureRect(rect);
        texture_.setRepeated(is_Repeated);
        this->setPosition(x, y);
    }
    else {
        std::cout << "blad tekstury" << std::endl;
    }
}


Character::Character(std::string texture_path, float scale, sf::IntRect rect,
    int x, int y, bool is_Repeated = false, int hp = 0) :
    Actor(texture_path, scale, rect, x, y, is_Repeated), health_points_(hp) {
}


void Character::setHP(int hp) { this->health_points_ = hp; }

int Character::getHP() { return health_points_; }

void Character::change_direction_texture(Direction direction) {
    if (direction == Direction::Right) this->setTextureRect(animationFrame_[2]);
    if (direction == Direction::Mid) this->setTextureRect(animationFrame_[1]);
    if (direction == Direction::Left) this->setTextureRect(animationFrame_[0]);
}

Enemy::Enemy(std::string texture_path, float scale, sf::IntRect rect,
    int x, int y, bool is_Repeated = false, int hp = 0, int veX = -25) :
    Character(texture_path, scale, rect, x, y, is_Repeated, hp), velocity_x(veX) {}

void Enemy::move_e() {
    this->move(velocity_x *( 1.f / 30), velocity_y*(1.f/30));
}

void Enemy::change_velocity(const Direction direction) {
    if (direction == Direction::Left) velocity_x = -std::abs(velocity_x);
    if (direction == Direction::Right) velocity_x = std::abs(velocity_x);
    if (direction == Direction::Mid) { /*velocity_x = 0;*/ velocity_y = 75; }
}

