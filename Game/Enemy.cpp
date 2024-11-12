#include "Enemy.h"
#include <iostream>

void Enemy::initEntity()
{
    if (!this->Texture.loadFromFile("Textures/Enemy.png"))
    {
        cerr << "Error: Kon Enemy Texture Niet Laden!" << endl;
    }
    this->sprite.setTexture(this->Texture);
    this->sprite.setScale(2.0f, 2.0f);
}
