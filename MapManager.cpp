#include "MapManager.h"

MapManager::MapManager()
{
	mMapImage = Image();
	mMapIndex = 2;
	mSpawnIndex = {0,0};
	mTileClickedIndex = {0,0};
	mShowBuyShop = false;
	mBuyShopButtons = {
		Buttons({1050, 250, 200, 200}, YELLOW, "Turret 1", BLACK, 30),
		Buttons({1050, 550, 200, 200}, YELLOW, "Turret 2", BLACK, 30),
		Buttons({1050, 850, 200, 50}, RED, "Quit shop", BLACK, 30)
	};
	mUpgradeShopButtons = {

	};
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
		UpdateBuyShop();
	}
}
void MapManager::UpdateBuyShop()
{
	for (Buttons& button : mBuyShopButtons) {
		button.Update();
	}
	if (mBuyShopButtons[0].GetClickedBool()) {
		mBuyShopButtons[0].SetClickedBool(false);
		mMap[(int)mTileClickedIndex.x][(int)mTileClickedIndex.y]->ChangeType(TileType::TURRET);
		HideShopMenu();
		//create first turret
	}
	if (mBuyShopButtons[1].GetClickedBool()) {
		mBuyShopButtons[1].SetClickedBool(false);
		mMap[(int)mTileClickedIndex.x][(int)mTileClickedIndex.y]->ChangeType(TileType::TURRET);
		HideShopMenu();
		//create second turret
	}
	if (mBuyShopButtons[2].GetClickedBool()) {
		mBuyShopButtons[2].SetClickedBool(false);
		HideShopMenu();
	}
}

void MapManager::UpdateUpgradeShop()
{
}

void MapManager::HideShopMenu()
{
	mMap[(int)mTileClickedIndex.x][(int)mTileClickedIndex.y]->SetShowRectangle(false);
	mShowBuyShop = false;
	for (Buttons& button : mBuyShopButtons) {
		button.ResetTimer();
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
		DrawBuyShop();
	}
}
void MapManager::DrawBuyShop()
{
	DrawRectangle(1000, 0, 400, 1000, GRAY);
	SetMoneyPos({ (float)(1150 - MeasureText(TextFormat("%i", GetMoney()), 50) / 2), GetMoneyPos().y });
	DrawText(TextFormat("%i", GetMoney()), GetMoneyPos().x, GetMoneyPos().y, 50, WHITE);
	for (Buttons& button : mBuyShopButtons) {
		button.Draw();
	}
}

void MapManager::DrawUpgradeShop()
{
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

