#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Score : public sf::Text
{
public:
    Score(std::string font_path, sf::Vector2f position, sf::Color color, int value);
    Score(std::string font_path, sf::Vector2f position, sf::Color color, std::string text);
    void update_score(const int &points);// aktualzacjia wartoœci wyœwietlanej przez obiekt
    void update(const int &value);
protected:
    int value; //wartoœc liczbowa wyœwietlana przez obiekt
    std::string valueSTR;//³añcuch znaków wyœwietlany przez obiekt
    sf::Font font;//rodzaj fontu obiektu
};
