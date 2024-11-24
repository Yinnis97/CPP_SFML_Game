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
	float Speed;
public:
	Entity(char type,int hp,float speed) : ID(type),Health(hp),Speed(speed) {}

	Sprite sprite;
	Texture Texture;

	virtual void initEntity(RenderWindow& window) = 0;

	const float GetSpeed()const;
	const int GetHealth()const;
	void MinHealth(int min);
	const char GetID()const;

};
