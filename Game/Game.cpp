#include "Game.h"

void Game::initvariables()
{
	this->window = nullptr;
    this->coins = 0;
    this->enemyspawntimermax = 10.f;
    this->enemyspawntimer = this->enemyspawntimermax;
    this->maxenemies = 10;
    this->mouseHeld = false;
    this->health = 20;
    this->MoveSpeed = 5.0f;
    this->endgame = false;
}

void Game::initwindow()
{
	this->videomode = VideoMode::getDesktopMode();
	this->window = new RenderWindow (this->videomode, "Game V1.0", Style::Fullscreen);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(true);
}

void Game::initfonts()
{
    if(!this->font.loadFromFile("Fonts/PixeloidSans.ttf"))
    {
        cerr << "Error: Kon Font Niet Laden!" << endl;
    }
}

void Game::inittext()
{
    //Links
    this->UItextCoinsHP.setFont(this->font);
    this->UItextCoinsHP.setCharacterSize(24);
    this->UItextCoinsHP.setFillColor(Color::Yellow);
    this->UItextCoinsHP.setString("NONE");
    //Rechts
    this->UItext2.setFont(this->font);
    this->UItext2.setCharacterSize(24);
    this->UItext2.setFillColor(Color::Yellow);
    this->UItext2.setString("NONE");
}

void Game::initbackground()
{
    if (!this->backgroundTexture.loadFromFile("Textures/background.png"))
    {
        cerr << "Error: Kon Background Texture Niet Laden!" << endl;
    }
    this->background.setTexture(this->backgroundTexture);

    float X = static_cast<float>(this->window->getSize().x) / this->backgroundTexture.getSize().x;
    float Y = static_cast<float>(this->window->getSize().y) / this->backgroundTexture.getSize().y;
    this->background.setScale(X,Y);    
}

void Game::initenemies()
{
    if (!this->enemyTexture.loadFromFile("Textures/Enemy.png"))
    {
        cerr << "Error: Kon Enemy Texture Niet Laden!" << endl;
    }
    this->enemy.setTexture(this->enemyTexture);
    this->enemy.setScale(2.0f, 2.0f);
}

//Constructors // Destructors

Game::Game()
{
	this->initvariables();
	this->initwindow();
    this->initfonts();
    this->inittext();
    this->initbackground();
    this->initenemies();
}

Game::~Game()
{
	delete this->window;
}

//Accessors

const bool Game::GameRunning() const
{
	return this->window->isOpen();
}

const bool Game::getendgame() const
{
    return this->endgame;
}


//Functions 

void Game::spawnEnemy()
{
    //Zet random positie voor de enemy.
    //Positie wordt bepaald door de grote van het scherm min de breedte van de enemy (zodat hij binnen het scherm spawnt.
    //we moete static int cast omdat rand een int wil.
    //we moete static float cast omdat setPosition een float vraagt.
   
    int type = rand() % 3;
    switch (type)
    {
    case 0:
        this->enemy.setScale(1.0f, 1.0f);
        break;
    case 1:
        this->enemy.setScale(2.0f, 2.0f);
        break;
    case 2:
        this->enemy.setScale(3.0f, 3.0f);
        break;

    default:
        this->enemy.setScale(2.0f, 2.0f);
        break;
    }
    
    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getGlobalBounds().width)),
        0.f
    );
    //spawn enemy
    this->enemies.push_back(this->enemy);
}

void Game::pollEvents()
{
    //checking for events
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case Event::Closed:
             this->window->close();
             break;
        case Event::KeyPressed:
            if (this->ev.key.code == Keyboard::Escape)
            {
             this->window->close();
            }
            break;

        }
    }
}

