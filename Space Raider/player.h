#pragma once
#include "character.h";
#include "projectile.h"

class Hero : public Character //klasa postaci sterowanej przez gracza
{
public:
    Hero(std::string texture_path, float scale, sf::IntRect rect,
        int x, int y, bool is_Repeated, int hp);
    ~Hero();
    void setMultishot(); //wzmacnia ilo�c wielostrza�u o 1
    void dmgUP();//zmiania obra�enie o 1
    void set_bounce();
    int getPower(); //getter aktualnych obra�e� pocisku
    void moveA();//poruszanie si� obiektu
    std::vector<PlayerProjectile*> getBullet(); //tworzenie pocisk�w
    void set_velocity(const float& x);//setter wektora poruszania
    float get_velocity();//getter wektora poruszania
    void exist(bool destroy); //ustawienie flagi istnienia gracza
    bool exist(); //sprawdzenia stanu flagi
private:
    int power_ = 2; //aktualne obra�enia od pocisk�w
    bool bounce = false;
    float velocity_x_; //predkosc poruszania si� x
    bool existing_flag = true; //flaga istnienia gracza

};