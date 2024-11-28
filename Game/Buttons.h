#pragma once
#include <iostream>
#include <sstream> 
#include <string>  
#include "SFML\Graphics.hpp"

#define ButtonColor Blue

using namespace std;
using namespace sf;

class Buttons
{
	
private:
	RectangleShape Restart;
	RectangleShape Quit;
	
	bool mouseHeldRestart;
	bool mouseHeldQuit;
	bool ButtonRestartPressed;
	bool ButtonQuitPressed;
	void initrestart();
	void initquit();

public:
	Buttons();
	virtual ~Buttons();

	//Setter & Getters
	void SetButtonRestartPressed(bool set);
	bool GetButtonRestartPressed();
	void SetButtonQuitPressed(bool set);
	bool GetButtonQuitPressed();

	//Update
	void updateRestart(Vector2f mousePosView, RenderTarget& target);
	void updateQuit(Vector2f mousePosView, RenderTarget& target);

	//Render
	void renderQuit(RenderTarget& target);
	void renderRestart(RenderTarget& target);

};

