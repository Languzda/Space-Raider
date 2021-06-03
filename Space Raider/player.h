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
private:
    int multishot_ = 1;
    int power_ = 2;
    bool bounce = false;
    //PlayerProjectile bullet;

};