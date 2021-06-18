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
    void create_player_bullet(); //towrzenie pocisk�w gracza
    void create_enemy_bullet();//towrzenie pocisk�w przeciwnika
    void attack_player(); //fukcja odpiwiedzilana za wybranie przeciwnika i zmiene wektora jego poruszania

private:
    void check_colision(); //obs�uga kolizji
    void update_actors(); //aktualizacja stanu i pozcyji actor�w
    void reload_actors(); //prze�adowanie wektora aktorzy
    void create_bonus(Enemy*& enemy); //tworzenie wzmocnienia
    void clear_actors(); //wczyszczenie nie potrzebnych actor�w w przypadku sko�czenia poziomu
    std::vector<Actor*> actors_; //wektor wszystkich obiekt�w animowanych
    std::vector<Enemy*> enemies_; //wektor wszystkich przeciwnik�w z mozliwo��i� ataku
    std::vector<Asteroid *> asteroids_; //wektor wszystkich asteroid�w
    std::vector<PowerUp *> power_ups_; //wektor wzmocnie�
    std::vector<PlayerProjectile*> player_shots_; //wektor pocisk�w gracza
    std::vector<EnemyProjectile *> enemy_shots_; //wektor pocisk�w przeciwnik�w
    Hero* player_; //wska�nik na gracza
    std::vector<Score*> scoreboads_; //wektor na punktacje i liczbe �y�
    sf::Vector2f window_size_; //wektor 2 elementowy zawieraj�cy rozmiar okna
    std::vector<sf::Sprite> scene_plain; //wektor zawieraj�cy t�a gry
    sf::Texture scene_texture;//tekstura t�a gry
    Score* Messege; //Obiekt wiadomo�c s�u�acy do informacji o pora�ace
};



