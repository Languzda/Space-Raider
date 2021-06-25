#pragma once
#include "character.h"

class Asteroid : public Actor
{
public:
    Asteroid(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated);
    ~Asteroid();
    bool remake(); //metoda odpowiedzialna za zmiene paramtr�w ateroidy w momencie zderzenia si� z granicami okna, zwraca warto�c T/F czy obiekt powinien zosta� usuni�ty
    void moveA(); //poruszanie si� obiektem
private:
    int life_span_ = 3; //czas zycia komety (ilosc powtorzen lotu)
    int velocity_x_ = 50; //wektor poruszania si� (Ox)
    int velocity_y_ = 50;//wektor poruszania si� (Oy)
    int rotate_ = 1; //okre�la kierunek rotacji
};


