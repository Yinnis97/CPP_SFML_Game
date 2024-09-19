#include "Classes.hpp"
#include <stdexcept>
using namespace sf;
using namespace std;

// Constructor 
Spaceship::Spaceship(const string& textureFile, const RenderWindow& window) 
{
    //Laad de meegegeven file (een png) als texture.
    if (!shiptex.loadFromFile(textureFile)) {
        throw runtime_error("Kan Texture niet laden.");
    }
    //set de texture van het ship.
    ship.setTexture(shiptex);
    //scaled het ship met de grote van de resolutie van het scherm.
    ship.setScale(Vector2f(0.05f, 0.05f));
    //begin positie van het ship zetten.
    ship.setPosition(window.getSize().x / 2.f, window.getSize().y - 100.f);
    //De setOrigin zorgt ervoor dat ik mijn origin pos in het midden van het ship zet
    //Zodat bij het roteren de positie niet veranderd van het ship.
    ship.setOrigin(ship.getLocalBounds().width / 2.f, ship.getLocalBounds().height / 2.f);
}

// Draw method 
void Spaceship::draw(RenderWindow& window) {
    window.draw(ship);
}

// Get position 
Vector2f Spaceship::getPosition() const {
    return ship.getPosition();
}

// Set position
void Spaceship::setPosition(float x, float y) {
    ship.setPosition(x, y);
}

// Move method 
void Spaceship::move(float offsetX, float offsetY) {
    ship.move(offsetX, offsetY);
}
FloatRect Spaceship::getGlobalBounds() const {
    return ship.getGlobalBounds();
}

// Set rotation
void Spaceship::setRotation(float angle) {
    ship.setRotation(angle);
}

// Get rotation 
float Spaceship::getRotation() const {
    return ship.getRotation();
}

////////////////////////////////////////////////////////////////////////////

// Constructor
Background::Background(const std::string& textureFile, const sf::RenderWindow& window) 
{
    // Laad texture
    if (!backgroundTexture.loadFromFile(textureFile)) {
        throw std::runtime_error("Could not load background texture");
    }

    // Set texture
    background.setTexture(backgroundTexture);

    // Scale background naar window size
    background.setScale(
        window.getSize().x / background.getLocalBounds().width,
        window.getSize().y / background.getLocalBounds().height
    );
}

// Draw Method
void Background::draw(sf::RenderWindow& window) {
    window.draw(background);
}
