#pragma once
#include "Entity.h"

class Heart : public Entity
{
private:

public:
    Heart(RenderWindow& window, char type, int hp, float speed) : Entity(type, hp, speed)
    {
        this->initEntity(window);
    }

    void initEntity(RenderWindow& window) override;
};

