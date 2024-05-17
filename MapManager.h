#pragma once
#include "raylib.h"
#include "Tile.h"
#include "Buttons.h"
#include "Datas.h"
#include "DartMonkey.h"
#include "TackShooter.h"
#include "TurretParent.h"
#include "Enemy.h"
#include <vector>

class MapManager
{
private:
	Tile* mMap[20][20];
	Image mMapImage;
	int mMapIndex;
	Vector2 mSpawnIndex;
	Vector2 mTileClickedIndex;
	bool mShowBuyShop;
	std::vector<Buttons> mBuyShopButtons;
	std::vector<Buttons> mUpgradeShopButtons;
	std::vector<DartMonkey> mDartMonkeyTurrets;
	std::vector<TackShooter> mTackShooterTurrets;
	std::vector<Enemy> mEnemies;
	Texture2D mDartMonkeyTexture, mTackShooterTexture;

public:
	MapManager();
	~MapManager();
	void Load();
	void Start();
	void Update();
	void UpdateBuyShop();
	void UpdateUpgradeShop();
	void HideShopMenu();
	void Draw();
	void DrawBuyShop();
	void DrawUpgradeShop();
	void Unload();
	void SetMapIndex(int index);
	Tile* GetTile(int i, int j);
	Vector2 GetSpawnTileIndex();
	void CreateNewEnemy();
	void MoveEnemies();
};



