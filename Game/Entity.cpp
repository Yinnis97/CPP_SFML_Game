#include "Entity.h"

const float Entity::GetSpeed() const
{
    return this->Speed;
}

const int Entity::GetHealth() const
{
    return this->Health;
}

void Entity::MinHealth(int min)
{
    this->Health = this->Health - min;
}

const char Entity::GetID() const
{
    return this->ID;
}
