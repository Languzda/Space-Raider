#pragma once
#include "character.h"
#include "player.h"

class PowerUp : public Actor
{
public:
	PowerUp(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated);
	virtual ~PowerUp()=default;
	virtual void power_up(Hero* &gracz)=0;
	void move_b();
};

class PowerUpDmg : public PowerUp
{
public:
	PowerUpDmg(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated);
	~PowerUpDmg();
	void power_up(Hero* &gracz);
};

class PowerUpMultishot : public PowerUp
{
public:
	PowerUpMultishot(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated);
	~PowerUpMultishot();
	void power_up(Hero* &gracz);
};

