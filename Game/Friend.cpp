#include "Friend.h"
#include <iostream>

void Friend::initEntity()
{
    if (!this->Texture.loadFromFile("Textures/Friend.png"))
    {
        cerr << "Error: Kon Friend Texture Niet Laden!" << endl;
    }
    this->sprite.setTexture(this->Texture);
    this->sprite.setScale(2.0f, 2.0f);
}