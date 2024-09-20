#include "Game.h"

void Game::initvariables()
{
	this->window = nullptr;
    this->coins = 0;
    this->enemyspawntimermax = 100.f;
    this->enemyspawntimer = this->enemyspawntimermax;
    this->maxenemies = 5;
}

void Game::initwindow()
{
	this->videomode = VideoMode::getDesktopMode();
	this->window = new RenderWindow (this->videomode, "Game V1.0", Style::Fullscreen);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(true);
}

void Game::initenemies()
{
    if (!this->enemyTexture.loadFromFile("Textures/Enemy.png"))
    {
        cerr << "Error: Kon texture niet laden!" << endl;
    }
    this->enemy.setTexture(this->enemyTexture);
    this->enemy.scale(2.f,2.f);
}

//Constructors // Destructors

Game::Game()
{
	this->initvariables();
	this->initwindow();
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


//Functions 

void Game::spawnEnemy()
{
    //Zet random positie voor de enemy.
    //Positie wordt bepaald door de grote van het scherm min de breedte van de enemy (zodat hij binnen het scherm spawnt.
    //we moete static int cast omdat rand een int wil.
    //we moete static float cast omdat setPosition een float vraagt.
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
    this->mousePosWindow = Mouse::getPosition(*this->window);
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
    //Movement van enemies. Blijft ze naar onder plaatsen per frame. Dit is een "for each loop".
    for (auto& e : this->enemies)
    {
        e.move(0.f,5.f);
    }
    //Verwijderd de enemies buiten het scherm.

}

void Game::update()
{
    this->pollEvents();
    this->updateMousePos();
    this->updateEnemies();

}

void Game::renderEnemies()
{
    //render elke enemy.
    for (auto& e : this->enemies)
    {
        this->window->draw(e);
    }
}

void Game::render()
{ 
    //1. Clear Old frame 2. Render Objects 3. Display New Frame

    this->window->clear();

    //Draw Game Objects
    this->renderEnemies();
    this->window->display();
}
