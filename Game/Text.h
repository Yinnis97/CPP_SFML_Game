#pragma once
#include <iostream>
#include <sstream> 
#include <string>  
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class TextClass 
{
private:
	
	Font font;

	Text UIRestart;
	Text UItextCoinsHP;
	Text UItext2;
	Text UIGameOver;

public:
	TextClass();
	virtual ~TextClass();

	void initfonts();
	void inittext();
	void updateText(unsigned coins, int health, bool endgame, const RenderWindow& window);
	void renderText(RenderTarget& target);

};
