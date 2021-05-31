#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
class Actor : public sf::Sprite //klasa abstrakcyjna wszystkich animowanych obiektów
{
public:
    Actor(std::string texture_path, float scale,sf::IntRect rect, int x , int y, bool is_Repeated);
    virtual ~Actor()=default;
private:
    sf::Texture texture_;
};

//Klasy postaci

class Character : public Actor //klasa abstrakcyjna wszystkich postaci (dzidziczy z Actor)
{
public:
    Character(std::string texture_path, float scale,sf::IntRect rect,
              int x , int y, bool is_Repeated,int hp);
    virtual ~Character()=default;
    //virtual void attack();
    void shot();
    int getHP();
    void setHP(int hp);
protected:
    int health_points_;
};

class Hero : public Character //klasa postaci sterowanej przez gracza
{
public:
    Hero(std::string texture_path, float scale,sf::IntRect rect,
         int x , int y, bool is_Repeated,int hp);
    ~Hero();
    void setMultishot();
    void setBounce_ball();
private:
    int multishot_ = 1;
    bool bounce_ball_ = false;

};

enum Direction { Left , Right };
class Enemy : public Character //klasa przeciwnika
{
public:
    Enemy(std::string texture_path, float scale,sf::IntRect rect,
         int x , int y, bool is_Repeated,int hp, int veX);
    ~Enemy(){};
    void move_e();
    void change_velocity(const Direction direction);
private:
    int velocity_x;
};

//Klasy obiektów

class PlayerBullet : public Actor //obiekt pocisk
{
public:
    PlayerBullet(std::string texture_path, float scale,sf::IntRect rect, int x , int y, bool is_Repeated,int veX,int veY);
    ~PlayerBullet(){};
    void move_bullet(/*sf::Time elapsed*/);
private:
    int velocity_x;
    int velocity_y;
};

#endif // CHARACTER_H
