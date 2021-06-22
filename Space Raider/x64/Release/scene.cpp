#include "scene.h"

Scene::Scene(int width, int height) : window_(sf::VideoMode(width, height), "Space Raiders") {
    window_.setFramerateLimit(30);
    if (soundtrack_.openFromFile("mixkit.wav")) {
        soundtrack_.setVolume(60);
        soundtrack_.setLoop(true);
        soundtrack_.play();
    }
};

void Scene::set_level(Level* ptr,const int& nr_lvl ) {
    ptr->generate(&window_,nr_lvl);
    level_ = ptr;
}

int Scene::draw() {
    window_.clear(sf::Color::Black);
    // draw every actor

    int what_next =level_->draw(&window_);

    // end the current frame
    window_.display();
    return what_next;
}

void Scene::events(sf::Event& event, const sf::Time& elapsed, sf::Clock& clock_shot) {
    if (event.type == sf::Event::Closed)    window_.close();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))    window_.close();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        //game pause
    }

    
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            level_->move_player(-300 * 1 / 30/*elapsed.asSeconds()*/, 0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            level_->move_player(300 * 1 / 30/*elapsed.asSeconds()*/, 0);
        }
        else {
            level_->move_player(0, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            sf::Time shot_elapsed = clock_shot.restart();;
            if (shot_elapsed.asSeconds() > 0.1) {
                level_->create_player_bullet();
                //shot_elapsed = clock_shot.restart();
            }
        }
    }//player movement
}

void Scene::window_loop(Level* lvl) {
    sf::Event event;
    sf::Clock clock;
    sf::Clock clock_shot;
   
    while (window_.isOpen()) { //when window is open check the events
        for (int i = 1; i <= 8; i++) {
            this->set_level(lvl, i);
            do {
                
                sf::Time time_elapsed = clock.restart();
                while (window_.pollEvent(event)) { //
                    events(event, time_elapsed, clock_shot);

                }
                if (nr_lvl == 1) {
                    timer++;
                    timer2++;
                    if (timer > 20) {
                        timer = 0;
                        level_->create_enemy_bullet();
                    }
                    if (timer2 > 150) {
                        timer2 = 0;
                        level_->attack_player();
                    }
                }
                if (!window_.isOpen()) break;
            }while (draw() != 0);
        }if (!window_.isOpen()) break;
        window_.close();
    }
}

