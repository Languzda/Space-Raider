#pragma once
#include "character.h";
#include "projectile.h"

class Hero : public Character //klasa postaci sterowanej przez gracza
{
public:
    Hero(std::string texture_path, float scale, sf::IntRect rect,
        int x, int y, bool is_Repeated, int hp);
    ~Hero();
    void setMultishot(); //wzmacnia iloœc wielostrza³u o 1
    void dmgUP();//zmiania obra¿enie o 1
    void set_bounce();
    int getPower(); //getter aktualnych obra¿eñ pocisku
    void moveA();//poruszanie siê obiektu
    std::vector<PlayerProjectile*> getBullet(); //tworzenie pocisków
    void set_velocity(const float& x);//setter wektora poruszania
    float get_velocity();//getter wektora poruszania
    void exist(bool destroy); //ustawienie flagi istnienia gracza
    bool exist(); //sprawdzenia stanu flagi
private:
    int power_ = 2; //aktualne obra¿enia od pocisków
    bool bounce = false;
    float velocity_x_; //predkosc poruszania siê x
    bool existing_flag = true; //flaga istnienia gracza

};