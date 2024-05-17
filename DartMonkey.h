#pragma once
#include "TurretParent.h"
#include "Enemy.h"
#include "Projectile.h"
#include <cmath>
#include <vector>
#include <iostream>

class DartMonkey : public TurretParent
{
private:
	float mRotation;
	float mTimerSinceLastShot;
	std::vector<Projectile> projectiles;
public:
	DartMonkey(Vector2 position, Texture2D& texture, std::vector<Enemy>* allEnemies);
	~DartMonkey();
	void Update() override;
	void Draw() override;
	void Unload();
	void Shoot();
	void SetRotation(float rotation);
};

