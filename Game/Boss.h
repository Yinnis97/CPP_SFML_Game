#pragma once
#include "Entity.h"
class Boss :
    public Entity
{
private:
   
public:
    Boss(RenderWindow& window, char type, int hp) : Entity(type,hp)
    {
        this->initEntity(window);
    }

    void initEntity(RenderWindow& window) override;
};

