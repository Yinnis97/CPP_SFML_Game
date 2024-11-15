#pragma once
#include "Entity.h"

class Enemy : public Entity
{
private:

public:
    Enemy(RenderWindow& window, char type) : Entity(type)
    {
        this->initEntity(window);
    }

    void initEntity(RenderWindow& window) override;
    
};

