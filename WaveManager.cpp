#include "WaveManager.h"

WaveManager::WaveManager()
{
	mWaveCount = 0;
	mWaveSpawnDelay = 0.5;
	mTimer = mWaveSpawnDelay;
	mIsInNewWave = false;
	mBonusScore = 200;
	mMaxNumberOfEnemies = 5;
	enemiesRemaining = 0;
	mPassButtonTexture = Texture();
	mPassButton = Buttons();
}

WaveManager::~WaveManager()
{
}

void WaveManager::AddMap(MapManager* map)
{
	mMap = map;
	Load();
}

void WaveManager::Load()
{
	mPassButtonTexture = LoadTexture("resources/sprites/Next.png");
	mPassButton = Buttons({ 1050, 750, 200, 150 }, BLUE, mPassButtonTexture, 1);
}

void WaveManager::Update()
{
	UpdateEnemiesRemaining(mMap->GetEnemiesRemaining());
	if (!mMap->GetShowBuyShop()) {
		mPassButton.Update();
		if (mPassButton.GetClickedBool()) {
			mPassButton.SetClickedBool(false);
			if (mMap->AreAllEnemiesDead()) {
				CreateNewWave();
			}
		}
	}
	if (!mMap->AreAllEnemiesDead()) {
		mPassButton.SetEnable(false);
		mPassButton.SetHoveredBool(false);
	}
	else {
		mPassButton.SetEnable(true);
	}
	NewWave();
}

void WaveManager::Draw()
{
	if (!mMap->GetShowBuyShop()) {
		DrawText("Next Wave", 1050, 700, 30, BLACK);
		mPassButton.Draw();
	}
}

void WaveManager::Unload()
{
	UnloadTexture(mPassButtonTexture);
}

void WaveManager::NewWave()
{
	if (mIsInNewWave) {
		if (enemiesRemaining < mMaxNumberOfEnemies) {
			mTimer -= GetFrameTime();
			if (mTimer < 0) {
				mTimer = mWaveSpawnDelay;
				mMap->CreateNewEnemy();
			}
		}
		else {
			mIsInNewWave = false;
		}
	}
}

void WaveManager::UpdateEnemiesRemaining(int amount)
{
	enemiesRemaining = amount;
}

void WaveManager::CreateNewWave()
{
	mIsInNewWave = true;
	if (mWaveSpawnDelay > 0.1) mWaveSpawnDelay -= 0.01;
	mTimer = mWaveSpawnDelay;
	mBonusScore += 100;
	mMaxNumberOfEnemies += 5 * mWaveCount;
	mWaveCount++;
	AddMoney(mBonusScore);
}
