#pragma once
#include "Entity.h"

class Boss : public Entity
{
private:
   
public:
    Boss(RenderWindow& window, char type, int hp, float speed) : Entity(type, hp, speed)
    {
        this->initEntity(window);
    }

    void initEntity(RenderWindow& window) override;
};

