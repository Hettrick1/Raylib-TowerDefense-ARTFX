#include "TackShooter.h"

TackShooter::TackShooter(Vector2 position, Texture2D& texture) : TurretParent(50, position, texture, 50, 0.5f)
{
	mTimerSinceLastShot = 0;
}

TackShooter::~TackShooter()
{
}

void TackShooter::Update()
{
}

void TackShooter::Draw()
{
	DrawTextureEx(mTexture, mPosition, 0, 1, WHITE);
}

void TackShooter::Unload()
{
	UnloadTexture(mTexture);
}

void TackShooter::Shoot()
{
}
