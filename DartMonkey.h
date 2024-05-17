#pragma once
#include "TurretParent.h"
#include "Enemy.h"
#include <vector>

class DartMonkey : public TurretParent
{
private:
	float mRotation;
	float mTimerSinceLastShot;
public:
	DartMonkey(Vector2 position, Texture2D& texture, std::vector<Enemy>* allEnemies);
	~DartMonkey();
	void Update() override;
	void Draw() override;
	void Unload();
	void Shoot();
};

