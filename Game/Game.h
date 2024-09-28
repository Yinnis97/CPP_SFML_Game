#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Network.hpp"
#include "Text.h"

using namespace std;
using namespace sf;


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
	Vector2f mousePosView;
	//Class
	TextClass text;
	//Game Logic
	unsigned coins; //Positief alleen
	int health;
	float MoveSpeed;
	float enemyspawntimer;
	float enemyspawntimermax;
	int maxenemies;
	bool mouseHeld;
	bool endgame;
	//Game Objects
	RectangleShape Restart;
	vector<Sprite> enemies;
	Sprite enemy;
	Texture enemyTexture;
	Sprite background;
	Texture backgroundTexture;
	//Private Functions
	void initvariables();
	void initwindow();
	void initbackground();
	void initenemies();
	void initrestart();


public:
	//Constructors / Destructors
	Game();
	virtual ~Game();
	//Accessors
	const bool GameRunning() const;
	const bool getendgame() const;
	//Functions
	void spawnEnemy();
	void pollEvents();
	void updateMousePos();
	void updateEnemies();
	void updateRestart();
	void update();

	void renderbackground(RenderTarget& target);
	void renderRestart(RenderTarget& target);
	void renderEnemies(RenderTarget& target);
	void render();
};
