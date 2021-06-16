#pragma once
#include "character.h"

class Projectile : public Actor
{
public:
    Projectile(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated, int veX, int veY, int dmg, bool bounce);
	~Projectile();
    void move_bullet(/*sf::Time elapsed*/);
    int getDmg();
    bool is_bouncy();
protected:
    bool bounce_;
    int velocity_x;
    int velocity_y;
    int projectile_dmg_;
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
