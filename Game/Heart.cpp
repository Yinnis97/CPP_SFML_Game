#include "Heart.h"
#include <iostream>

void Heart::initEntity(RenderWindow& window)
{
    if (!this->Texture.loadFromFile("Textures/Entity4.png"))
    {
        cerr << "Error: Kon Entity4 Texture Niet Laden!" << endl;
    }
    this->sprite.setTexture(this->Texture);
    this->sprite.setScale(2.0f, 2.0f);

    this->sprite.setPosition(
        static_cast<float>(rand() % static_cast<int>(window.getSize().x - this->sprite.getGlobalBounds().width)),
        0.f
    );
}
