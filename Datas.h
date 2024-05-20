#pragma once

#include "raylib.h"

extern int money;
extern int Life;
extern Vector2 moneyPos;

Vector2 GetMoneyPos();
void SetMoneyPos(Vector2 newpos);
int GetMoney();
void AddMoney(int amount);
void AddLife(int amount);
void ResetLife();
int Getlife();
