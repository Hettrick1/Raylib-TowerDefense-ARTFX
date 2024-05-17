#include "TurretParent.h"



TurretParent::TurretParent()
{
}

TurretParent::TurretParent(int price, Vector2 position, Texture2D& texture, float range, float shootingSpeed, std::vector<Enemy>* allEnemies)
{
	mPrice = price;
	mPosition = position;
	mTexture = texture;
	mRange = range;
	mShootingSpeed = shootingSpeed;
	mAllEnemies = allEnemies;
}

TurretParent::~TurretParent()
{
}

void TurretParent::Update()
{
}

void TurretParent::Draw()
{
}

int TurretParent::GetPrice()
{
	return mPrice;
}

Vector2 TurretParent::GetPosition()
{
	return mPosition;
}

Texture2D TurretParent::GetTexture()
{
	return mTexture;
}

float TurretParent::GetRange()
{
	return mRange;
}

float TurretParent::GetShootingSpeed()
{
	return mShootingSpeed;
}
