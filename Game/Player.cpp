#include "Player.h"


Player::Player()
{
	this->SetAllToDefault();
}


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
	return this->BossesKilled;
}

const int Player::GetEnemiesKilled()
{
	return this->EnemiesKilled;
}

const int Player::GetFriendsKilled()
{
	return this->FriendsKilled;
}


void Player::AddHealth(int value)
{
	this->Health = this->Health + value;
}

void Player::MinHealth(int value)
{
	this->Health = this->Health - value;
}

void Player::AddCoins(int value)
{
	this->Coins = this->Coins + value;
}

void Player::AddBossesKilled(int value)
{
	this->BossesKilled = this->BossesKilled + value;
}

void Player::AddEnemiesKilled(int value)
{
	this->EnemiesKilled = this->EnemiesKilled + value;
}

void Player::AddFriendsKilled(int value)
{
	this->FriendsKilled = this->FriendsKilled + value;
}


//Set to default value
void Player::SetAllToDefault()
{
	this->Health = 20;
	this->Coins = 0;
	this->BossesKilled = 0;
	this->EnemiesKilled = 0;
	this->FriendsKilled = 0;
}


