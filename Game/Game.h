#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Network.hpp"

using namespace std;
using namespace sf;
/*
   Main Game class
   This-> : zodat je duidelijk kan zien wat deel uit maakt van de class en wat niet.

   Info :
   virtual ~Game(); -> 
   virtual zorgt ervoor dat eerst de destructor "activeert" voor de class wordt gedelete.
   Destructor zorgt ervoor dat er geen memory leak is en dat alles mooi wordt opgeruimt.
*/

class Game
{
private:
	//Variables
	//window
	RenderWindow* window;
	VideoMode videomode;
	Event ev;
	//Mouse Positions
	Vector2i mousePosWindow;
	//Game Logic
	float enemyspawntimer;
	float enemyspawntimermax;
	int maxenemies;
	int coins;
	//Game Objects
	vector<Sprite> enemies;
	Sprite enemy;          
	Texture enemyTexture;
	//Private Functions
	void initvariables(); 
	void initwindow();
	void initenemies();

public:
	//Constructors / Destructors
	Game();
	virtual ~Game();
	//Accessors
	const bool GameRunning() const;
	//Functions
	void spawnEnemy();
	void pollEvents();
	void updateMousePos();
	void updateEnemies();
	void update();
	void renderEnemies();
	void render();

};

