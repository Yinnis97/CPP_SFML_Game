#include "Buttons.h"

void Buttons::initrestart()
{
    this->Restart.setFillColor(Color::Transparent);
    this->Restart.setOutlineThickness(8.f);
    this->Restart.setOutlineColor(Color::Yellow);
    this->Restart.setSize(Vector2f(220.f, 50.f));
    this->mouseHeldRestart = false;
}

void Buttons::initquit()
{
    this->Quit.setFillColor(Color::Transparent);
    this->Quit.setOutlineThickness(8.f);
    this->Quit.setOutlineColor(Color::Yellow);
    this->Quit.setSize(Vector2f(220.f, 50.f));
    this->mouseHeldQuit = false;
}

Buttons::Buttons()
{
    this->initrestart();
    this->initquit();
}

Buttons::~Buttons()
{

}

void Buttons::updateRestart(int& health, unsigned& coins, vector<Sprite>& enemies, Vector2f mousePosView,  bool& endgame, RenderTarget& target)
{
    float windowWidth = target.getSize().x;
    float windowHeight = target.getSize().y;
    this->Restart.setPosition((windowWidth - this->Restart.getSize().x) / 2, (windowHeight / 2) + 165); 

    //Deleting all enemies 
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies.erase(enemies.begin() + i);
    }

    if (Mouse::isButtonPressed(Mouse::Left))
    {
        //Druk en mouseheld wordt true 
        if (!this->mouseHeldRestart && this->Restart.getGlobalBounds().contains(mousePosView))
        {
            this->mouseHeldRestart = true;
            this->Restart.setOutlineColor(Color::Green);
         
        }
    }

    else //activeert wnr je los laat
    {
        //omdat mouseheld true is van de vorige frame zal deze activeren bij de frame ne de frame dat de muis is ingedrukt.
        if (this->mouseHeldRestart && this->Restart.getGlobalBounds().contains(mousePosView))
        {
            endgame = false;
            health = 20;
            coins = 0;
            //std::cout << "Restart button clicked.\n"; //debug
        }
        this->mouseHeldRestart = false;
        this->Restart.setOutlineColor(Color::Yellow);
    }
}

void Buttons::updateQuit(bool& Boolquit, Vector2f mousePosView,  bool& endgame, RenderTarget& target)
{
    
    float windowWidth = target.getSize().x;
    float windowHeight = target.getSize().y;
    this->Quit.setPosition((windowWidth - this->Quit.getSize().x) / 2, (windowHeight / 2) + 242); 

    if (Mouse::isButtonPressed(Mouse::Left))
    {
        if (!this->mouseHeldQuit && this->Quit.getGlobalBounds().contains(mousePosView))
        {
            this->mouseHeldQuit = true;
            this->Quit.setOutlineColor(Color::Green);
            //cout << "Quit mouseheld is true.\n"; //debug
        }
    }

    else 
    {
        if (this->mouseHeldQuit && this->Quit.getGlobalBounds().contains(mousePosView))
        {
            Boolquit = true;
            //std::cout << "Quit button clicked.\n"; //debug 
        }
        this->mouseHeldQuit = false;
        this->Quit.setOutlineColor(Color::Yellow);
    }
}

void Buttons::renderQuit(RenderTarget& target)
{
    target.draw(Quit);
}

void Buttons::renderRestart(RenderTarget& target)
{
    target.draw(Restart);
}
