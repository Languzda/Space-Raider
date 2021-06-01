#include "score.h"
#include <string>

Score::Score(std::string font_path)
{
    if (font.loadFromFile(font_path)) {
        this->setFont(font);
        this->value = 0;
        this->valueSTR = "000";
        this->setFillColor(sf::Color::Red);
        this->setString(valueSTR);
        this->setPosition(sf::Vector2f(700, 50));
    }
}

void Score::update_score(const int &points) {
    this->value += points;
    this->valueSTR = std::to_string(value);
    while (valueSTR.size() < 4) {
        valueSTR = "0" + valueSTR;
    }
    this->setString(valueSTR);
}