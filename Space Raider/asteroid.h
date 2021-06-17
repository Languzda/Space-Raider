#pragma once
#include "character.h"

class Asteroid : public Actor
{
public:
    Asteroid(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated);
    ~Asteroid();
    bool remake();
    void move_asteroid();

private:
    int life_span_ = 3;
    int velocity_x_ = 50;
    int velocity_y_ = 50;
};


