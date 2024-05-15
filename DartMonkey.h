#pragma once
#include "TurretParent.h"

class DartMonkey : public TurretParent
{
private:
	float mRotation;
	float mTimerSinceLastShot;
public:
	DartMonkey(Vector2 position, Texture2D& texture);
	~DartMonkey();
	void Update() override;
	void Draw() override;
	void Unload();
	void Shoot();
};

