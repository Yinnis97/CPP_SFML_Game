#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;


class Highscores
{
private:
    vector<int> highscores;
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
    void addHighscore(int coins);
    void updatehighscores(int coins);

    const vector<int>& getHighscores() const;
};

//Eerst de scores laden zodat we de oude scores krijgen anders reseten we telkens keer.