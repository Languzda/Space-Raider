#include "enemy.h"

Enemy::Enemy(std::string texture_path, float scale, sf::IntRect rect,
    int x, int y, bool is_Repeated = false, int hp = 0, int veX = -25) :
    Character(texture_path, scale, rect, x, y, is_Repeated, hp), velocity_x(veX) {}

Enemy::Enemy(std::string texture_path, float scale, sf::IntRect rect,
    int x, int y, bool is_Repeated = false, int hp = 0, int veX = -25, int multishot = 1) :
    Character(texture_path, scale, rect, x, y, is_Repeated, hp), velocity_x(veX) {
    this->multishot_ = multishot;
}

void Enemy::move_e() {
    this->move(velocity_x * (1.f / 30), velocity_y * (1.f / 30));
}

void Enemy::change_velocity(const Direction direction) {
    if (direction == Direction::Left) velocity_x = -std::abs(velocity_x);
    if (direction == Direction::Right) velocity_x = std::abs(velocity_x);
    if (direction == Direction::Mid) { /*velocity_x = 0;*/ velocity_y = 75; }
}

std::vector<EnemyProjectile*> Enemy::getBullet() {
    std::vector<EnemyProjectile*> buff_vector;
    int znak;
    for (int i = 0; i < multishot_; i++) {
        if (i % 2 == 0) { znak = -1; }
        else { znak = 1; }
        buff_vector.emplace_back(new EnemyProjectile("ball.png", 1, sf::IntRect(0, 0, 25, 25),
            this->getPosition().x + this->getGlobalBounds().width / 2, this->getPosition().y,
            false, (i * 40) % 200 * znak, 200, 1, true));
    }

    return buff_vector;
}