#include "player.h"

Hero::Hero(std::string texture_path, float scale, sf::IntRect rect, //konstruktor gracza
    int x, int y, bool is_Repeated = false, int hp = 0) : Character(texture_path, scale, rect, x, y, is_Repeated, hp) {
    this->setTextureRect(sf::IntRect(155, 0, 155, 380));
    for (int i = 1; i < 4; i++) animationFrame_.emplace_back(sf::IntRect(155 * (i - 1), 0, 155, 380));
    this->velocity_x_ = 0;
    this->multishot_ = 1;
}

Hero::~Hero() {}

void Hero::dmgUP() { this->power_++; } //Funkcja odpowiadaj¹ca za wzmonienie si³y pocisków

int Hero::getPower() { return this->power_; } //funckja zwracj¹ca moc pocisków 

void Hero::set_bounce() { this->bounce = true; } 

void Hero::set_velocity(const float &x) { //poruszanie pojazdem, zmiana wektora poruszania
    this->velocity_x_ = x;
}

float Hero::get_velocity() { return this->velocity_x_; } // zwrocenie wektora poruszania

void Hero::setMultishot() { //wzomonienie ilosci wystrzeliwanych pociskow
    this->multishot_++;
}

void Hero::moveA() {
    this->move(velocity_x_, 0);
}

void Hero::getBullet(std::vector<PlayerProjectile*> &buff_vector) { //tworzenie pociskow
    int znak;
    for (int i = 0; i < multishot_; i++) {
        if (i % 2 == 0) { znak = -1; } else{  znak = 1;}
        buff_vector.emplace_back(new PlayerProjectile("Textures/transbal.png", 0.05, sf::IntRect(0, 0, 530, 570) ,
            this->getGlobalBounds().left + (this->getGlobalBounds().width / 2 )-10, this->getPosition().y,
            false,(i*40)%200*znak, -350, this->power_, true));
    }
}

bool Hero::exist() { //zwrocenie flagi istnienia
    return this->existing_flag;
}

void Hero::exist(bool destroy) { //zmaiana wartosci flagi istnienia 
    this->existing_flag = destroy;
}