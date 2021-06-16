#include "projectile.h"

//podstawowy konstruktor

Projectile::Projectile(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated, int veX, int veY,int dmg, bool bounce)
    :Actor(texture_path, scale, rect, x, y, is_Repeated), velocity_x(veX), velocity_y(veY) ,projectile_dmg_(dmg), bounce_(bounce) {
    this->setOrigin(this->getGlobalBounds().width / 2, this->getGlobalBounds().height / 2);
}

Projectile::~Projectile()
{
}


void Projectile::move_bullet() { //poruszanie pocisku po planszy
    this->move(velocity_x * 1.f / 30, velocity_y * 1.f / 30);
    this->rotate(80 * 1.f / 30);
}

int Projectile::getDmg() { return projectile_dmg_; } //zwracanie wartosci obrazaen pocisku

//Konstruktory pocisków przeciwników i gracza
PlayerProjectile::PlayerProjectile(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated, int veX, int veY, int dmg, bool bounce)
    :Projectile(texture_path, scale, rect, x, y, is_Repeated, veX, veY, dmg, bounce) {

}

PlayerProjectile::~PlayerProjectile() {

}

EnemyProjectile::EnemyProjectile(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated, int veX, int veY, int dmg=1,bool bounce=true)
    : Projectile(texture_path, scale, rect, x, y, is_Repeated,veX,veY,dmg,bounce) {

}

EnemyProjectile::~EnemyProjectile()
{
}
