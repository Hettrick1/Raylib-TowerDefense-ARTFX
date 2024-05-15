#include "Datas.h"

extern int money = 10000;
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
