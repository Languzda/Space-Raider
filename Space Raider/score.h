#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Score : public sf::Text
{
public:
    Score(std::string font_path, sf::Vector2f position, sf::Color color, int value);
    void update_score(const int &points);
    void update(const int &value);
protected:
    int value;
    std::string valueSTR;
    sf::Font font;
};
