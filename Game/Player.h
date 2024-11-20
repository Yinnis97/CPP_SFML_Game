#pragma once
class Player
{
private:

	int Coins;
	int Health;
	int EnemiesKilled;
	int BossesKilled;
	int FriendsKilled;

public:

	Player();

	//Getters
	const int GetCoins();
	const int GetHealth();
	const int GetBossesKilled();
	const int GetEnemiesKilled();
	const int GetFriendsKilled();

	//Setters
	void AddHealth(int value);
	void MinHealth(int value);
	void AddCoins(int value);
	void AddBossesKilled(int value);
	void AddEnemiesKilled(int value);
	void AddFriendsKilled(int value);

	//Set everything to default value
	void SetAllToDefault();
	

};

