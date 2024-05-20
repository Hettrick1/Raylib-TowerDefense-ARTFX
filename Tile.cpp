#include "Tile.h"

Tile::Tile(int posX, int posY, int sizeX, int sizeY)
{
	mPosX = posX;
	mPosY = posY;
	mSizeX = sizeX;
	mSizeY = sizeY;
	mCenterPosX = mPosX + (mSizeX/2);
	mCenterPosY = mPosY + (mSizeY / 2);
	mType = TileType::GRASS;
	mColor = GREEN;
	mIsHovered = false;
	mClicked = false;
	mShowRectangle = false;
}

Tile::~Tile()
{
}

void Tile::Load()
{
}

void Tile::Draw()
{
	DrawRectangle(mPosX, mPosY, mSizeX, mSizeY, mColor);
	//DrawCircle(mCenterPosX, mCenterPosY, 5, RED);
	if (mIsHovered) {
		DrawRectangle(mPosX, mPosY, mSizeX, mSizeY, Color{ 0, 0, 0, 100 });
		DrawRectangleLinesEx({ (float)mPosX, (float)mPosY, (float)mSizeX, (float)mSizeY }, 4, YELLOW);
	}
	if (mShowRectangle) {
		DrawRectangle(mPosX, mPosY, mSizeX, mSizeY, Color{ 0, 0, 0, 200 });
		DrawRectangleLinesEx({ (float)mPosX, (float)mPosY, (float)mSizeX, (float)mSizeY }, 4, YELLOW);
	}
}

void Tile::Update()
{
}

void Tile::Unload()
{
}

void Tile::ChangeType(TileType type)
{
	mType = type;
	if (mType == TileType::GRASS) {
		mColor = GREEN;
	}
	else if (mType == TileType::ROAD) {
		mColor = GRAY;
	}
	else if (mType == TileType::TURRET) {
		mColor = LIGHTGRAY;
	}
}

void Tile::CheckClicked()
{
	Rectangle rect = { mPosX, mPosY, mSizeX, mSizeY };
	if (CheckCollisionPointRec(GetMousePosition(), rect)) {
		SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
		mIsHovered = true;
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			mClicked = !mClicked;
		}
	}
	else if (mIsHovered) {
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
		mIsHovered = false;
	}
}

TileType Tile::GetTileType()
{
	return mType;
}

void Tile::SetClicked(bool clicked)
{
	mClicked = clicked;
}

bool Tile::GetIsClicked()
{
	return mClicked;
}

void Tile::SetShowRectangle(bool show)
{
	mShowRectangle = show;
}

bool Tile::GetShowRectangle()
{
	return mShowRectangle;
}

