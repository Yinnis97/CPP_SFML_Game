#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Network.hpp"
using namespace sf;
using namespace std;

class Entity
{
private:
	char ID;
public:
	Entity(char type) : ID(type) {}
	
	Sprite sprite;
	Texture Texture;

	virtual void initEntity(RenderWindow& window) = 0;

	const char GetID()const
	{
		return this->ID;
	}
};

