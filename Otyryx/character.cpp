#include "character.h"
#include <iostream>

Actor::Actor(std::string texture_path, float scale,sf::IntRect rect, int x , int y, bool is_Repeated = false){
    if(texture_.loadFromFile(texture_path)){
        this->setTexture(texture_);
        this->setScale(scale,scale);
        this->setTextureRect(rect);
        texture_.setRepeated(is_Repeated);
        this->setPosition(x,y);
    }
    else{
        std::cout<<"blad tekstury"<<std::endl;
    }
}


Character::Character(std::string texture_path, float scale,sf::IntRect rect,
                     int x , int y, bool is_Repeated = false,int hp=0) :
    Actor(texture_path,scale,rect,x,y,is_Repeated),health_points_(hp){}

void Character::setHP(int hp){this->health_points_=hp;}

int Character::getHP(){return health_points_;}

Hero::Hero(std::string texture_path, float scale,sf::IntRect rect,
           int x , int y, bool is_Repeated = false,int hp=0) : Character(texture_path,scale,rect,x,y,is_Repeated,hp){}

Hero::~Hero(){}


Enemy::Enemy(std::string texture_path, float scale, sf::IntRect rect,
             int x , int y, bool is_Repeated = false, int hp=0, int veX=-25) : Character(texture_path,scale,rect,x,y,is_Repeated,hp),velocity_x(veX){}

void Enemy :: move_e(){
    this->move(velocity_x*1/30,0);
}

void Enemy::change_velocity(const Direction direction){
    if(direction == Left) velocity_x = -std::abs(velocity_x);
    if(direction == Right) velocity_x = std::abs(velocity_x);
}

PlayerBullet::PlayerBullet(std::string texture_path, float scale,sf::IntRect rect, int x , int y, bool is_Repeated,int veX,int veY)
    :Actor(texture_path,scale,rect,x,y,is_Repeated),velocity_x(veX),velocity_y(veY){
    this->setRotation(0.5);
}

void PlayerBullet::move_bullet(){
    this->move(velocity_x*1/30,velocity_y*1/30);
}
