#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Actor : public sf::Sprite //klasa abstrakcyjna wszystkich animowanych obiekt�w
{
public:
    Actor(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated);
    virtual ~Actor() = default;
    virtual void moveA()=0; //wirtualana metoda odpowiedzialna za poruszanie si� aktor�w
protected:
    sf::Texture texture_;
};