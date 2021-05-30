#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
class Actor : public sf::Sprite //klasa abstrakcyjna wszystkich animowanych obiektów
{
public:
    Actor(std::string texture_path, float scale,sf::IntRect rect, int x , int y, bool is_Repeated);
    virtual ~Actor()=0;
private:
    sf::Texture texture_;
};

class Character : public Actor //klasa abstrakcyjna wszystkich postaci (dzidziczy z Actor)
{
public:
    Character(std::string texture_path, float scale,sf::IntRect rect,
              int x , int y, bool is_Repeated,int hp);
    virtual ~Character();
    virtual void attack();
    void shot();
protected:
    int health_points_;
};

class Hero : public Character //klasa postaci sterowanej przez gracza
{
public:
    void movement();
    void setMultishot();
    void setBounce_ball();
private:
    int multishot_ = 1;
    bool bounce_ball_ = false;

};

//class Melee : public Character
//{
//public:

//};

class Ranged : public Character //klasa przeciwnika
{

};

class Bullet : public Actor //obiekt pocisk
{
    ~Bullet();
};

#endif // CHARACTER_H
