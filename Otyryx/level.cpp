#include "level.h"

Level::Level()
{

}

Level::~Level(){
    for(auto &actor : actors_){
        delete actor;
    }
}

/// Class Scene methods
///
Scene::Scene(int width,int height) : window_(sf::VideoMode(width, height), "Otyryx the Game"){};

void Scene::set_level(Level *ptr){
    level_ = ptr;
}

void Scene::draw(){
    window_.clear(sf::Color::Black);
    // draw every actor

   //level_->draw(&window_);

    // end the current frame
    window_.display();
}

void Scene::events(sf::Event &event){}

void Scene::window_loop(){
    while (window_.isOpen()) { //when window is open check the events
        sf::Event event;
        while (window_.pollEvent(event)) { //
            events(event);
            draw();
        }
    }
}
