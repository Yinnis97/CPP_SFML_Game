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
#include "Heart.h"

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

	//Clock
	Clock clock;

	//Game Logic
	float MoveSpeed;
	float enemyspawntimer;
	float enemyspawntimermax;
	int maxenemies;
	bool mouseHeld;
	bool endgame;
	bool deleted;
	bool BossActive;
	bool EnemyClicked;

	//Game Objects
	TextClass text;
	Buttons buttons;
	Highscores highscores;
	Player player;
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

	//Getters
	const bool GameRunning() const;
	const bool getendgame() const;
	const Vector2f GetupdateMousePos();
	const bool GetBossTimeInterval();

	//Functions
	void pollEvents();
	void toggleFullscreen();
	void spawnEntity();
	void checkFriend(int i);
	void checkEnemy(int i);
	void checkBoss(int i);
	void checkHeart(int i);
	void deleteAllEnemies();

	void updateEnemies();
	void update();

	void renderbackground(RenderTarget& target);
	void renderEnemies(RenderTarget& target);
	void render();
};
