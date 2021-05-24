#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <vector>

#include "level.h"

using namespace std;

int main()
{
    Level lvl1;
    lvl1.generate(); //generate level first
    return 0;
}
