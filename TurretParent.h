#pragma once
#include "raylib.h"
class TurretParent
{
protected:
	int mPrice;
	Vector2 mPosition;
	Texture2D mTexture;
	float mRange;
	float mShootingSpeed;
public:
	TurretParent();
	TurretParent(int price, Vector2 position, Texture2D& texture, float range, float shootingSpeed);
	~TurretParent();
	virtual void Update();
	virtual void Draw();
	int GetPrice();
	Vector2 GetPosition();
	Texture2D GetTexture();
	float GetRange();
	float GetShootingSpeed();
};

