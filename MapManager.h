#pragma once
#include "Tile.h"
#include <vector>
class MapManager
{
private:
	Tile* mMap[20][20];
	Image mMapImage;
	int mMapIndex;
	Vector2 mSpawnIndex;

public:
	MapManager();
	~MapManager();
	void Load();
	void Start();
	void Update();
	void Draw();
	void Unload();
	void SetMapIndex(int index);
	Tile* GetTile(int i, int j);
	Vector2 GetSpawnTileIndex();
};



