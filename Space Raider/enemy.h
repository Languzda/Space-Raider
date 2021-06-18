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
    void moveA(); //poruszanie siê obiekty
    void change_velocity(const Direction direction); //zmienia kierunku poruszanie siê obiektu
    std::vector<EnemyProjectile*> getBullet(); //towrzenie pocisków
private:
    int velocity_x; //wektor poruszania siê(OX)
    int velocity_y = 0;//wektor poruszania siê (OY)
};