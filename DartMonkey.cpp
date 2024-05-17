#include "DartMonkey.h"

DartMonkey::DartMonkey(Vector2 position, Texture2D& texture, std::vector<Enemy>* allEnemies) : TurretParent(250, position, texture, 150, 0.5f, allEnemies)
{
	mRotation = 0;
	mTimerSinceLastShot = 0;
}

DartMonkey::~DartMonkey()
{
}

void DartMonkey::Update()
{
	if (mCanShoot) {
		mTimerSinceLastShot -= GetFrameTime();
		if (mTimerSinceLastShot < 0) {
			mTimerSinceLastShot = mShootingSpeed;
			Shoot();
		}
	}
	if (!mCanShoot) {
		mTimerSinceLastShot = 0;
	}
	for (Projectile& projectile : projectiles) {
		if (!projectile.isOutOfRange) {
			projectile.position.x += 300 * projectile.velocity.x * GetFrameTime();
			projectile.position.y += 300 * projectile.velocity.y * GetFrameTime();
			float distance = sqrt(pow(projectile.position.x - projectile.startPosition.x, 2) + pow(projectile.position.y - projectile.startPosition.y, 2));
			if (distance > projectile.range) {
				projectile.isOutOfRange = true;
			}
			for (Enemy& enemy : *mAllEnemies) {
				if (!enemy.mIsDead && CheckCollisionCircles(projectile.position, 5, enemy.mPosition, 20)) {
					projectile.isDestroyed = true;
					enemy.mIsDead = true;
				}
			}
		}
		if (projectile.isOutOfRange) {
			projectiles.erase(begin(projectiles));
		}
	}
}

void DartMonkey::Draw() 
{
	DrawTexturePro(mTexture, { 0, 0, (float)mTexture.width, (float)mTexture.height }, { mPosition.x + (float)mTexture.width / 2, mPosition.y + (float)mTexture.height / 2, (float)mTexture.width, (float)mTexture.height }, { (float)mTexture.width/2, (float)mTexture.height/2 }, 90+mRotation, WHITE);
	for (Projectile& projectile : projectiles) {
		if (!projectile.isDestroyed) {
			DrawCircle(projectile.position.x, projectile.position.y, 5, BLUE);
		}
	}
}

void DartMonkey::Unload()
{
	UnloadTexture(mTexture);
}

void DartMonkey::Shoot()
{
	float rotationRadians = (float)mRotation * PI / 180.0f;

	Projectile newProjectile;

	newProjectile.position = { mPosition.x + 25, mPosition.y + 25 };
	newProjectile.startPosition = { mPosition.x + 25, mPosition.y + 25 };
	newProjectile.range = mRange;
	newProjectile.velocity.x = cos(rotationRadians);
	newProjectile.velocity.y = sin(rotationRadians);
	newProjectile.isDestroyed = false;
	newProjectile.isOutOfRange = false;
	projectiles.push_back(newProjectile);
}

void DartMonkey::SetRotation(float rotation)
{
	mRotation = rotation * 180/PI;
}
