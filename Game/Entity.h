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
	int Health;
public:
	Entity(char type,int hp) : ID(type),Health(hp) {}

	Sprite sprite;
	Texture Texture;

	virtual void initEntity(RenderWindow& window) = 0;

	const int GetHealth()const;
	void MinHealth(int min);
	const char GetID()const;

};
