#include "Highscores.h"



Highscores::~Highscores()
{
}

bool Highscores::GetScoreAdded()
{
    return this->ScoreAdded;
}

void Highscores::SetScoreAdded(bool Added)
{
    this->ScoreAdded = Added;
}

void Highscores::loadHighscores()
{
    ifstream file(this->highscoreFile);

    if (!file.is_open())
    {
        cerr << "Error: Kon highscores niet laden!" << endl;
        return;
    }

    //Variable voor de scores te lezen van de file,lijn per lijn.
    unsigned score;
    while (file >> score)
    {
        this->highscores.push_back(score);
    }
    file.close();

    //Zorg dat de lijst gesorteerd is (hoogste eerst).
    sort(this->highscores.begin(), this->highscores.end(), greater<unsigned>());
}

void Highscores::saveHighscores()
{
    ofstream file(this->highscoreFile);

    if (!file.is_open())
    {
        cerr << "Error: Kon highscores niet opslaan!" << endl;
        return;
    }

    for (const auto& score : this->highscores)
    {
        file << score << endl;
    }
    file.close();
}

void Highscores::addHighscore(int coins)
{
    if (this->ScoreAdded == false)
    {
        this->highscores.push_back(coins);

        //Worden gesorteerd van hoog naar laag.
        sort(this->highscores.begin(), this->highscores.end(), greater<unsigned>());

        //Houd alleen de top maxHighscores scores bij.
        if (this->highscores.size() > this->maxHighscores)
        {
            this->highscores.pop_back();
        }
        ScoreAdded = true;
    }
   
}

void Highscores::updatehighscores(int coins)
{
    this->addHighscore(coins);
    this->saveHighscores();
}

const std::vector<int>& Highscores::getHighscores() const
{
    return this->highscores;
}
