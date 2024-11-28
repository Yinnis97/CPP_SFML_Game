#pragma once
#include <iostream>
#include <sstream> 
#include <string>  
#include <SFML/Graphics.hpp>
#include "Highscores.h"

#define TextColor Blue

using namespace std;
using namespace sf;

class TextClass 
{
private:
	
	Font font;

	Text UIQuit;
	Text UIRestart;
	Text UItextCoinsHP;
	Text UIVersion;
	Text UIGameOver;
	Text UIHighscores;
	Text EnemyClicked;
	Text EnemiesKilled;
	Text BossesKilled;
	Text FriendsKilled;

public:
	TextClass();
	virtual ~TextClass();

	void initfonts();
	void inittext();
	void updateClickText(const RenderWindow& window,Vector2f mousePosView);
	void updatePlayerStatsText(int coins, int health, int EnemiesKilled, int BossesKilled, int FriendsKilled, bool endgame, const RenderWindow& window);
	void updateText(int coins, int health, bool endgame, const RenderWindow& window, const Highscores& highscores);
	void renderText(RenderTarget& target);

};
