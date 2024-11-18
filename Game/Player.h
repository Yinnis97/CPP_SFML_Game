#pragma once
class Player
{
private:

	int Coins;
	int Health;
	int EnemiesKilled;
	int BossesKiled;
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
	void SetHealth(int value);
	void SetCoins(int value);
	void SetBossesKilled(int value);
	void SetEnemiesKilled(int value);
	void SetFriendsKilled(int value);

	//Set everything to default value
	void SetAllToDefault();
	

};

