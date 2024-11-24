#pragma once
#include "Entity.h"

class Friend : public Entity
{
private:

public:
	Friend(RenderWindow& window, char type, int hp, float speed) : Entity(type, hp, speed)
    {
        this->initEntity(window);
    }

	void initEntity(RenderWindow& window) override;

};

