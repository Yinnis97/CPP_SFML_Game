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
protected:
	
public:
	Sprite sprite;
	Texture Texture;
	virtual void initEntity() = 0;
	//virtual Sprite spawnEnemy() = 0;

};

