#include "character.h"

Actor::Actor(std::string texture_path, float scale,sf::IntRect rect, int x , int y, bool is_Repeated = false){
    if(texture_.loadFromFile(texture_path)){
        this->setTexture(texture_);
        this->setScale(scale,scale);
        this->setTextureRect(rect);
        texture_.setRepeated(is_Repeated);
        this->setPosition(x,y);
    }
}

Character::Character(std::string texture_path, float scale,sf::IntRect rect,
                     int x , int y, bool is_Repeated = false,int hp=0) :
    Actor(texture_path,scale,rect,x,y,is_Repeated),health_points_(hp){}

