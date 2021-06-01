#include "projectile.h"

Projectile::Projectile(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated, int veX, int veY,int dmg)
    :Actor(texture_path, scale, rect, x, y, is_Repeated), velocity_x(veX), velocity_y(veY) ,projectile_dmg_(dmg){
    this->setRotation(0.5);
}

Projectile::~Projectile()
{
}

PlayerProjectile::PlayerProjectile(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated, int veX, int veY, int dmg)
    :Projectile(texture_path, scale, rect, x, y, is_Repeated,veX,veY,dmg) {
    this->setRotation(0.5);
}

void PlayerProjectile::move_bullet() {
    this->move(velocity_x * 1.f / 30, velocity_y * 1.f / 30);
}

EnemyProjectile::EnemyProjectile(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated, int veX, int veY, int dmg=1)
    : Projectile(texture_path, scale, rect, x, y, is_Repeated,veX,veY,dmg) {
    this->setRotation(0.5);

}

EnemyProjectile::~EnemyProjectile()
{
}
