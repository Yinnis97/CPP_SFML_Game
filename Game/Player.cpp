#include "Player.h"


Player::Player()
{
	this->SetAllToDefault();
}

//Getters
const int Player::GetCoins()
{
	return this->Coins;
}

const int Player::GetHealth()
{
	return this->Health;
}

const int Player::GetBossesKilled()
{
	return this->BossesKiled;
}

const int Player::GetEnemiesKilled()
{
	return this->EnemiesKilled;
}

const int Player::GetFriendsKilled()
{
	return this->FriendsKilled;
}


//Setters
void Player::SetHealth(int value)
{
	this->Health = this->Health - value;
}

void Player::SetCoins(int value)
{
	this->Coins = this->Coins + value;
}

void Player::SetBossesKilled(int value)
{
	this->BossesKiled = this->BossesKiled + value;
}

void Player::SetEnemiesKilled(int value)
{
	this->EnemiesKilled = this->EnemiesKilled + value;
}

void Player::SetFriendsKilled(int value)
{
	this->FriendsKilled = this->FriendsKilled + value;
}


//Set to default value
void Player::SetAllToDefault()
{
	this->Health = 20;
	this->Coins = 0;
	this->BossesKiled = 0;
	this->EnemiesKilled = 0;
	this->FriendsKilled = 0;
}


