#include "Game.h"

void Game::initvariables()
{
    this->window = nullptr;
    this->coins = 0;
    this->enemyspawntimermax = 10.f;
    this->enemyspawntimer = this->enemyspawntimermax;
    this->maxenemies = 15;
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


//Constructors,Destructors

Game::Game()
{
    this->initvariables();
    this->initwindow();
    this->initbackground();
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

void Game::spawnEntity(RenderWindow& window)
{
    int type = rand() % 2;
    switch (type)
    {
    case 0:
        entities.push_back(new Enemy(window,'E'));
        break;
    case 1:
        //entities.push_back(new Friend(window,'F'));
        entities.push_back(new Enemy(window,'E'));
        break;
    default:
        cerr << "Error Spawn Entity.\n";
        break;
    }
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
    if (this->entities.size() < this->maxenemies)
    {
        if (this->enemyspawntimer >= this->enemyspawntimermax)
        {
            this->spawnEntity(*this->window);
            this->enemyspawntimer = 0.f;
        }
        else
        {
            this->enemyspawntimer += 1.f;
        }
    }
    //Movement van enemies. Blijft elke enemy naar onder verplaatsen elke frame.
    for (int i = 0; i < this->entities.size(); i++)
    {
        this->entities[i]->sprite.move(0.f, this->MoveSpeed);

        //checken of de enemy buiten het scherm is.
        if (this->entities[i]->sprite.getPosition().y > this->window->getSize().y)
        {
            this->entities.erase(this->entities.begin() + i);
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
            for (int i = 0; i < this->entities.size() && deleted == false; i++)
            {
                //contains checkt of de muis binnen de bounds van de enemy is.
                if (this->entities[i]->sprite.getGlobalBounds().contains(this->mousePosView))
                {
                    //Krijg coins
                    if (this->entities[i]->sprite.getScale() == Vector2f(1.0f, 1.0f))
                    {
                        if (this->entities[i]->GetID() == 'E')
                        {
                            this->coins += 3;
                        }
                        else if (this->entities[i]->GetID() == 'F')
                        {
                            if (this->coins >= 1)
                            {
                                this->coins -= 1;
                            }
                        }
                    }
                    else if (this->entities[i]->sprite.getScale() == Vector2f(2.0f, 2.0f))
                    {
                        if (this->entities[i]->GetID() == 'E')
                        {
                            this->coins += 2;
                        }
                        else if (this->entities[i]->GetID() == 'F')
                        {
                            if (this->coins >= 2)
                            {
                                this->coins -= 2;
                            }
                        }
                    }
                    else if (this->entities[i]->sprite.getScale() == Vector2f(3.0f, 3.0f))
                    {
                        if (this->entities[i]->GetID() == 'E')
                        {
                            this->coins += 1;
                        }
                        else if (this->entities[i]->GetID() == 'F')
                        {
                            if (this->coins >= 3)
                            {
                                this->coins -= 3;
                            }
                        }
                    }

                    //Verwijder Enemy
                    deleted = true;
                    this->entities.erase(this->entities.begin() + i);
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
        this->highscores.SetScoreAdded(false);
    }
    else
    {
        //Deleting all enemies 
        for (int i = 0; i < this->entities.size(); i++)
        {
            this->entities.erase(this->entities.begin() + i);
        }
        //Update de highscores wnr endgame.
        this->highscores.updatehighscores(coins);
        //Update restart/Quit screen wnr endgame.
        this->buttons.updateRestart(this->health, this->coins, this->mousePosView, this->endgame, *this->window);
        this->buttons.updateQuit(this->Boolquit, this->mousePosView, this->endgame, *this->window);
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
    for (int i = 0; i < this->entities.size(); i++)
    {
        target.draw(this->entities[i]->sprite);
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
