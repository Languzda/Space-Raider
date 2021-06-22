#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Score : public sf::Text
{
public:
    Score(std::string font_path, sf::Vector2f position, sf::Color color, int value);
    Score(std::string font_path, sf::Vector2f position, sf::Color color, std::string text);
    void update_score(const int &points);// aktualzacjia warto�ci wy�wietlanej przez obiekt
    void update(const int &value);
protected:
    int value; //warto�c liczbowa wy�wietlana przez obiekt
    std::string valueSTR;//�a�cuch znak�w wy�wietlany przez obiekt
    sf::Font font;//rodzaj fontu obiektu
};
