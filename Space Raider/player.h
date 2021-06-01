#pragma once
#include "character.h";

class Hero : public Character //klasa postaci sterowanej przez gracza
{
public:
    Hero(std::string texture_path, float scale, sf::IntRect rect,
        int x, int y, bool is_Repeated, int hp);
    ~Hero();
    void setMultishot();
    void dmgUP();
    int getPower();
private:
    int multishot_ = 1;
    int power_ = 2;

};