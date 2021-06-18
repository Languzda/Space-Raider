#include "powerUp.h"
#include <iostream>

PowerUp :: PowerUp(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated) :
	Actor(texture_path,scale,rect,x,y,is_Repeated){}

PowerUpDmg::PowerUpDmg(std::string texture_path, float scale, sf::IntRect rect, int x, int y,bool is_Repeated):
	PowerUp(texture_path, scale, rect, x, y, is_Repeated) {}


void PowerUp::moveA() {
	this->move(0, 50 * 1.f / 30);
}

void PowerUpDmg::power_up(Hero* &gracz) {
	gracz->dmgUP();
}

PowerUpDmg ::~PowerUpDmg()
{
}

PowerUpMultishot::PowerUpMultishot(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated) :
	PowerUp(texture_path, scale, rect, x, y, is_Repeated) {}


void PowerUpMultishot::power_up(Hero* &gracz) {
	gracz->setMultishot();
}

PowerUpMultishot ::~PowerUpMultishot()
{
}

PowerUpHealth::PowerUpHealth(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated) :
	PowerUp(texture_path, scale, rect, x, y, is_Repeated) {}


void PowerUpHealth::power_up(Hero*& gracz) {
	gracz->setHP(gracz->getHP()+1);
}

PowerUpHealth ::~PowerUpHealth()
{
}