#pragma once
#include "raylib.h"
#include "Enemy.h"
#include <vector>

class TurretParent
{
protected:
	int mPrice;
	Vector2 mPosition;
	Texture2D mTexture;
	float mRange;
	float mShootingSpeed;
	std::vector<Enemy>* mAllEnemies;
	bool mCanShoot;
public:
	TurretParent();
	TurretParent(int price, Vector2 position, Texture2D& texture, float range, float shootingSpeed, std::vector<Enemy>* allEnemies);
	~TurretParent();
	virtual void Update();
	virtual void Draw();
	int GetPrice();
	Vector2 GetPosition();
	Texture2D GetTexture();
	float GetRange();
	float GetShootingSpeed();
	void SetCanShoot(bool shoot);
};

