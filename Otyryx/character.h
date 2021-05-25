#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>

class Character : public sf::Sprite
{
public:
    Character();
    virtual ~Character();
    virtual void attack();
protected:
    int Health_points_;
};

class Hero : public Character{
public:
    void movement();
    void shot();
    void setMultishot();
    void setBounce_ball();
private:
    int multishot_ = 1;
    bool bounce_ball_ = false;

};

class Melee : public Character
{
public:
    void pathfinding();
};

class Ranged : public Character
{

};

#endif // CHARACTER_H
