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
    this->UIVersion.setFont(this->font);
    this->UIVersion.setCharacterSize(24);
    this->UIVersion.setFillColor(Color::Yellow);
    this->UIVersion.setString("");
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
    //Quit
    this->UIQuit.setFont(this->font);
    this->UIQuit.setCharacterSize(50);
    this->UIQuit.setFillColor(Color::Yellow);
    this->UIQuit.setString("");
    //Highscores
    this->UIHighscores.setFont(this->font);
    this->UIHighscores.setCharacterSize(50);
    this->UIHighscores.setFillColor(Color::Yellow);
    this->UIHighscores.setString("");
    //Enemy clicked
    this->EnemyClicked.setFont(this->font);
    this->EnemyClicked.setCharacterSize(20);
    this->EnemyClicked.setFillColor(Color::Yellow);
    this->EnemyClicked.setString("");

}

void TextClass::updateClickText(const RenderWindow& window, Vector2f mousePosView)
{

    this->EnemyClicked.setPosition(mousePosView.x-30,mousePosView.y-20);
    this->EnemyClicked.setString("-1");

}

void TextClass::updateText(unsigned coins, int health, bool endgame, const RenderWindow& window, const Highscores& highscores, Vector2f mousePosView)
{
    if (!endgame)
    {
        stringstream ss1, ss2;
        //Coins And HP
        ss1 << "Coins: " << coins << endl << "Health: " << health << endl;
        this->UItextCoinsHP.setCharacterSize(24);
        this->UItextCoinsHP.setString(ss1.str());
        this->UItextCoinsHP.setPosition(10.f, 10.f);

        //PRE-ALPHA
        this->UIVersion.setString("PRE-ALPHA");
        FloatRect textBounds = this->UIVersion.getLocalBounds();
        float windowWidth = window.getSize().x;
        this->UIVersion.setPosition(windowWidth - textBounds.width - 10.f, 10.f);

        //Setting strings empty.
        this->UIGameOver.setString("");
        this->UIRestart.setString("");
        this->UIQuit.setString("");
        this->UIHighscores.setString("");

        //Set enemy clicked string back to empty
        this->EnemyClicked.setString("");
    }
    else
    {
        float windowWidth = window.getSize().x;
        float windowHeight = window.getSize().y;

        //Game Over
        this->UIGameOver.setString("Game Over");
        FloatRect textBounds2 = this->UIGameOver.getLocalBounds();
        this->UIGameOver.setPosition((windowWidth - textBounds2.width) / 2, (windowHeight / 2) - 70);

        //Last Score
        stringstream ss1;
        ss1 << "Score: " << coins;
        this->UItextCoinsHP.setString(ss1.str());
        this->UItextCoinsHP.setCharacterSize(40);
        this->UItextCoinsHP.setFillColor(Color::Yellow);

        FloatRect textBounds1 = this->UItextCoinsHP.getLocalBounds();
        this->UItextCoinsHP.setPosition((windowWidth - textBounds1.width) / 2, (windowHeight / 2) + 85);

        //Highscores 
        stringstream ssHighscores;
        ssHighscores << "Highscores:" << endl;
        const auto& highscore = highscores.getHighscores();
        for (int i = 0; i < highscore.size(); ++i)
        {
            ssHighscores << i + 1 << ". " << highscore[i] << endl;
        }
        this->UIHighscores.setString(ssHighscores.str());
        this->UIHighscores.setCharacterSize(30);
        this->UIHighscores.setPosition(10.f, 300.f);

        //Restart
        this->UIRestart.setString("Restart");
        FloatRect textBounds3 = this->UIRestart.getLocalBounds();
        this->UIRestart.setPosition((windowWidth - textBounds3.width) / 2, (windowHeight / 2) + 160);

        //Quit
        this->UIQuit.setString("Quit");
        FloatRect textBounds4 = this->UIQuit.getLocalBounds();
        this->UIQuit.setPosition((windowWidth - textBounds4.width) / 2, (windowHeight / 2) + 237);

    }
}

void TextClass::renderText(RenderTarget& target)
{
    target.draw(this->EnemyClicked);
    target.draw(this->UItextCoinsHP);
    target.draw(this->UIVersion);
    target.draw(this->UIGameOver);
    target.draw(this->UIRestart);
    target.draw(this->UIQuit);
    target.draw(this->UIHighscores);
}