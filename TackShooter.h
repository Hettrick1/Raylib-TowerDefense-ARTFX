#pragma once

#include "TurretParent.h"
#include "Projectile.h"
#include <cmath>
#include <vector>

class TackShooter : public TurretParent
{
private:
	float mTimerSinceLastShot;
	std::vector<Projectile> projectiles;
public:
	TackShooter(Vector2 position, Texture2D& texture);
	~TackShooter();
	void Update() override;
	void Draw() override;
	void Unload();
	void Shoot();
};

