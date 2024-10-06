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
    this->Boolquit = false;
    this->Fullscreen = true;
}

void Game::initwindow()
{
    this->videomode = VideoMode::getDesktopMode();
    this->window = new RenderWindow(this->videomode, "Game V1.0", Style::Fullscreen);
    this->window->setFramerateLimit(60);
    this->window->setVerticalSyncEnabled(true);
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
    this->background.setScale(X, Y);
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

void Game::toggleFullscreen()
{
    delete this->window;
    this->Fullscreen = !this->Fullscreen;

    if (this->Fullscreen)
    {
        this->window = new RenderWindow(this->videomode, "Game V1.0", Style::Fullscreen);
    }
    else
    {
        this->window = new RenderWindow(this->videomode, "Game V1.0", Style::Close | Style::Resize);
    }

    this->window->setFramerateLimit(60);
    this->window->setVerticalSyncEnabled(true);
}

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
    //checking voor events
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

            if (this->ev.key.code == Keyboard::LAlt)
            {
                this->toggleFullscreen();
            }
            break;

        }

    }

    if (Boolquit)
    {
        this->window->close();
    }
}

void Game::updateMousePos()
{
    //er wordt bijna altijd gewerkt met view omdat we dan met een float kunnen werken.
    //zet onze cursor coord om naar een float vector2 zodat we de coordinaten hebben van onze muis.
    this->mousePosWindow = Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}


void Game::updateEnemies()
{
    //Update de timer van enemy spawn 
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
    this->text.updateText(this->coins, this->health, this->endgame, *this->window, highscores);

    if (this->getendgame() == false)
    {
        //Stop updating enemies wnr endgame.
        this->updateEnemies();
        //Zet de Scoreadded terug op false wnr je het spell restart.
        this->highscores.ScoreAdded = false;
    }
    else
    {
        //Update de highscores wnr endgame.
        this->highscores.updatehighscores(coins);
        //Update restart/Quit screen wnr endgame.
        this->buttons.updateRestart(health, coins, enemies, mousePosView, endgame, *this->window);
        this->buttons.updateQuit(Boolquit, mousePosView, endgame, *this->window);
    }

    //End game wnr health 0 of lager is.
    if (this->health <= 0)
    {
        this->endgame = true;
    }

}


void Game::renderbackground(RenderTarget& target)
{
    target.draw(background);
}

void Game::renderEnemies(RenderTarget& target)
{
    //render elke enemy. Iterators/for each loops gaan over elk element van een vector. 
    for (auto& e : this->enemies)
    {
        target.draw(e);
    }
}

void Game::render()
{
    //1. Clear Old frame 2. Render Objects 3. Display New Frame
    this->window->clear();
  
    this->renderbackground(*this->window);
    this->text.renderText(*this->window);

    
    if (this->getendgame() == false) 
    {
        //Stop met enemies renderen wnr endgame.
        this->renderEnemies(*this->window);
    }
    else
    {
        //Laat restart/quit scherm zien wnr endgame.
        this->buttons.renderRestart(*this->window);
        this->buttons.renderQuit(*this->window);
    }


    this->window->display();
}
