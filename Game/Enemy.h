#pragma once
#include "Entity.h"

class Enemy : public Entity
{
private:

public:
    Enemy(RenderWindow& window, char type, int hp, float speed) : Entity(type, hp, speed)
    {
        this->initEntity(window);
    }

    void initEntity(RenderWindow& window) override;
    
};

