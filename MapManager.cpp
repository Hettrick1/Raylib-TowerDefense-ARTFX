#include "MapManager.h"

MapManager::MapManager()
{
	mMapImage = Image();
	mMapIndex = 2;
	mSpawnIndex = {0,0};
	mTileClickedIndex = {0,0};
	mShowBuyShop = false;
	mShop = Shop();
}

MapManager::~MapManager()
{
}

void MapManager::Load()
{
	int index = 0;
	mMapImage = LoadImage(TextFormat("maps/Map%i.png", mMapIndex));
	Color* colors = LoadImageColors(mMapImage);
	int tileSizeX = 50;
	int TileSizeY = 50;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			mMap[i][j] = new Tile(j * tileSizeX, i * TileSizeY, tileSizeX, TileSizeY);
			if (colors[index].r > 0 && colors[index].g == 0 && colors[index].b == 0) {
				mMap[i][j]->ChangeType(TileType::ROAD);
			}
			else if (colors[index].g > 0 && colors[index].r == 0 && colors[index].b == 0) {
				mMap[i][j]->ChangeType(TileType::GRASS);
			}
			else if (colors[index].b > 0 && colors[index].r == 0 && colors[index].g == 0) {
				mMap[i][j]->ChangeType(TileType::TURRET);
			}
			else if (colors[index].b == 0 && colors[index].r == 0 && colors[index].g == 0) {
				mMap[i][j]->ChangeType(TileType::ROAD);
				mSpawnIndex = { (float)j, (float)i };
			}
			index += 1;
		}
	}
	UnloadImageColors(colors);
	UnloadImage(mMapImage);
}

void MapManager::Start()
{
}

void MapManager::Update()
{
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			
			if (mMap[i][j]->GetTileType() == TileType::GRASS) {
				mMap[i][j]->CheckClicked();
				if (mMap[i][j]->GetIsClicked()) {
					mMap[i][j]->SetClicked(false);
					mMap[i][j]->SetShowRectangle(!mMap[i][j]->GetShowRectangle());
					mShowBuyShop = mMap[i][j]->GetShowRectangle();
					if (i != mTileClickedIndex.x || j != mTileClickedIndex.y) {
						mMap[(int)mTileClickedIndex.x][(int)mTileClickedIndex.y]->SetShowRectangle(false);
						mTileClickedIndex = { (float)i, (float)j };
					}
				}
			}
		}
	}
	if (mShowBuyShop) {
		mShop.UpdateBuyShop();
	}
}

void MapManager::Draw()
{
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			mMap[i][j]->Draw();
		}
	}
	if (mShowBuyShop) {
		mShop.DrawBuyShop();
	}
}

void MapManager::Unload()
{

}

void MapManager::SetMapIndex(int index)
{
	mMapIndex = index;
}

Tile* MapManager::GetTile(int i, int j)
{
	return mMap[j][i];
}

Vector2 MapManager::GetSpawnTileIndex()
{
	return mSpawnIndex;
}

