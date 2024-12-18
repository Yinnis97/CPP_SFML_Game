#include "Enemy.h"
#include <iostream>


void Enemy::initEntity(RenderWindow& window)
{
    if (!this->Texture.loadFromFile("Textures/Entity5.png"))
    {
        cerr << "Error: Kon Entity1 Texture Niet Laden!" << endl;
    }
    this->sprite.setTexture(this->Texture);

    int type = rand() % 3;
    switch (type)
    {
    case 0:
        this->sprite.setScale(1.0f, 1.0f);
        break;
    case 1:
        this->sprite.setScale(2.0f, 2.0f);
        break;
    case 2:
        this->sprite.setScale(3.0f, 3.0f);
        break;

    default:
        this->sprite.setScale(2.0f, 2.0f);
        break;
    }

    this->sprite.setPosition(
        static_cast<float>(rand() % static_cast<int>(window.getSize().x - this->sprite.getGlobalBounds().width)),
        0.f
    );
}
