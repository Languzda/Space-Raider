#ifndef MAP_H
#define MAP_H

#include "character.h"

class Level
{
public:
    Level();
    void generate();
    void draw();
    ~Level();
private:
    std::vector<Actor *> actors_;
    Hero *player_;
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
    void events(sf::Event &event); //chceck events
    void window_loop(); //window loop

};

class Terrain{
public:
    Terrain();
private:
    int pos_x,pos_y;
    bool block_movement = true;
    bool block_shoots = true;
};

#endif // MAP_H
