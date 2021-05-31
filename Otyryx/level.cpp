#include "level.h"

Level::Level()
{

}

Level::~Level(){
    player_shots_.erase(player_shots_.begin(),player_shots_.end());
    for(auto &actor : actors_){
        delete actor;
    }
}

void Level :: generate(const sf::RenderWindow *window){
    player_= new Hero("character.png",1,sf::IntRect(200,0,37,37),window->getSize().x/2,window->getSize().y-150,false,2);
    actors_.emplace_back(player_);
    Enemy *chicken;
    for(int j=0;j<4;j++){
        for(int i=0;i<6;i++){
            chicken = new  Enemy("enemy.png",0.1,sf::IntRect(0,0,600,650),100*i+25,window->getSize().y-(400+100*j),false,2,-75);
            enemies_.emplace_back(chicken);
            actors_.emplace_back(chicken);
        }
    }
    enemy_counter=24;
}

void Level :: check_colision(){
    bool exit = false;
    for(auto &el : enemies_){
        if(el->getGlobalBounds().left<=0) {for(auto &ell : enemies_) ell->change_velocity(Direction::Right); break;}
        if(el->getGlobalBounds().left+el->getGlobalBounds().width >800) {for(auto &ell : enemies_) ell->change_velocity(Direction::Left); break;}
    }

    for(auto it = player_shots_.begin();it!=player_shots_.end();){ //check that bullet is out of window
        sf::FloatRect bullet_bounds = (*it)->getGlobalBounds();
        if(bullet_bounds.top<=0){
            it=player_shots_.erase(it);
            reload_actors();
            break;
        }
        for(auto itt = enemies_.begin();itt!=enemies_.end();itt++){ //check that enemy was hitten
            if((*itt)->getGlobalBounds().intersects((*it)->getGlobalBounds())){
                if((*itt)->getHP()<=1){
                    itt=enemies_.erase(itt);
                    it=player_shots_.erase(it);
                    reload_actors();
                    it++;
                    enemy_counter--;
                    exit=true;
                    break;
                }
                else{
                    (*itt)->setHP((*itt)->getHP()-1);
                    it=player_shots_.erase(it);
                    reload_actors();
                    exit=true;
                    break;
                }
            }
        }
        if(exit==true)break;
        it++;
    }
}

void Level :: reload_actors(){
    actors_.erase(actors_.begin(),actors_.end());
    actors_.emplace_back(player_);
    for(auto &e:enemies_){
        actors_.emplace_back(e);
    }
    for(auto &b: player_shots_){
        actors_.emplace_back(b);
    }
} //erase actors vector, then emplace back all actors back

void Level :: update_actors(){
    check_colision();
    for(auto &bullet : player_shots_){
        bullet->rotate(1080*1/30);
        bullet->move_bullet();
    }
    for(auto &enemy : enemies_){
        enemy->move_e();
    }
}   //update location & rotation of actors, its checking colision too

void Level :: draw(sf::RenderWindow *window){
    update_actors();
    for(auto &obj : actors_){
        window->draw(*obj);
    }
}

void Level :: move_player(float x, float y){ player_->move(x,y);}

void Level :: create_player_bullet(){
    PlayerBullet *bullet =new PlayerBullet("ball.png",1,sf::IntRect(0,0,25,25),
            player_->getPosition().x+player_->getGlobalBounds().width/2,player_->getPosition().y,false,0,-150);
    player_shots_.emplace_back(bullet);
    actors_.emplace_back(bullet);
}

/// Class Scene methods
///
Scene::Scene(int width,int height) : window_(sf::VideoMode(width, height), "Otyryx the Game"){
    window_.setFramerateLimit(30);
};

void Scene::set_level(Level *ptr){
    ptr->generate(&window_);
    level_ = ptr;
}

void Scene::draw(){
    window_.clear(sf::Color::Black);
    // draw every actor

   level_->draw(&window_);

    // end the current frame
    window_.display();
}

void Scene::events(sf::Event &event, const sf::Time &elapsed, sf::Clock &clock_shot){
    if (event.type == sf::Event::Closed)    window_.close();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))    window_.close();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
        //game pause
    }

    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            level_->move_player(-100*1/30/*elapsed.asSeconds()*/,0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            level_->move_player(100*1/30/*elapsed.asSeconds()*/,0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            sf::Time shot_elapsed=clock_shot.restart();;
            if(shot_elapsed.asSeconds()>0.5){
                level_->create_player_bullet();
                //shot_elapsed = clock_shot.restart();
            }
        }
    }//player movement
}

void Scene::window_loop(){
    sf::Event event;
    sf::Clock clock;
    sf::Clock clock_shot;
    while (window_.isOpen()) { //when window is open check the events

        sf::Time time_elapsed = clock.restart();
        while (window_.pollEvent(event)) { //
            events(event,time_elapsed,clock_shot);

        }
        draw();
    }
}
