#include "score.h"
#include <string>

Score::Score(std::string font_path,sf::Vector2f position,sf::Color color, int value=0)
{
    if (font.loadFromFile(font_path)) {
        this->setFont(font);
        this->setFillColor(color);
        this->setString(std::to_string(value));
        this->setPosition(position);
    }
}

Score::Score(std::string font_path, sf::Vector2f position, sf::Color color, std::string text)
{
    if (font.loadFromFile(font_path)) {
        this->setFont(font);
        this->setFillColor(color);
        this->setString(text);
        this->setPosition(position);
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

void Score::update(const int &value) { this->value=value; this->setString(std::to_string(this->value)); }
