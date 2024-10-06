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
	Text UItext2;
	Text UIGameOver;
	Text UIHighscores;
public:
	TextClass();
	virtual ~TextClass();

	void initfonts();
	void inittext();
	void updateText(unsigned coins, int health, bool endgame, const RenderWindow& window, const Highscores& highscores);
	void renderText(RenderTarget& target);

};
