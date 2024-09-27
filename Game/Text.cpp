#include "Text.h"

TextClass::TextClass()
{
    this->initfonts();
    this->inittext();
}

TextClass::~TextClass() 
{
   
}

void TextClass::initfonts()
{
    if (!this->font.loadFromFile("Fonts/PixeloidSans.ttf"))
    {
        cerr << "Error: Kon Font Niet Laden!" << endl;
    }
}


void TextClass::inittext()
{
    //Coins And HP
    this->UItextCoinsHP.setFont(this->font);
    this->UItextCoinsHP.setCharacterSize(24);
    this->UItextCoinsHP.setFillColor(Color::Yellow);
    this->UItextCoinsHP.setString("");
    //Rechts
    this->UItext2.setFont(this->font);
    this->UItext2.setCharacterSize(24);
    this->UItext2.setFillColor(Color::Yellow);
    this->UItext2.setString("");
    //Restart
    this->UIRestart.setFont(this->font);
    this->UIRestart.setCharacterSize(50);
    this->UIRestart.setFillColor(Color::Yellow);
    this->UIRestart.setString("");
    //Game Over
    this->UIGameOver.setFont(this->font);
    this->UIGameOver.setCharacterSize(100);
    this->UIGameOver.setFillColor(Color::Yellow);
    this->UIGameOver.setString("");
}

void TextClass::updateText(unsigned coins, int health, bool endgame, const RenderWindow& window)
{
    if (!endgame)
    {
        stringstream ss1, ss2;
        //Coins And HP
        ss1 << "Coins: " << coins << endl << "Health: " << health << endl;
        this->UItextCoinsHP.setString(ss1.str());
        this->UItextCoinsHP.setPosition(10.f, 10.f);

        // PRE-ALPHA
        ss2 << "PRE-ALPHA" << endl;
        this->UItext2.setString(ss2.str());

        FloatRect textBounds = this->UItext2.getLocalBounds();
        float windowWidth = window.getSize().x;
        this->UItext2.setPosition(windowWidth - textBounds.width - 10.f, 10.f);
    }
    else
    {
        float windowWidth = window.getSize().x;
        float windowHeight = window.getSize().y;

        // Last Score
        stringstream ss1;
        ss1 << "Score: " << coins;
        this->UItextCoinsHP.setString(ss1.str());
        this->UItextCoinsHP.setCharacterSize(40);
        this->UItextCoinsHP.setFillColor(Color::Yellow);

        FloatRect textBounds1 = this->UItextCoinsHP.getLocalBounds();
        this->UItextCoinsHP.setPosition((windowWidth - textBounds1.width) / 2, (windowHeight / 2) + 140);

        // Game Over
        this->UIGameOver.setString("Game Over");
        FloatRect textBounds2 = this->UIGameOver.getLocalBounds();
        this->UIGameOver.setPosition((windowWidth - textBounds2.width) / 2, (windowHeight / 2));

        // Restart
        this->UIRestart.setString("Restart");
        FloatRect textBounds3 = this->UIRestart.getLocalBounds();
        this->UIRestart.setPosition((windowWidth - textBounds3.width) / 2, (windowHeight / 2) + 200);
    }
}

void TextClass::renderText(RenderTarget& target)
{
    target.draw(this->UItextCoinsHP);
    target.draw(this->UItext2);
    target.draw(this->UIGameOver);
    target.draw(this->UIRestart);
}