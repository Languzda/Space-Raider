#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <memory>

#include "scene.h"
//#include "character.h"
#include <time.h>

int main()
{
    Scene scene(800, 800);
    Level lvl;
    srand(time(NULL));
    scene.window_loop(&lvl);
    std::cout << "Thank" << std::endl;
}
