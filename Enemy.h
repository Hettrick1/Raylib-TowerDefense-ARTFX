#pragma once
#include "raylib.h"
#include "MapManager.h"
#include "Tile.h"
#include "TileType.h"
class Enemy
{
private:
	int mHealth;
	Vector2 mSpawnPos;
	Vector2 mDestination;
	Vector2 mPosition;
	Vector2 mDestinationIndex;
	int mDirection; // 0 front, 1 right, 2 left, 3 backward;
	int mIndexX;
	int mIndexY;
	float mSpeed;
	int	mDamage;
	int	mCoins;
	MapManager mMap;
public:
	Enemy(Vector2 spawnPos, Vector2 destinationIndex, MapManager& map);
	~Enemy();
	void Load();
	void Draw();
	void Update();
	void Unload();
	void Move();
};

