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

using namespace std;
using namespace sf;
/*
   Main Game class
   This-> : zodat je duidelijk kan zien wat deel uit maakt van de class en wat niet.

   Info :
   virtual ~Game(); -> 
   virtual zorgt ervoor dat eerst de destructor "activeert" voor de class wordt gedelete.
   Destructor zorgt ervoor dat er geen memory leak is en dat alles mooi wordt opgeruimt.

   mouseview --> float sinds bijna heel het programma met floats werkt waardoor het makkelijker is.
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
	Vector2f mousePosView;
	//Resources
	Font font;
	//Text
	Text UItextCoinsHP;
	Text UItext2;
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
	vector<Sprite> enemies;
	Sprite enemy;          
	Texture enemyTexture;
	Sprite background;
	Texture backgroundTexture;
	//Private Functions
	void initvariables(); 
	void initwindow();
	void initfonts();
	void inittext();
	void initbackground();
	void initenemies();
	

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
	void updateText();
	void updateEnemies();
	void update();

	void renderText(RenderTarget& target);
	void renderbackground(RenderTarget& target);
	void renderEnemies(RenderTarget& target);
	void render();
};

