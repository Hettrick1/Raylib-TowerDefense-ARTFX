#include "Enemy.h"

Enemy::Enemy(Vector2 spawnPos, Vector2 destinationIndex, MapManager& map)
{
	mHealth = 100;
	mSpawnPos = spawnPos;
	mPosition = { (float)spawnPos.x - 10, (float)spawnPos.y };
	mDestination = spawnPos;
	mDestinationIndex = destinationIndex;
	mDirection = 0; // 0 right, 1 down, 2 up, 3 left;
	mIndexX = 1; // 1 horizontal front, -1 horizontal back
	mIndexY = 0; // 1 vertical front, -1 vertical back
	mSpeed = 0;
	mDamage = 10;
	mCoins = 100;
	mMap = map;
}

Enemy::~Enemy()
{
}

void Enemy::Load()
{
}

void Enemy::Draw()
{
	DrawCircle(mPosition.x, mPosition.y, 20, BLUE);
}

void Enemy::Update()
{
	Move();
}

void Enemy::Unload()
{
}

void Enemy::Move()
{
	switch (mDirection)
	{
	case 0:
		mPosition.x += mSpeed * GetFrameTime();
		break;
	case 1:
		mPosition.y += mSpeed * GetFrameTime();
		break;
	case 2:
		mPosition.y -= mSpeed * GetFrameTime();
		break;
	case 3:
		mPosition.x -= mSpeed * GetFrameTime();
		break;
	}
	if ((mDirection == 0 && mPosition.x > mDestination.x) || (mDirection == 1 && mPosition.y > mDestination.y) || (mDirection == 2 && mPosition.y < mDestination.y) || (mDirection == 3 && mPosition.x < mDestination.x)) {
		switch (mDirection)
		{
		case 0: // right
			if (mMap.GetTile(mDestinationIndex.x + 1, mDestinationIndex.y)->GetTileType() == TileType::ROAD) {
				mDirection = 0;
				mDestinationIndex.x += 1;
				mDestination = mMap.GetTile(mDestinationIndex.x, mDestinationIndex.y)->GetCenterPos();
			}
			else if (mMap.GetTile(mDestinationIndex.x, mDestinationIndex.y + 1)->GetTileType() == TileType::ROAD) {
				mDirection = 1;
				mDestinationIndex.y += 1;
				mDestination = mMap.GetTile(mDestinationIndex.x, mDestinationIndex.y)->GetCenterPos();
			}
			else if (mMap.GetTile(mDestinationIndex.x, mDestinationIndex.y - 1)->GetTileType() == TileType::ROAD) {
				mDirection = 2;
				mDestinationIndex.y -= 1;
				mDestination = mMap.GetTile(mDestinationIndex.x, mDestinationIndex.y)->GetCenterPos();
			}
			else {
				std::cout << "ATTACK";
			}
			break;
		case 1: // down
			if (mMap.GetTile(mDestinationIndex.x, mDestinationIndex.y + 1)->GetTileType() == TileType::ROAD) {
				mDirection = 1;
				mDestinationIndex.y += 1;
				mDestination = mMap.GetTile(mDestinationIndex.x, mDestinationIndex.y)->GetCenterPos();
			}
			else if (mMap.GetTile(mDestinationIndex.x - 1, mDestinationIndex.y)->GetTileType() == TileType::ROAD) {
				mDirection = 3;
				mDestinationIndex.x -= 1;
				mDestination = mMap.GetTile(mDestinationIndex.x, mDestinationIndex.y)->GetCenterPos();
			}
			else if (mMap.GetTile(mDestinationIndex.x + 1, mDestinationIndex.y)->GetTileType() == TileType::ROAD) {
				mDirection = 0;
				mDestinationIndex.x += 1;
				mDestination = mMap.GetTile(mDestinationIndex.x, mDestinationIndex.y)->GetCenterPos();
			}
			else {
				std::cout << "ATTACK";
			}
			break;
		case 2: // up
			if (mMap.GetTile(mDestinationIndex.x, mDestinationIndex.y - 1)->GetTileType() == TileType::ROAD) {
				mDirection = 2;
				mDestinationIndex.y -= 1;
				mDestination = mMap.GetTile(mDestinationIndex.x, mDestinationIndex.y)->GetCenterPos();
			}
			else if (mMap.GetTile(mDestinationIndex.x + 1, mDestinationIndex.y)->GetTileType() == TileType::ROAD) {
				mDirection = 0; 
				mDestinationIndex.x += 1;
				mDestination = mMap.GetTile(mDestinationIndex.x, mDestinationIndex.y)->GetCenterPos();
			}
			else if (mMap.GetTile(mDestinationIndex.x - 1, mDestinationIndex.y)->GetTileType() == TileType::ROAD) {
				mDirection = 3;
				mDestinationIndex.x -= 1;
				mDestination = mMap.GetTile(mDestinationIndex.x, mDestinationIndex.y)->GetCenterPos();
			}
			else {
				std::cout << "ATTACK";
			}
			break;
		case 3: // left
			if (mMap.GetTile(mDestinationIndex.x - 1, mDestinationIndex.y)->GetTileType() == TileType::ROAD) {
				mDirection = 3;
				mDestinationIndex.x -= 1;
				mDestination = mMap.GetTile(mDestinationIndex.x, mDestinationIndex.y)->GetCenterPos();
			}
			else if (mMap.GetTile(mDestinationIndex.x, mDestinationIndex.y - 1)->GetTileType() == TileType::ROAD) {
				mDirection = 2;
				mDestinationIndex.y -= 1;
				mDestination = mMap.GetTile(mDestinationIndex.x, mDestinationIndex.y)->GetCenterPos();
			}
			else if (mMap.GetTile(mDestinationIndex.x, mDestinationIndex.y + 1)->GetTileType() == TileType::ROAD) {
				mDirection = 1;
				mDestinationIndex.y += 1;
				mDestination = mMap.GetTile(mDestinationIndex.x, mDestinationIndex.y)->GetCenterPos();
			}
			else {
				std::cout << "ATTACK";
			}
			break;
		}
	}
}
