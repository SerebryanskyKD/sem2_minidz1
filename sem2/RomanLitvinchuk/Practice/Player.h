#pragma once

class Player 
{
private:
	int energy = 100;
	int money = 100;
	bool shovel = false;
	bool brush = false;
	bool pickaxe = false;

	bool SmallBone = false;
	bool CommonBone = false;
	bool BigBone = false;

	bool RareBone = false;
	bool EpicBone = false;
	bool LegendaryBone = false;
public:
	int getEnergy();
	void setEnergy(int someEnergy);
	int getMoney();
	void setMoney(int someMoney);
	bool getShovel();
	void setShovel();
	bool getBrush();
	void setBrush();
	bool getPickaxe();
	void setPickaxe();

	bool getSB();
	void setSB();
	bool getCB();
	void setCB();
	bool getBB();
	void setBB();

	bool getRB();
	void setRB();
	bool getEB();
	void setEB();
	bool getLB();
	void setLB();
};