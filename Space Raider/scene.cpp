#include "scene.h"

Scene::Scene(int width, int height) : window_(sf::VideoMode(width, height), "Otyryx the Game") {
    window_.setFramerateLimit(30);
};

void Scene::set_level(Level* ptr) {
    ptr->generate(&window_);
    level_ = ptr;
}

void Scene::draw() {
    window_.clear(sf::Color::Black);
    // draw every actor

    level_->draw(&window_);

    // end the current frame
    window_.display();
}

void Scene::events(sf::Event& event, const sf::Time& elapsed, sf::Clock& clock_shot) {
    if (event.type == sf::Event::Closed)    window_.close();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))    window_.close();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        //game pause
    }

    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            level_->move_player(-100 * 1 / 30/*elapsed.asSeconds()*/, 0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            level_->move_player(100 * 1 / 30/*elapsed.asSeconds()*/, 0);
        }
        else {
            level_->move_player(0, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            sf::Time shot_elapsed = clock_shot.restart();;
            if (shot_elapsed.asSeconds() > 0.25) {
                level_->create_player_bullet();
                //shot_elapsed = clock_shot.restart();
            }
        }
    }//player movement
}

void Scene::window_loop() {
    sf::Event event;
    sf::Clock clock;
    sf::Clock clock_shot;
    while (window_.isOpen()) { //when window is open check the events

        sf::Time time_elapsed = clock.restart();
        while (window_.pollEvent(event)) { //
            events(event, time_elapsed, clock_shot);

        }
        draw();
    }
}
