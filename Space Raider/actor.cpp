#include "actor.h"


Actor::Actor(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated = false) {
    if (texture_.loadFromFile(texture_path)) {
        this->setTexture(texture_);
        this->setScale(scale, scale);
        this->setTextureRect(rect);
        texture_.setRepeated(is_Repeated);
        this->setPosition(x, y);
        this->setOrigin(this->getGlobalBounds().width / 2, this->getGlobalBounds().height / 2);
    }
    else {
        std::cout << "blad tekstury" << std::endl;
    }
}
