#pragma once
#include "character.h";
#include "projectile.h"

class Hero : public Character //klasa postaci sterowanej przez gracza
{
public:
    Hero(std::string texture_path, float scale, sf::IntRect rect,
        int x, int y, bool is_Repeated, int hp);
    ~Hero();
    void setMultishot();
    void dmgUP();
    void set_bounce();
    int getPower();
    std::vector<PlayerProjectile*> getBullet();
    void set_velocity(const float& x);
    float get_velocity();
    void exist(bool destroy);
    bool exist();
private:
    int power_ = 2;
    bool bounce = false;
    float velocity_x_;
    bool existing_flag = true;

};