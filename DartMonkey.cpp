#include "DartMonkey.h"

DartMonkey::DartMonkey(Vector2 position, Texture2D& texture) : TurretParent(250, position, texture, 50, 0.5f)
{
	mRotation = 0;
	mTimerSinceLastShot = 0;
}

DartMonkey::~DartMonkey()
{
}

void DartMonkey::Update()
{
}

void DartMonkey::Draw() 
{
	DrawTextureEx(mTexture, mPosition, mRotation, 1, WHITE);
}

void DartMonkey::Unload()
{
	UnloadTexture(mTexture);
}

void DartMonkey::Shoot()
{
}
