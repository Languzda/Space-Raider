#pragma once

#include "character.h"
#include "projectile.h"

class Enemy : public Character //klasa przeciwnika
{
public:
    Enemy(std::string texture_path, float scale, sf::IntRect rect,
        int x, int y, bool is_Repeated, int hp, int veX);
    Enemy(std::string texture_path, float scale, sf::IntRect rect,
        int x, int y, bool is_Repeated, int hp, int veX,int multishot);
    ~Enemy() {};
    void move_e();
    void change_velocity(const Direction direction);
    std::vector<EnemyProjectile*> getBullet();
private:
    int velocity_x;
    int velocity_y = 0;
};