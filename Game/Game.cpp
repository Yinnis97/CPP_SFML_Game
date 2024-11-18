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
    this->deleted = false;
    this->BossActive = false;
    this->EnemyClicked = false;
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
    clock.restart();
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

void Game::spawnEntity()
{
    if (this->BossActive == false && this->clock.getElapsedTime().asSeconds() >= 20 && this->clock.getElapsedTime().asSeconds() <= 22)
    {
        //Deleting all enemies 
        this->deleteAllEnemies();
        
        //Spawn boss
        entities.push_back(new Boss(*this->window, 'B', 10));
        this->BossActive = true;
    }
    else if (this->BossActive == false)
    {
        int type = rand() % 2;
        switch (type)
        {
        case 0:
            entities.push_back(new Enemy(*this->window, 'E', 1));
            break;
        case 1:
            entities.push_back(new Friend(*this->window, 'F', 1));
            break;
        case 2:
            break;
        default:
            cerr << "Error Spawning Entity.\n";
            break;
        }
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

const Vector2f Game::GetupdateMousePos()
{
    //er wordt bijna altijd gewerkt met view omdat we dan met een float kunnen werken.
    //zet onze cursor coord om naar een float vector2 zodat we de coordinaten hebben van onze muis.
    this->mousePosWindow = Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);

    return this->mousePosView;
}


void Game::updateEnemies()
{
    //Update de timer van enemy spawn 
    if (this->entities.size() < this->maxenemies)
    {
        if (this->enemyspawntimer >= this->enemyspawntimermax)
        {
            this->spawnEntity();
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
            if (this->entities[i]->GetID() == 'E')
            {
                this->health -= 1;
            }
            else if (this->entities[i]->GetID() == 'B')
            {
                this->health -= 10;
                this->BossActive = false;
            }
            this->entities.erase(this->entities.begin() + i);
        }
    }

    //checken of er op de enemy geklikt is.
    if (Mouse::isButtonPressed(Mouse::Left))
    {
        if (this->mouseHeld == false)
        {
            this->mouseHeld = true;
            this->deleted = false;
            for (int i = 0; i < this->entities.size() && this->deleted == false; i++)
            {
                //contains checkt of de muis binnen de bounds van de enemy is.
                if (this->entities[i]->sprite.getGlobalBounds().contains(this->GetupdateMousePos()))
                {
                    this->EnemyClicked = true;

                    if (this->deleted == false)
                    {
                        this->checkBoss(i);
                    }
                    if (this->deleted == false)
                    {
                        this->checkEnemy(i);
                    }
                    if (this->deleted == false)
                    {
                        this->checkFriend(i);
                    }     
                }
            }
        }

    }
    else
    {
        this->mouseHeld = false;
    }
}

void Game::checkFriend(int i)
{
    if (this->entities[i]->GetID() == 'F')
    {
        if (this->entities[i]->sprite.getScale() == Vector2f(1.0f, 1.0f))
        {
            this->entities[i]->MinHealth(1);
            if (this->entities[i]->GetHealth() <= 0)
            {
                if (this->coins >= 1)
                {
                    this->coins -= 1;
                }

                this->entities.erase(this->entities.begin() + i);
                this->deleted = true;
            }
        }
        else if (this->entities[i]->sprite.getScale() == Vector2f(2.0f, 2.0f))
        {
            this->entities[i]->MinHealth(1);
            if (this->entities[i]->GetHealth() <= 0)
            {
                if (this->coins >= 2)
                {
                    this->coins -= 2;
                }

                this->entities.erase(this->entities.begin() + i);
                this->deleted = true;
            }

        }
        else if (this->entities[i]->sprite.getScale() == Vector2f(3.0f, 3.0f))
        {
            this->entities[i]->MinHealth(1);
            if (this->entities[i]->GetHealth() <= 0)
            {
                if (this->coins >= 3)
                {
                    this->coins -= 3;
                }

                this->entities.erase(this->entities.begin() + i);
                this->deleted = true;
            }

        }
    }
}

void Game::checkEnemy(int i)
{
    if (this->entities[i]->GetID() == 'E')
    {
        if (this->entities[i]->sprite.getScale() == Vector2f(1.0f, 1.0f))
        {
            this->entities[i]->MinHealth(1);
            if (this->entities[i]->GetHealth() <= 0)
            {
                this->coins += 3;
                this->entities.erase(this->entities.begin() + i);
                this->deleted = true;
            }
        }
        else if (this->entities[i]->sprite.getScale() == Vector2f(2.0f, 2.0f))
        {
            this->entities[i]->MinHealth(1);
            if (this->entities[i]->GetHealth() <= 0)
            {
                this->coins += 2;
                this->entities.erase(this->entities.begin() + i);
                this->deleted = true;
            }
        }
        else if (this->entities[i]->sprite.getScale() == Vector2f(3.0f, 3.0f))
        {
            this->entities[i]->MinHealth(1);
            if (this->entities[i]->GetHealth() <= 0)
            {
                this->coins += 1;
                this->entities.erase(this->entities.begin() + i);
                this->deleted = true;
            }
        }
    }
}

void Game::checkBoss(int i)
{
    if (this->entities[i]->GetID() == 'B')
    {
        this->entities[i]->MinHealth(1);
        if (this->entities[i]->GetHealth() <= 0)
        {
            this->coins += 10;
            this->entities.erase(this->entities.begin() + i);
            this->deleted = true;
            this->BossActive = false;
        }
    }
}

void Game::deleteAllEnemies()
{
    for (int i = 0; i < this->entities.size(); i++)
    {
        this->entities.erase(this->entities.begin() + i);
        if (i == this->entities.size() - 1)
        {
            cout << "size-1" << endl;
        }
    }
    
}

void Game::update()
{
    this->pollEvents();
    this->GetupdateMousePos();
    this->text.updateText(this->coins, this->health, this->endgame, *this->window, highscores, this->GetupdateMousePos());
    if (this->EnemyClicked)
    {
        this->text.updateClickText(*this->window, this->GetupdateMousePos());
        this->EnemyClicked = false;
    }

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
        this->deleteAllEnemies();
        //Update de highscores wnr endgame.
        this->highscores.updatehighscores(coins);
        //Update restart/Quit screen wnr endgame.
        this->buttons.updateRestart(this->health, this->coins, this->GetupdateMousePos(), this->endgame, *this->window);
        this->buttons.updateQuit(this->Boolquit, this->GetupdateMousePos(), this->endgame, *this->window);
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
    //render elke enemy sprite.
    for (int i = 0; i < this->entities.size(); i++)
    {
        target.draw(this->entities[i]->sprite);
    }
}

void Game::render()
{
    //1. Clear Old frame 2. Render Objects 3. Display New Frame
    //Eerst render background en text als laatste.
    this->window->clear();
  
    this->renderbackground(*this->window);

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

    this->text.renderText(*this->window);

    this->window->display();
}
