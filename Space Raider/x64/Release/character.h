#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include "actor.h"
#include "projectile.h"

enum class Direction { Left, Right, Mid };

class Character : public Actor //klasa abstrakcyjna wszystkich postaci (dzidziczy z Actor)
{
public:
    Character(std::string texture_path, float scale, sf::IntRect rect,
        int x, int y, bool is_Repeated, int hp);
    virtual void moveA()=0;
    virtual ~Character() = default;
    int getHP();  //getter punktów ¿ycia
    void setHP(int hp); //setter punktów ¿ycia
    void change_direction_texture(Direction direction);//funckja odpowiedzialna za zmianne klatki animacji
protected:
    int health_points_; //punkty ¿ycia
    std::vector<sf::IntRect> animationFrame_;//wektor z klatkami animacji
    int multishot_ = 1; //zmienna odpowiadajaca wielostrza³owi postaci
};

#endif // CHARACTER_H

