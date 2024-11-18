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
#include "Buttons.h"
#include "Highscores.h"
#include "Entity.h"
#include "Enemy.h"
#include "Friend.h"
#include "Boss.h"
#include "Player.h"

using namespace std;
using namespace sf;


class Game
{
	
private:
	//window
	RenderWindow* window;
	VideoMode videomode;
	bool Fullscreen;
	Event ev;

	//Mouse Positions
	Vector2i mousePosWindow;
	Vector2f mousePosView;

	//Classes
	TextClass text;
	Buttons buttons;
	Highscores highscores;

	//Clock
	Clock clock;

	//Game Logic
	unsigned coins; 
	int health;
	float MoveSpeed;
	float enemyspawntimer;
	float enemyspawntimermax;
	int maxenemies;
	bool mouseHeld;
	bool endgame;
	bool Boolquit;
	bool deleted;
	bool BossActive;
	bool EnemyClicked;

	//Game Objects
	vector<Entity*> entities;
	Sprite background;
	Texture backgroundTexture;

	//Private Functions
	void initvariables();
	void initwindow();
	void initbackground();
	


public:

	//Constructor
	Game();

	//Destructor
	virtual ~Game();

	//Accessors
	const bool GameRunning() const;
	const bool getendgame() const;
	
	//Functions
	void toggleFullscreen();
	void spawnEntity();
	void pollEvents();
	const Vector2f GetupdateMousePos();
	void updateEnemies();
	void checkFriend(int i);
	void checkEnemy(int i);
	void checkBoss(int i);
	void deleteAllEnemies();
	void update();

	void renderbackground(RenderTarget& target);
	void renderEnemies(RenderTarget& target);
	void render();
};
