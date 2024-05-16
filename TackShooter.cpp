#include "TackShooter.h"

TackShooter::TackShooter(Vector2 position, Texture2D& texture) : TurretParent(50, position, texture, 60, 0.5f)
{
	mTimerSinceLastShot = 0;
}

TackShooter::~TackShooter()
{
}

void TackShooter::Update()
{
	mTimerSinceLastShot += GetFrameTime();
	if (mTimerSinceLastShot > 1.5) {
		mTimerSinceLastShot = 0;
		Shoot();
	}
	for (Projectile& projectile : projectiles) {
		projectile.position.x += 100 * projectile.velocity.x * GetFrameTime();
		projectile.position.y += 100 * projectile.velocity.y * GetFrameTime();
		float distance = sqrt(pow(projectile.position.x - projectile.startPosition.x, 2) + pow(projectile.position.y - projectile.startPosition.y, 2));
		if (distance > projectile.range) {
			projectile.isDestroyed = true;
		}
		if (projectile.isDestroyed) {
			projectiles.erase(begin(projectiles));
		}
	}
}

void TackShooter::Draw()
{
	DrawTextureEx(mTexture, mPosition, 0, 1, WHITE);
	for (Projectile& projectile : projectiles) {
		DrawCircle(projectile.position.x, projectile.position.y, 5, BLUE);
	}
}

void TackShooter::Unload()
{
	UnloadTexture(mTexture);
}

void TackShooter::Shoot()
{
	for (int i = 0; i < 8; i++) {
		float angle = (45 * (PI/180)) * i;
		Projectile newProjectile;

		newProjectile.position = { mPosition.x + 25, mPosition.y + 25 };
		newProjectile.startPosition = { mPosition.x + 25, mPosition.y + 25 };
		newProjectile.range = mRange;
		newProjectile.velocity.x = cos(angle);
		newProjectile.velocity.y = sin(angle);
		newProjectile.isDestroyed = false;
		projectiles.push_back(newProjectile);
	}

}
