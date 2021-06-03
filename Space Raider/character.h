#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>

enum class Direction { Left, Right, Mid };

class Actor : public sf::Sprite //klasa abstrakcyjna wszystkich animowanych obiektów
{
public:
    Actor(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated);
    virtual ~Actor() = default;
protected:
    sf::Texture texture_;
};

//Klasy postaci

class Character : public Actor //klasa abstrakcyjna wszystkich postaci (dzidziczy z Actor)
{
public:
    Character(std::string texture_path, float scale, sf::IntRect rect,
        int x, int y, bool is_Repeated, int hp);

    virtual ~Character() = default;
    int getHP();
    void setHP(int hp);
    void change_direction_texture(Direction direction);
protected:
    int health_points_;
    std::vector<sf::IntRect> animationFrame_;
};

class Enemy : public Character //klasa przeciwnika
{
public:
    Enemy(std::string texture_path, float scale, sf::IntRect rect,
        int x, int y, bool is_Repeated, int hp, int veX);
    ~Enemy() {};
    void move_e();
    void change_velocity(const Direction direction);
private:
    int velocity_x;
    int velocity_y=0;
};

//Klasy obiektów

#endif // CHARACTER_H

