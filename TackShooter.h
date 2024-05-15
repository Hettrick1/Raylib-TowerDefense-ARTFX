#pragma once

#include "TurretParent.h"

class TackShooter : public TurretParent
{
private:
	float mTimerSinceLastShot;
public:
	TackShooter(Vector2 position, Texture2D& texture);
	~TackShooter();
	void Update() override;
	void Draw() override;
	void Unload();
	void Shoot();
};

