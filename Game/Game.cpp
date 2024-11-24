#include "Game.h"

void Game::initvariables()
{
    this->window = nullptr;
    this->enemyspawntimermax = 10.f;
    this->enemyspawntimer = this->enemyspawntimermax;
    this->maxenemies = 15;
    this->mouseHeld = false;
    this->endgame = false;
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
    this->clock.restart();
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

const Vector2f Game::GetupdateMousePos()
{
    //er wordt bijna altijd gewerkt met view omdat we dan met een float kunnen werken.
    //zet onze cursor coord om naar een float vector2 zodat we de coordinaten hebben van onze muis.
    this->mousePosWindow = Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);

    return this->mousePosView;
}

const bool Game::GetBossTimeInterval()
{
    if (this->clock.getElapsedTime().asSeconds() >= 20 && this->clock.getElapsedTime().asSeconds() <= 21)
    {
        return true;
    }
    return false;
}

//Functions 

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
}

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
    if (this->BossActive == false && this->GetBossTimeInterval())
    {
        //Deleting all enemies 
        this->deleteAllEnemies();
        
        //Spawn boss
        entities.push_back(new Boss(*this->window, 'B', 10, 5.0f));
        this->BossActive = true;
    }
    else if (this->BossActive == false)
    {
        int RandomNum = rand() % 100;

        if (RandomNum < 45)
        {
            entities.push_back(new Enemy(*this->window, 'E', 1, 5.0f));
        }
        else if (RandomNum < 90)
        {
            entities.push_back(new Friend(*this->window, 'F', 1, 5.0f));
        }
        else
        {
            entities.push_back(new Heart(*this->window, 'H', 1, 5.0f));
        }
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
                this->player.AddCoins(-1);
                if (this->player.GetCoins() < 0)
                {
                    this->player.AddCoins(-this->player.GetCoins());
                }
                this->entities.erase(this->entities.begin() + i);
                this->deleted = true;
                this->player.AddFriendsKilled(1);
            }
        }
        else if (this->entities[i]->sprite.getScale() == Vector2f(2.0f, 2.0f))
        {
            this->entities[i]->MinHealth(1);
            if (this->entities[i]->GetHealth() <= 0)
            {
                this->player.AddCoins(-2);
                if (this->player.GetCoins() < 0)
                {
                    this->player.AddCoins(-this->player.GetCoins());
                }
                this->entities.erase(this->entities.begin() + i);
                this->deleted = true;
                this->player.AddFriendsKilled(1);
            }

        }
        else if (this->entities[i]->sprite.getScale() == Vector2f(3.0f, 3.0f))
        {
            this->entities[i]->MinHealth(1);
            if (this->entities[i]->GetHealth() <= 0)
            {
                this->player.AddCoins(-3);
                if (this->player.GetCoins() < 0)
                {
                    this->player.AddCoins(-this->player.GetCoins());
                }
                this->entities.erase(this->entities.begin() + i);
                this->deleted = true;
                this->player.AddFriendsKilled(1);
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
                this->player.AddCoins(3);
                this->entities.erase(this->entities.begin() + i);
                this->deleted = true;
                this->player.AddEnemiesKilled(1);
            }
        }
        else if (this->entities[i]->sprite.getScale() == Vector2f(2.0f, 2.0f))
        {
            this->entities[i]->MinHealth(2);
            if (this->entities[i]->GetHealth() <= 0)
            {
                this->player.AddCoins(3);
                this->entities.erase(this->entities.begin() + i);
                this->deleted = true;
                this->player.AddEnemiesKilled(1);
            }
        }
        else if (this->entities[i]->sprite.getScale() == Vector2f(3.0f, 3.0f))
        {
            this->entities[i]->MinHealth(1);
            if (this->entities[i]->GetHealth() <= 0)
            {
                this->player.AddCoins(1);
                this->entities.erase(this->entities.begin() + i);
                this->deleted = true;
                this->player.AddEnemiesKilled(1);
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
            this->player.AddBossesKilled(1);
            this->player.AddCoins(10);
            this->entities.erase(this->entities.begin() + i);
            this->deleted = true;
            this->BossActive = false;
            this->clock.restart();
        }
    }
}

void Game::checkHeart(int i)
{
    if (this->entities[i]->GetID() == 'H')
    {
        this->entities[i]->MinHealth(1);
        if (this->entities[i]->GetHealth() <= 0)
        {
            this->player.AddHealth(1);
            this->entities.erase(this->entities.begin() + i);
            this->deleted = true;
        }
    }
}

void Game::deleteAllEnemies()
{
    for (int i = 0; i < this->entities.size(); i++)
    {
        this->entities.erase(this->entities.begin() + i);
    }

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
        //Move enemy 
        this->entities[i]->sprite.move(0.f, this->entities[i]->GetSpeed());
  
        //checken of de enemy buiten het scherm is.
        if (this->entities[i]->sprite.getPosition().y > this->window->getSize().y)
        {
            if (this->entities[i]->GetID() == 'E')
            {
                this->player.MinHealth(1);
            }
            else if (this->entities[i]->GetID() == 'B')
            {
                this->player.MinHealth(10);
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
                    if (this->deleted == false)
                    {
                        this->checkHeart(i);
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

void Game::update()
{
    this->pollEvents();
    this->GetupdateMousePos();
    this->text.updatePlayerStatsText(this->player.GetCoins(), this->player.GetHealth(), this->player.GetEnemiesKilled(), this->player.GetBossesKilled(), this->player.GetFriendsKilled(), this->endgame, *this->window);
    this->text.updateText(this->player.GetCoins(), this->player.GetHealth(), this->endgame, *this->window, highscores);
    
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
        this->highscores.updatehighscores(this->player.GetCoins());

        //Restart Button
        this->buttons.updateRestart(this->GetupdateMousePos(), *this->window);
        if (this->buttons.GetButtonRestartPressed())
        {
            this->endgame = false;
            this->buttons.SetButtonRestartPressed(false);
            this->player.SetAllToDefault();
            this->clock.restart();
        }

        //Quit Button
        this->buttons.updateQuit(this->GetupdateMousePos(), *this->window);
        if (this->buttons.GetButtonQuitPressed())
        {
            this->window->close();
        }
    }

    //End game wnr health 0 of lager is.
    if (this->player.GetHealth() <= 0)
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
