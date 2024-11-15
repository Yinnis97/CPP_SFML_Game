#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;


class Highscores
{
private:
    vector<unsigned> highscores;
    const string highscoreFile = "Resources/highscores.txt";
    int maxHighscores;
    bool ScoreAdded;

public:
    Highscores() : ScoreAdded(false), maxHighscores(15)
    {
        this->loadHighscores();
    }
    ~Highscores();
    bool GetScoreAdded();
    void SetScoreAdded(bool Added);
    void loadHighscores();
    void saveHighscores();
    void addHighscore(unsigned coins);
    void updatehighscores(unsigned coins);

    const vector<unsigned>& getHighscores() const;
};

//Eerst de scores laden zodat we de oude scores krijgen anders reseten we telkens keer.