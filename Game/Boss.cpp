#include "Boss.h"
#include <iostream>



void Boss::initEntity(RenderWindow& window)
{
    if (!this->Texture.loadFromFile("Textures/Entity3.png"))
    {
        cerr << "Error: Kon Entity1 Texture Niet Laden!" << endl;
    }
    this->sprite.setTexture(this->Texture);
    this->sprite.setScale(4.0f, 4.0f);

    this->sprite.setPosition(
        static_cast<float>(rand() % static_cast<int>(window.getSize().x - this->sprite.getGlobalBounds().width)),
        0.f
    );
}
