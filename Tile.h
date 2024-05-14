#pragma once
#include "TileType.h"
#include "raylib.h"

#include <iostream>

class Tile
{
private:
	int mPosX;
	int mPosY;
	int mSizeX;
	int mSizeY;
	int mCenterPosX;
	int mCenterPosY;
	TileType mType;
	Color mColor;
	bool mIsHovered;
	bool mClicked;
public:
	Tile(int posX, int posY, int sizeX, int sizeY);
	~Tile();
	void Load();
	void Draw();
	void Update();
	void Unload();
	void ChangeType(TileType type);
	void CheckClicked();
	TileType GetTileType();
	int GetPosX() const { return mPosX; }
	int GetPosY() const { return mPosY; }
	Vector2 GetCenterPos() { return { (float)mCenterPosX, (float)mCenterPosY }; }
	int GetSizeX() const { return mSizeX; }
	int GetSizeY() const { return mSizeY; }
	void SetClicked(bool clicked);
	bool GetIsClicked();
};



