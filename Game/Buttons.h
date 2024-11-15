#pragma once
#include <iostream>
#include <sstream> 
#include <string>  
#include "SFML\Graphics.hpp"
using namespace std;
using namespace sf;

class Buttons
{
	
private:
	RectangleShape Restart;
	RectangleShape Quit;
	
	bool mouseHeldRestart;
	bool mouseHeldQuit;

	void initrestart();
	void initquit();

public:
	Buttons();
	virtual ~Buttons();

	void updateRestart(int& health, unsigned& coins, Vector2f mousePosView, bool& endgame, RenderTarget& target);
	void updateQuit(bool& Boolquit, Vector2f mousePosView, bool& endgame, RenderTarget& target);

	void renderQuit(RenderTarget& target);
	void renderRestart(RenderTarget& target);

};

