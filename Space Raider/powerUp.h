#pragma once
#include "character.h"
#include "player.h"

class PowerUp : public Actor //klasa abstrakcyjna wzmocnienia
{
public:
	PowerUp(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated);
	virtual ~PowerUp()=default;
	virtual void power_up(Hero* &gracz)=0; //wirtualna metoda wzmocnienia gracza
	void moveA(); //metoda odpowiedzialna za poruszanie si� obiektu PowerUp
};

class PowerUpDmg : public PowerUp //klasa dziedzicz�ca z klasy PowerUp, specyfikuje wzmocnienie jako wzmocnienie obrazen
{
public:
	PowerUpDmg(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated);
	~PowerUpDmg();
	void power_up(Hero* &gracz);// metoda wzmocnienia gracza, wzmiacnia obra�enia
};

class PowerUpMultishot : public PowerUp//klasa dziedzicz�ca z klasy PowerUp, specyfikuje wzmocnienie jako wzmocnienie wielostrza�u
{
public:
	PowerUpMultishot(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated);
	~PowerUpMultishot();
	void power_up(Hero* &gracz);// metoda wzmocnienia gracza, wzmiacnia wielostrza�
};

class PowerUpHealth : public PowerUp//klasa dziedzicz�ca z klasy PowerUp, specyfikuje wzmocnienie jako wzmocnienie punkt�w �ycia
{
public:
	PowerUpHealth(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated);
	~PowerUpHealth();
	void power_up(Hero*& gracz);// metoda wzmocnienia gracza, dodaje punkty �ycia

};