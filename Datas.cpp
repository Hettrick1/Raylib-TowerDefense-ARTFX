#include "Datas.h"

extern int money = 10000;
extern int life = 50;
extern Vector2 moneyPos = {1000, 100};

Vector2 GetMoneyPos() {
	return moneyPos;
}

void SetMoneyPos(Vector2 newPos)
{
	moneyPos = newPos;
}

int GetMoney()
{
	return money;
}

void AddMoney(int amount)
{
	money += amount;
}

void AddLife(int amount)
{
	life += amount;
}

void ResetLife()
{
	life = 50;
}

int Getlife()
{
	return life;
}

