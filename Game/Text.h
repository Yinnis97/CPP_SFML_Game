#pragma once
#include <iostream>
#include <sstream> 
#include <string>  
#include <SFML/Graphics.hpp>
#include "Highscores.h"
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
public:
	TextClass();
	virtual ~TextClass();

	void initfonts();
	void inittext();
	void updateClickText(const RenderWindow& window,Vector2f mousePosView);
	void updateText(unsigned coins, int health, bool endgame, const RenderWindow& window, const Highscores& highscores, Vector2f mousePosView);
	void renderText(RenderTarget& target);

};
