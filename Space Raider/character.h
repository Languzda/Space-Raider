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
    int multishot_ = 1;
};

class Asteroid : public Actor
{
public:
	Asteroid(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated);
	~Asteroid();
    bool remake();
    void move_asteroid(const sf::Time& elapsed);

private:
    int life_span_ = 3;
    int velocity_x_=50;
    int velocity_y_=50;
};




//Klasy obiektów

#endif // CHARACTER_H

