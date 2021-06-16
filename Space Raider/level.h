#pragma once
#include "character.h"
#include "score.h"
#include "player.h"
#include "enemy.h"
#include "projectile.h"
#include "powerUp.h"

class Level
{
public:
    Level();
    void generate(const sf::RenderWindow* window, int lvl_nr);
   
    int draw(sf::RenderWindow* window);
    ~Level();
    void move_player(float x, float y);
    void create_player_bullet();
    void create_enemy_bullet();
    void attack_player();

private:
    void check_colision();
    void update_actors();
    std::vector<Actor*> actors_;
    std::vector<Enemy*> enemies_;
    std::vector<Asteroid *> asteroids_;
    std::vector<PowerUp *> power_ups_;
    std::vector<PlayerProjectile*> player_shots_;
    std::vector<EnemyProjectile *> enemy_shots_;
    Hero* player_;
    std::vector<Score*> scoreboads_;
   // int enemy_counter;
    void reload_actors();
    void create_bonus(Enemy* &enemy);
    sf::Vector2f window_size_;
    void clear_actors();
    std::vector<sf::Sprite> scene_plain;
    sf::Texture scene_texture;
    void Game_Over();
    Score* Messege;
};



