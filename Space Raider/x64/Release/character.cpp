#include "character.h"

Character::Character(std::string texture_path, float scale, sf::IntRect rect, 
    int x, int y, bool is_Repeated = false, int hp = 0) :
    Actor(texture_path, scale, rect, x, y, is_Repeated), health_points_(hp) {
}

void Character::setHP(int hp) { this->health_points_ = hp; } //setter punktów ¿ycia

int Character::getHP() { return health_points_; } //getter punktów ¿ycia

void Character::change_direction_texture(Direction direction) { //funckja odpowiedzialna za zmianne klatki animacji
    if (direction == Direction::Right) this->setTextureRect(animationFrame_[2]);
    if (direction == Direction::Mid) this->setTextureRect(animationFrame_[1]);
    if (direction == Direction::Left) this->setTextureRect(animationFrame_[0]);
}
