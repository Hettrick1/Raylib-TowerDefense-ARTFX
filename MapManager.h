#pragma once
#include "Tile.h"
#include "Buttons.h"
#include "Datas.h"
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
};



