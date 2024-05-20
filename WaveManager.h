#pragma once
#include "MapManager.h"
#include "Datas.h"
#include "Buttons.h"
#include "raylib.h"
class WaveManager
{
private:
	int mWaveCount;
	float mWaveSpawnDelay;
	float mTimer;
	bool mIsInNewWave;
	int mBonusScore;
	int mMaxNumberOfEnemies;
	int enemiesRemaining;
	MapManager* mMap;
	Buttons mPassButton;
	Texture2D mPassButtonTexture;
public :
	WaveManager();
	~WaveManager();
	void AddMap(MapManager* map);
	void Load();
	void Update();
	void Draw();
	void Unload();
	void NewWave();
	void UpdateEnemiesRemaining(int amount);
	void CreateNewWave();
};

