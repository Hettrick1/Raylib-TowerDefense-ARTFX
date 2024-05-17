#pragma once

#include "TurretParent.h"
#include "Projectile.h"
#include "Enemy.h"
#include <cmath>
#include <vector>

class TackShooter : public TurretParent
{
private:
	float mTimerSinceLastShot;
	std::vector<Projectile> projectiles;
public:
	TackShooter(Vector2 position, Texture2D& texture, std::vector<Enemy>* allEnemies);
	~TackShooter();
	void Update() override;
	void Draw() override;
	void Unload();
	void Shoot();
};

