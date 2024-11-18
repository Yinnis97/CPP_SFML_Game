#pragma once
class Player
{
private:

	int coins;
	int health;
	int EnemiesKilled;
	int BossesKiled;
	int FriendsKilled;

public:

	const int GetCoins();
	const int GetHealth();

	const int GetBossesKilled();
	const int GetEnemiesKilled();
	const int GetFriendsKilled();

	void SetHealth(int value);
	void SetCoins(int value);
	void SetBossesKilled(int value);
	void SetEnemiesKilled(int value);
	void SetFriendsKilled(int value);

};

