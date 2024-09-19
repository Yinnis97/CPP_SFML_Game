#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

class Spaceship 
{
private:
    Texture shiptex;    
    Sprite ship;        

public:
    // Constructor
    Spaceship(const string& textureFile, const RenderWindow& window);

    // Draw method
    void draw(RenderWindow& window);

    // Getter for position
    Vector2f getPosition() const;

    // Setter for position
    void setPosition(float x, float y);

    // Movement functionality
    void move(float offsetX, float offsetY);

    FloatRect getGlobalBounds() const;

    // Rotation methods
    void setRotation(float angle);    // Set a specific angle
    float getRotation() const;        // Get the current rotation angle

};

class Background 
{
private:
    sf::Texture backgroundTexture;  
    sf::Sprite background;          

public:
    // Constructor
    Background(const std::string& textureFile, const sf::RenderWindow& window);

    void draw(sf::RenderWindow& window);
};

#endif