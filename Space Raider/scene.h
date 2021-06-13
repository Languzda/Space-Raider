#pragma once
#include "level.h"


class Scene
{
private:
    sf::RenderWindow window_;
    Level* level_;
    sf::RectangleShape plain;
    int timer, timer2 = 0;
    int nr_lvl=1;

public:
    Scene(int width, int height); // Create window
    void set_level(Level* ptr, const int& nr_lvl); //
    int draw(); //draw scene
    void events(sf::Event& event, const sf::Time& elapsed, sf::Clock& clock_shot); //chceck events
    void window_loop(Level* lvl); //window loop
};