void Game::updateMousePos()
{
    //er wordt bijna altijd gewerkt met view omdat we dan met een float kunnen werken.
    //zet onze cursor coord om naar een float vector2 zodat we de coordinaten hebben van onze muis.
    this->mousePosWindow = Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateText()
{
    if (this->getendgame() == false)
    {
        stringstream ss1, ss2;
        //Left Side Text
        ss1 << "Coins: " << this->coins << endl
            << "Health: " << this->health << endl;
        this->UItextCoinsHP.setString(ss1.str());
        this->UItextCoinsHP.setPosition(10.f, 10.f);

        //Right Side Text
        ss2 << "PRE-ALPHA" << endl;
        this->UItext2.setString(ss2.str());
        FloatRect textBounds = this->UItext2.getLocalBounds(); //Grote van text 
        float windowWidth = this->window->getSize().x;         //grote van scherm/window                
        this->UItext2.setPosition(windowWidth - textBounds.width - 10.f, 10.f);
    }
    else
    {
        float windowWidth = this->window->getSize().x;         //grote van scherm/window   
        float windowHeight = this->window->getSize().y;
        
        //Last Score
        stringstream ss1;
        ss1 << "Score: " << this->coins;
        this->UItextCoinsHP.setString(ss1.str());
        this->UItextCoinsHP.setCharacterSize(40);
        this->UItextCoinsHP.setFillColor(Color::Yellow);

        FloatRect textBounds1 = this->UItextCoinsHP.getLocalBounds(); //Grote van text
        this->UItextCoinsHP.setPosition( (windowWidth - textBounds1.width) / 2, (windowHeight / 2) + 140 );
        
        //Game Over
        this->UItext2.setString("Game Over");
        this->UItext2.setCharacterSize(100);
        this->UItext2.setFillColor(Color::Yellow);

        FloatRect textBounds2 = this->UItext2.getLocalBounds(); //Grote van text 
        this->UItext2.setPosition( (windowWidth - textBounds2.width) / 2, (windowHeight / 2) );
    }

    

}

void Game::updateEnemies()
{
    //Update de timer van enemie spawn 
    if (this->enemies.size() < this->maxenemies)
    {
        if (this->enemyspawntimer >= this->enemyspawntimermax)
        {
            this->spawnEnemy();
            this->enemyspawntimer = 0.f;
        }
        else
        {
            this->enemyspawntimer += 1.f;
        }
    }
    //Movement van enemies. Blijft elke enemy naar onder verplaatsen elke frame.
    for (int i = 0; i < this->enemies.size(); i++)
    {
        this->enemies[i].move(0.f, this->MoveSpeed);

        //checken of de enemy buiten het scherm is.
        if (this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
            //cout << health << endl;
        }
    }

    //checken of er op de enemy geklikt is.
    if (Mouse::isButtonPressed(Mouse::Left))
    {
        if (this->mouseHeld == false)
        {
            this->mouseHeld = true;
            bool deleted = false;
            for (int i = 0; i < this->enemies.size() && deleted == false; i++)
            {
                //contains checkt of de muis binnen de bounds van de enemy is.
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
                {
                    //Krijg coins
                    if (this->enemies[i].getScale() == Vector2f(1.0f, 1.0f))
                    {
                        this->coins += 3;
                        cout << coins << endl;
                    }
                    else if (this->enemies[i].getScale() == Vector2f(2.0f, 2.0f))
                    {
                        this->coins += 2;
                        cout << coins << endl;
                    }
                    else if (this->enemies[i].getScale() == Vector2f(3.0f, 3.0f))
                    {
                        this->coins += 1;
                        cout << coins << endl;
                    }

                    //Verwijder Enemy
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);
                }
            }
        }

    }
    else
    {
        this->mouseHeld = false;
    }
}

void Game::update()
{
    this->pollEvents();
    this->updateMousePos();
    this->updateText();
    if (this->getendgame() == false)
    {
        this->updateEnemies();
    }
    
    
    //End game wnr health 0 of lager is.
    if (this->health <= 0)
    {
        this->endgame = true;
    }

}

void Game::renderText(RenderTarget& target)
{
    target.draw(this->UItextCoinsHP);
    target.draw(this->UItext2);
}

void Game::renderbackground(RenderTarget& target)
{
    target.draw(background);
}

void Game::renderEnemies(RenderTarget& target)
{
    //render elke enemy. Iterators/for each loops gaan over elk element van een vector. 
    //auto : compiler kiest automatisch het juiste type.
    for (auto& e : this->enemies)
    {
        target.draw(e);
    }
}

void Game::render()
{ 
    //1. Clear Old frame 2. Render Objects 3. Display New Frame
    this->window->clear();
    //Draw Game Objects
    this->renderbackground(*this->window);
    this->renderText(*this->window);

    if (this->getendgame() == false)
    {
        this->renderEnemies(*this->window);
    }
   
   
    this->window->display();
}
