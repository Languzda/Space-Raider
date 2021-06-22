#pragma once
#include "character.h"

class Projectile : public Actor
{
public:
    Projectile(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated, int veX, int veY, int dmg, bool bounce);
	~Projectile();
    void moveA(); //porsuzanie si� obiektu
    int getDmg(); //geter ilo�ci obra�e� pocisku
    bool is_bouncy();
protected:
    bool bounce_;
    int velocity_x; //wektor poruszania si� obeiktu (OX)
    int velocity_y; //wektor poruszania si� obeiktu (OY)
    int projectile_dmg_; //ilosc obra�e� pocisku
};

class PlayerProjectile : public Projectile //obiekt pocisk
{
public:
    PlayerProjectile(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated, int veX, int veY, int dmg, bool bounce);
    ~PlayerProjectile();
    
private:
    
};

class EnemyProjectile : public Projectile
{
public:
	EnemyProjectile(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated, int veX, int veY, int dmg, bool bounce);
	~EnemyProjectile();

private:

};
