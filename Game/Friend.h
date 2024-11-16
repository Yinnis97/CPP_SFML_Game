#pragma once
#include "Entity.h"

class Friend : public Entity
{
private:

public:
	Friend(RenderWindow& window, char type, int hp) : Entity(type,hp)
    {
        this->initEntity(window);
    }

	void initEntity(RenderWindow& window) override;

};

