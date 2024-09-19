// GameFunctions.cpp
// function definitions

#include "Classes.hpp"
#include "GameFunctions.hpp"
using namespace sf;

void Update(Spaceship& spaceship, RenderWindow& window)
{
    FloatRect bounds = spaceship.getGlobalBounds();
    
    if (Keyboard::isKeyPressed(Keyboard::Q) && bounds.left > 0)
    {
        spaceship.move(-10.f, 0.f);
        spaceship.setRotation(270.f);
    }
    if (Keyboard::isKeyPressed(Keyboard::D) && bounds.left + bounds.width < window.getSize().x)
    {
        spaceship.move(10.f, 0.f);
        spaceship.setRotation(90.f);
    }
    if (Keyboard::isKeyPressed(Keyboard::Z) && bounds.top > 0)
    {
        spaceship.move(0.f, -10.f);
        spaceship.setRotation(0.f);
    }
    if (Keyboard::isKeyPressed(Keyboard::S) && bounds.top + bounds.height < window.getSize().y) //1080 * 0.05 = 54
    {
        spaceship.move(0.f, 10.f);
        spaceship.setRotation(180.f);
    }

}

void Draw(RenderWindow& window, Spaceship& spaceship, Background &background)
{
    window.clear(Color::Cyan); //Clear : Moet gebeuren vor telkens een nieuwe versie van de display te krijgen.
    background.draw(window);
    spaceship.draw(window);    //Draw Spaceship
    window.display();          //Display the updated version.
}

