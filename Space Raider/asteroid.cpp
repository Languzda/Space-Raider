#include "asteroid.h"

Asteroid::Asteroid(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated) :
    Actor(texture_path, scale, rect, x, y, is_Repeated)
{
    this->velocity_x_ = rand() % 100 + 20;
    if (rand() % 2 == 0) this->velocity_x_ = -velocity_x_;
    this->velocity_y_ = rand() % 170 + 100;
}

bool Asteroid::remake() {
    if (this->life_span_ == 1) return true;
    else {
        this->life_span_--;
        this->velocity_x_ = rand() % 100 + 25;
        if (rand() % 2 == 0) this->velocity_x_ = -velocity_x_;
        this->velocity_y_ = rand() % 170 + 100;
        this->setPosition(rand() % 700 + 20, 20);
        return false;
    }
}

void Asteroid::moveA() {
    this->move(velocity_x_ * 1.f / 30, velocity_y_ * 1.f / 30);
    this->rotate(20 * 1.f / 30);
}

Asteroid::~Asteroid()
{
}
