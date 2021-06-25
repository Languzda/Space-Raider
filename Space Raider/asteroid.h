#pragma once
#include "character.h"

class Asteroid : public Actor
{
public:
    Asteroid(std::string texture_path, float scale, sf::IntRect rect, int x, int y, bool is_Repeated);
    ~Asteroid();
    bool remake(); //metoda odpowiedzialna za zmiene paramtrów ateroidy w momencie zderzenia siê z granicami okna, zwraca wartoœc T/F czy obiekt powinien zostaæ usuniêty
    void moveA(); //poruszanie siê obiektem
private:
    int life_span_ = 3; //czas zycia komety (ilosc powtorzen lotu)
    int velocity_x_ = 50; //wektor poruszania siê (Ox)
    int velocity_y_ = 50;//wektor poruszania siê (Oy)
    int rotate_ = 1; //okreœla kierunek rotacji
};


