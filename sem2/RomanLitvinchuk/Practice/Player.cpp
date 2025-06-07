#include "Player.h"

int Player::getEnergy() { return energy; }


void Player::setEnergy(int someEnergy) 
{
	if (energy + someEnergy <= 100) { energy += someEnergy; }
	else { energy = 100; }
	if (energy + someEnergy < 0) { energy = 0; }
}

int Player::getMoney() { return money; }

void Player::setMoney(int someMoney) { money += someMoney; }

bool Player::getShovel() { return shovel; }
void Player::setShovel() { shovel = true; }
bool Player::getBrush() { return brush; }
void Player::setBrush() { brush = true; }
bool Player::getPickaxe() { return pickaxe; }
void Player::setPickaxe() { pickaxe = true; }

bool Player::getSB() { return SmallBone; }
bool Player::getCB() { return CommonBone; }
bool Player::getBB() { return BigBone; }
void Player::setSB() { SmallBone = true; }
void Player::setCB() { CommonBone = true; }
void Player::setBB() { BigBone = true; }

bool Player::getRB() { return RareBone; }
bool Player::getEB() { return EpicBone; }
bool Player::getLB() { return LegendaryBone; }
void Player::setRB() { RareBone = true; }
void Player::setEB() { EpicBone = true; }
void Player::setLB() { LegendaryBone = true; }
