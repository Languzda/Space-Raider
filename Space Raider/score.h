#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Score : public sf::Text
{
public:
    Score(std::string font_path);

    void update_score(const int &points);
private:
    int value;
    std::string valueSTR;
    sf::Font font;
};
