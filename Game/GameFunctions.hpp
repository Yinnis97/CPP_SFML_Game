// GameFunctions.hpp
// function declarations
#ifndef GAMEFUNCTIONS_HPP
#define GAMEFUNCTIONS_HPP
#include "Classes.hpp"
#include <SFML/Graphics.hpp>
using namespace sf;

void Update(Spaceship& spaceship, RenderWindow& window);
void Draw(RenderWindow& window, Spaceship& spaceship, Background& background);

#endif 
