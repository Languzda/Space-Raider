#include "projectile.h"

Projectile::Projectile(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated, int veX, int veY,int dmg, bool bounce)
    :Actor(texture_path, scale, rect, x, y, is_Repeated), velocity_x(veX), velocity_y(veY) ,projectile_dmg_(dmg), bounce_(bounce) {
    
}

Projectile::~Projectile()
{
}

PlayerProjectile::PlayerProjectile(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated, int veX, int veY, int dmg, bool bounce)
    :Projectile(texture_path, scale, rect, x, y, is_Repeated,veX,veY,dmg,bounce)  {

}

void Projectile::move_bullet() {
    this->move(velocity_x * 1.f / 30, velocity_y * 1.f / 30);
}

int Projectile::getDmg() { return projectile_dmg_; }

EnemyProjectile::EnemyProjectile(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated, int veX, int veY, int dmg=1,bool bounce=true)
    : Projectile(texture_path, scale, rect, x, y, is_Repeated,veX,veY,dmg,bounce) {

}

EnemyProjectile::~EnemyProjectile()
{
}
