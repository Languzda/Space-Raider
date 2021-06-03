#pragma once
#include "character.h"
#include "score.h"
#include "player.h"
#include "projectile.h"
#include "powerUp.h"

class Level
{
public:
    Level();
    void generate(const sf::RenderWindow* window, int lvl_nr);
    void check_colision();
    void update_actors();
    void draw(sf::RenderWindow* window);
    ~Level();
    void move_player(float x, float y);
    void create_player_bullet();
    void create_enemy_bullet();
    void attack_player();

private:
    std::vector<Actor*> actors_;
    std::vector<Enemy*> enemies_;
    //std::vector<Asteroid *> asteroids_;
    std::vector<PowerUp *> power_ups_;
    std::vector<PlayerProjectile*> player_shots_;
    std::vector<EnemyProjectile *> enemy_shots_;
    Hero* player_;
    std::vector<Score*> scoreboads_;
    int enemy_counter;
    void reload_actors();
    void create_bonus(Enemy* &enemy);
};


