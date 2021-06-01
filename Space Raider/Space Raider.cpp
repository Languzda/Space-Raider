#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <memory>

#include "scene.h"
#include "character.h"

using namespace std;

int main()
{
    Scene scene(800, 800);
    Level lvl;
    scene.set_level(&lvl);
    scene.window_loop();
}
