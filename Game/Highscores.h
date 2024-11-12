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
    

    void initHighscores();

public:
    Highscores();
    ~Highscores();
    bool ScoreAdded;
    void loadHighscores();
    void saveHighscores();
    void addHighscore(unsigned coins);
    void updatehighscores(unsigned coins);

    const vector<unsigned>& getHighscores() const;
};

/*
ScoreAdded moet public zijn omdat game.cpp deze moet kunnen veranderen.
maxHighscore is het max aantal high scores dat we laten zien.

*/