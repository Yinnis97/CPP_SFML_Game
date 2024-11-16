#pragma once
#include "Entity.h"

class Enemy : public Entity
{
private:

public:
    Enemy(RenderWindow& window, char type,int hp) : Entity(type,hp)
    {
        this->initEntity(window);
    }

    void initEntity(RenderWindow& window) override;
    
};

