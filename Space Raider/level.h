#pragma once
#include "character.h"
#include "score.h"
#include "player.h"
#include "enemy.h"
#include "projectile.h"
#include "powerUp.h"
#include "asteroid.h"

class Level
{
public:
    Level();
    void generate(const sf::RenderWindow* window, int lvl_nr); //funkcja odpowiedzialna ze generowanie poziomu
   
    int draw(sf::RenderWindow* window);//funckja odpowiedzilana za rysowanie poziomu 
    ~Level();
    void move_player(float x, float y); //funckja ospowiedzialno za sterowanie graczem
    void create_player_bullet(); //towrzenie pocisków gracza
    void create_enemy_bullet();//towrzenie pocisków przeciwnika
    void attack_player(); //fukcja odpiwiedzilana za wybranie przeciwnika i zmiene wektora jego poruszania

private:
    void check_colision(); //obs³uga kolizji
    void update_actors(); //aktualizacja stanu i pozcyji actorów
    void reload_actors(); //prze³adowanie wektora aktorzy
    void create_bonus(Enemy*& enemy); //tworzenie wzmocnienia
    void clear_actors(); //wczyszczenie nie potrzebnych actorów w przypadku skoñczenia poziomu
    std::vector<Actor*> actors_; //wektor wszystkich obiektów animowanych
    std::vector<Enemy*> enemies_; //wektor wszystkich przeciwników z mozliwoœæi¹ ataku
    std::vector<Asteroid *> asteroids_; //wektor wszystkich asteroidów
    std::vector<PowerUp *> power_ups_; //wektor wzmocnieñ
    std::vector<PlayerProjectile*> player_shots_; //wektor pocisków gracza
    std::vector<EnemyProjectile *> enemy_shots_; //wektor pocisków przeciwników
    Hero* player_; //wskaŸnik na gracza
    std::vector<Score*> scoreboads_; //wektor na punktacje i liczbe ¿yæ
    sf::Vector2f window_size_; //wektor 2 elementowy zawieraj¹cy rozmiar okna
    std::vector<sf::Sprite> scene_plain; //wektor zawieraj¹cy t³a gry
    sf::Texture scene_texture;//tekstura t³a gry
    Score* Messege; //Obiekt wiadomoœc s³u¿acy do informacji o pora¿ace
};



