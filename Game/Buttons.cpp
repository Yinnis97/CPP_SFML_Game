#include "Buttons.h"

void Buttons::initrestart()
{
    this->Restart.setFillColor(Color::Transparent);
    this->Restart.setOutlineThickness(8.f);
    this->Restart.setOutlineColor(Color::Yellow);
    this->Restart.setSize(Vector2f(220.f, 50.f));

}

Buttons::Buttons()
{
    this->initrestart();
   
}

Buttons::~Buttons()
{

}

void Buttons::updateRestart(int& health, unsigned& coins, vector<Sprite>& enemies, Vector2f mousePosView, bool& mouseHeld, bool& endgame, RenderTarget& target)
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
        if (mouseHeld == false)
        {
            mouseHeld = true;

            if (this->Restart.getGlobalBounds().contains(mousePosView))
            {
                endgame = false;
                health = 20;
                coins = 0;
            }
        }
    }
    else
    {
        mouseHeld = false;
    }
}

void Buttons::renderRestart(RenderTarget& target)
{
    target.draw(Restart);
}
