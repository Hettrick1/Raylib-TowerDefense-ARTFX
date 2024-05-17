#include "TackShooter.h"

TackShooter::TackShooter(Vector2 position, Texture2D& texture, std::vector<Enemy>* allEnemies) : TurretParent(50, position, texture, 60, 0.5f, allEnemies)
{
	mTimerSinceLastShot = 0;
}

TackShooter::~TackShooter()
{
}

void TackShooter::Update()
{
	if (mCanShoot) {
		mTimerSinceLastShot -= GetFrameTime();
		if (mTimerSinceLastShot < 0) {
			mTimerSinceLastShot = 1;
			Shoot();
		}
	}
	if (!mCanShoot) {
		mTimerSinceLastShot = 0;
	}
	for (Projectile& projectile : projectiles) {
		if (!projectile.isOutOfRange) {
			projectile.position.x += 150 * projectile.velocity.x * GetFrameTime();
			projectile.position.y += 150 * projectile.velocity.y * GetFrameTime();
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

void TackShooter::Draw()
{
	DrawTextureEx(mTexture, mPosition, 0, 1, WHITE);
	for (Projectile& projectile : projectiles) {
		if (!projectile.isDestroyed) {
			DrawCircle(projectile.position.x, projectile.position.y, 5, BLUE);
		}
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
		newProjectile.isOutOfRange = false;
		projectiles.push_back(newProjectile);
	}

}
