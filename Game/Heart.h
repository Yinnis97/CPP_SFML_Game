#pragma once
#include "Entity.h"
class Heart : public Entity
{
private:

public:
    Heart(RenderWindow& window, char type, int hp) : Entity(type, hp)
    {
        this->initEntity(window);
    }

    void initEntity(RenderWindow& window) override;
};

