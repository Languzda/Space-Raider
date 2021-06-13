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

Asteroid::Asteroid(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated) :
    Actor(texture_path, scale, rect, x, y, is_Repeated)
{
    this->velocity_x_ = rand() % 170 + 100;
    if (rand() % 2 == 0) this->velocity_x_ = -velocity_x_;
    this->velocity_y_ = rand() % 170 + 100;
}

bool Asteroid::remake() {
    if (this->life_span_ == 1) return true;
    else {
        this->life_span_--;
        this->velocity_x_ = rand() % 170 + 100;
        if (rand() % 2 == 0) this->velocity_x_ = -velocity_x_;
        this->velocity_y_ = rand() % 170 + 100;
        this->setPosition(rand() % 700 + 20, 20);
        return false;
    }
}

void Asteroid::move_asteroid(const sf::Time& elapsed) {
    this->move(this->velocity_x_ * elapsed.asSeconds(), this->velocity_y_ * elapsed.asSeconds());
}

Asteroid::~Asteroid()
{
}