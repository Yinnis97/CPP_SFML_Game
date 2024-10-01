#pragma once
#include <iostream>
#include <sstream> 
#include <string>  
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Buttons
{
private:
	RectangleShape Restart;
	//RectangleShape Quit;

	void initrestart();

public:
	Buttons();
	virtual ~Buttons();
	void updateRestart(int& health, unsigned& coins, vector<Sprite>& enemies, Vector2f mousePosView, bool& mouseHeld, bool& endgame, RenderTarget& target);
	void renderRestart(RenderTarget& target);

};

