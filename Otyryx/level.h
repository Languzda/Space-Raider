#ifndef MAP_H
#define MAP_H

#include "character.h"

class Level
{
public:
    Level();
    void generate(const sf::RenderWindow *window);
    void check_colision();
    void update_actors();
    void draw(sf::RenderWindow *window);
    ~Level();
    void move_player(float x,float y);
    void create_player_bullet();

private:
    std::vector<Actor *> actors_;
    std::vector<Enemy *> enemies_;
//    std::vector<Asteroid *> asteroids_;
//    std::vector<PowerUp *> power_ups_;
    std::vector<PlayerBullet *> player_shots_;
//    std::vector<EnemyShot *> enemy_shots_;
    Hero *player_;
    int enemy_counter;
    void reload_actors();

};

class Scene
{
private:
    sf::RenderWindow window_;
    Level *level_;

public:
    Scene(int width, int height); // Create window
    void set_level(Level *ptr); //
    void draw(); //draw scene
    void events(sf::Event &event,const sf::Time &elapsed,sf::Clock &clock_shot); //chceck events
    void window_loop(); //window loop

};

#endif // MAP_H
