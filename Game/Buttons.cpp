#include "Buttons.h"

void Buttons::initrestart()
{
    this->Restart.setFillColor(Color::Transparent);
    this->Restart.setOutlineThickness(8.f);
    this->Restart.setOutlineColor(Color::ButtonColor);
    this->Restart.setSize(Vector2f(220.f, 50.f));
    this->mouseHeldRestart = false;
    this->ButtonRestartPressed = false;
    this->ButtonQuitPressed = false;
}

void Buttons::initquit()
{
    this->Quit.setFillColor(Color::Transparent);
    this->Quit.setOutlineThickness(8.f);
    this->Quit.setOutlineColor(Color::ButtonColor);
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

void Buttons::SetButtonRestartPressed(bool set)
{
    this->ButtonRestartPressed = set;
}

bool Buttons::GetButtonRestartPressed()
{
    return this->ButtonRestartPressed;
}

void Buttons::SetButtonQuitPressed(bool set)
{
    this->ButtonQuitPressed = set;
}

bool Buttons::GetButtonQuitPressed()
{
    return this->ButtonQuitPressed;
}

void Buttons::updateRestart(Vector2f mousePosView, RenderTarget& target)
{
    float windowWidth = target.getSize().x;
    float windowHeight = target.getSize().y;
    this->Restart.setPosition((windowWidth - this->Restart.getSize().x) / 2, (windowHeight / 2) + 165); 


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
            
            this->SetButtonRestartPressed(true);
        }
        this->mouseHeldRestart = false;
        this->Restart.setOutlineColor(Color::ButtonColor);
    }
}

void Buttons::updateQuit(Vector2f mousePosView, RenderTarget& target)
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
        }
    }

    else 
    {
        if (this->mouseHeldQuit && this->Quit.getGlobalBounds().contains(mousePosView))
        {
            this->SetButtonQuitPressed(true);
        }
        this->mouseHeldQuit = false;
        this->Quit.setOutlineColor(Color::ButtonColor);
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
