#pragma once
#include "raylib.h"

struct Enemy
{
	int mHealth;
	Vector2 mSpawnPos;
	Vector2 mDestination;
	Vector2 mPosition;
	Vector2 mDestinationIndex;
	int mDirection; // 0 front, 1 right, 2 left, 3 backward;
	float mSpeed;
	int	mDamage;
	int	mCoins;
};

