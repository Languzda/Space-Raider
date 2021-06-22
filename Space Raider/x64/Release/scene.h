#pragma once
#include "level.h"
#include <SFML/Audio.hpp>

class Scene
{
private:
    sf::RenderWindow window_; //okno gry
    Level* level_; //wskaŸnik na poziom
    int timer, timer2 = 0; //timery do odmierzania czasu w tikach animacji
    int nr_lvl=1;//nr aktualnego poziomu
public:
    Scene(int width, int height); // Create window
    void set_level(Level* ptr, const int& nr_lvl); //ustawienie aktualnego poziomu
    int draw(); //draw scene
    void events(sf::Event& event, const sf::Time& elapsed, sf::Clock& clock_shot); //sprawdzanie wystêpuj¹cych eventów
    void window_loop(Level* lvl); //window loop
    sf::Music soundtrack_;
};

