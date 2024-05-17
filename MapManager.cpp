#include "MapManager.h"

int timer = 0;

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
	mDartMonkeyTexture = Texture2D();
	mTackShooterTexture = Texture2D();
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
	mDartMonkeyTexture = LoadTexture("resources/sprites/DartMonkey.png");
	mTackShooterTexture = LoadTexture("resources/sprites/TackShooter.png");
	CreateNewEnemy();
}

void MapManager::Start()
{
}

void MapManager::Update()
{
	timer += 1;
	if (timer > 50) {
		CreateNewEnemy();
		timer = 0;
	}
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
	for (DartMonkey& turret : mDartMonkeyTurrets) {
		for (int j = 0; j < mEnemies.size(); j++) {
			float distance = sqrt(pow(mEnemies[j].mPosition.x - turret.GetPosition().x, 2) + pow(mEnemies[j].mPosition.y - turret.GetPosition().y, 2));
			if (!mEnemies[j].mIsDead && distance < turret.GetRange() + 20) {
				turret.SetRotation(atan2f(mEnemies[j].mPosition.y - turret.GetPosition().y, mEnemies[j].mPosition.x - turret.GetPosition().x));
				turret.SetCanShoot(true);
				break;
			}
			else {
				turret.SetCanShoot(false);
			}
		}
		turret.Update();
	}
	for (TackShooter& turret : mTackShooterTurrets) {
		for (int j = 0; j < mEnemies.size(); j++) {
			float distance = sqrt(pow(mEnemies[j].mPosition.x - turret.GetPosition().x, 2) + pow(mEnemies[j].mPosition.y - turret.GetPosition().y, 2));
			if (!mEnemies[j].mIsDead && distance < turret.GetRange() + 20) {
				turret.SetCanShoot(true);
				break;
			}
			else {
				turret.SetCanShoot(false);
			}
		}
		turret.Update();
	}
	MoveEnemies();
}
void MapManager::UpdateBuyShop()
{
	for (Buttons& button : mBuyShopButtons) {
		button.Update();
	}
	if (GetMoney() > 3000 && mBuyShopButtons[0].GetClickedBool()) {
		mBuyShopButtons[0].SetClickedBool(false);
		mMap[(int)mTileClickedIndex.x][(int)mTileClickedIndex.y]->ChangeType(TileType::TURRET);
		AddMoney(-3000);
		HideShopMenu();
		DartMonkey turret = DartMonkey({(float) mMap[(int)mTileClickedIndex.x][(int)mTileClickedIndex.y]->GetPosX(), (float)mMap[(int)mTileClickedIndex.x][(int)mTileClickedIndex.y]->GetPosY() }, mDartMonkeyTexture, &mEnemies);
		mDartMonkeyTurrets.push_back(turret);
		//create first turret
	}
	if (GetMoney() > 5000 && mBuyShopButtons[1].GetClickedBool()) {
		mBuyShopButtons[1].SetClickedBool(false);
		mMap[(int)mTileClickedIndex.x][(int)mTileClickedIndex.y]->ChangeType(TileType::TURRET);
		AddMoney(-5000);
		HideShopMenu();
		TackShooter turret = TackShooter({ (float)mMap[(int)mTileClickedIndex.x][(int)mTileClickedIndex.y]->GetPosX(), (float)mMap[(int)mTileClickedIndex.x][(int)mTileClickedIndex.y]->GetPosY() }, mTackShooterTexture, &mEnemies);
		mTackShooterTurrets.push_back(turret);
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
	SetMoneyPos({ (float)(1150 - MeasureText(TextFormat("%i", GetMoney()), 50) / 2), GetMoneyPos().y });
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
	for (DartMonkey& turret : mDartMonkeyTurrets) {
		turret.Draw();
	}
	for (TackShooter& turret : mTackShooterTurrets) {
		turret.Draw();
	}
	for (Enemy& enemy : mEnemies) {
		if (!enemy.mIsDead) {
			DrawCircle(enemy.mPosition.x, enemy.mPosition.y, 20, BLUE);
		}
	}
	SetMoneyPos({ (float)(1150 - MeasureText(TextFormat("%i", GetMoney()), 50) / 2), GetMoneyPos().y });
	DrawText(TextFormat("%i", GetMoney()), GetMoneyPos().x, GetMoneyPos().y, 50, BLACK);
}
void MapManager::DrawBuyShop()
{
	DrawRectangle(1000, 0, 400, 1000, GRAY);
	SetMoneyPos({ (float)(1150 - MeasureText(TextFormat("%i", GetMoney()), 50) / 2), GetMoneyPos().y });
	DrawText(TextFormat("%i", GetMoney()), GetMoneyPos().x, GetMoneyPos().y, 50, WHITE);
	DrawText("3000", 1050, 460, 30, WHITE);
	DrawText("5000", 1050, 760, 30, WHITE);
	for (Buttons& button : mBuyShopButtons) {
		button.Draw();
	}
}

void MapManager::DrawUpgradeShop()
{
}

void MapManager::Unload()
{
	std::cout << mEnemies.size();
	UnloadTexture(mDartMonkeyTexture);
	UnloadTexture(mTackShooterTexture);
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

void MapManager::CreateNewEnemy()
{
	Enemy newEnemy;

	newEnemy.mCoins = 100;
	newEnemy.mDamage = 1;
	newEnemy.mDestination = GetTile((int)mSpawnIndex.x, (int)mSpawnIndex.y)->GetCenterPos();
	newEnemy.mDestinationIndex = mSpawnIndex;
	newEnemy.mDirection = 0;
	newEnemy.mHealth = 2;
	newEnemy.mSpawnPos = GetTile((int)mSpawnIndex.x, (int)mSpawnIndex.y)->GetCenterPos();
	newEnemy.mPosition = { (float)newEnemy.mSpawnPos.x - 10, (float)newEnemy.mSpawnPos.y };
	newEnemy.mSpeed = 100;
	newEnemy.mIsDead = false;

	mEnemies.push_back(newEnemy);
}

void MapManager::MoveEnemies()
{
	for (Enemy& enemy : mEnemies) { // Bon c'est pas propre mais j'avais une inclusion circulaire et c'est le moyen le plus simple que j'ai trouvé de la régler
		if (!enemy.mIsDead) {
			switch (enemy.mDirection)
			{
			case 0:
				enemy.mPosition.x += enemy.mSpeed * GetFrameTime();
				break;
			case 1:
				enemy.mPosition.y += enemy.mSpeed * GetFrameTime();
				break;
			case 2:
				enemy.mPosition.y -= enemy.mSpeed * GetFrameTime();
				break;
			case 3:
				enemy.mPosition.x -= enemy.mSpeed * GetFrameTime();
				break;
			}
			if ((enemy.mDirection == 0 && enemy.mPosition.x > enemy.mDestination.x) || (enemy.mDirection == 1 && enemy.mPosition.y > enemy.mDestination.y) || (enemy.mDirection == 2 && enemy.mPosition.y < enemy.mDestination.y) || (enemy.mDirection == 3 && enemy.mPosition.x < enemy.mDestination.x)) {
				switch (enemy.mDirection)
				{
				case 0: // right
					if (GetTile(enemy.mDestinationIndex.x + 1, enemy.mDestinationIndex.y)->GetTileType() == TileType::ROAD) {
						enemy.mDirection = 0;
						enemy.mDestinationIndex.x += 1;
						enemy.mDestination = GetTile(enemy.mDestinationIndex.x, enemy.mDestinationIndex.y)->GetCenterPos();
					}
					else if (GetTile(enemy.mDestinationIndex.x, enemy.mDestinationIndex.y + 1)->GetTileType() == TileType::ROAD) {
						enemy.mDirection = 1;
						enemy.mDestinationIndex.y += 1;
						enemy.mDestination = GetTile(enemy.mDestinationIndex.x, enemy.mDestinationIndex.y)->GetCenterPos();
					}
					else if (GetTile(enemy.mDestinationIndex.x, enemy.mDestinationIndex.y - 1)->GetTileType() == TileType::ROAD) {
						enemy.mDirection = 2;
						enemy.mDestinationIndex.y -= 1;
						enemy.mDestination = GetTile(enemy.mDestinationIndex.x, enemy.mDestinationIndex.y)->GetCenterPos();
					}
					else {
						std::cout << "ATTACK";
					}
					break;
				case 1: // down
					if (GetTile(enemy.mDestinationIndex.x, enemy.mDestinationIndex.y + 1)->GetTileType() == TileType::ROAD) {
						enemy.mDirection = 1;
						enemy.mDestinationIndex.y += 1;
						enemy.mDestination = GetTile(enemy.mDestinationIndex.x, enemy.mDestinationIndex.y)->GetCenterPos();
					}
					else if (GetTile(enemy.mDestinationIndex.x - 1, enemy.mDestinationIndex.y)->GetTileType() == TileType::ROAD) {
						enemy.mDirection = 3;
						enemy.mDestinationIndex.x -= 1;
						enemy.mDestination = GetTile(enemy.mDestinationIndex.x, enemy.mDestinationIndex.y)->GetCenterPos();
					}
					else if (GetTile(enemy.mDestinationIndex.x + 1, enemy.mDestinationIndex.y)->GetTileType() == TileType::ROAD) {
						enemy.mDirection = 0;
						enemy.mDestinationIndex.x += 1;
						enemy.mDestination = GetTile(enemy.mDestinationIndex.x, enemy.mDestinationIndex.y)->GetCenterPos();
					}
					else {
						std::cout << "ATTACK";
					}
					break;
				case 2: // up
					if (GetTile(enemy.mDestinationIndex.x, enemy.mDestinationIndex.y - 1)->GetTileType() == TileType::ROAD) {
						enemy.mDirection = 2;
						enemy.mDestinationIndex.y -= 1;
						enemy.mDestination = GetTile(enemy.mDestinationIndex.x, enemy.mDestinationIndex.y)->GetCenterPos();
					}
					else if (GetTile(enemy.mDestinationIndex.x + 1, enemy.mDestinationIndex.y)->GetTileType() == TileType::ROAD) {
						enemy.mDirection = 0;
						enemy.mDestinationIndex.x += 1;
						enemy.mDestination = GetTile(enemy.mDestinationIndex.x, enemy.mDestinationIndex.y)->GetCenterPos();
					}
					else if (GetTile(enemy.mDestinationIndex.x - 1, enemy.mDestinationIndex.y)->GetTileType() == TileType::ROAD) {
						enemy.mDirection = 3;
						enemy.mDestinationIndex.x -= 1;
						enemy.mDestination = GetTile(enemy.mDestinationIndex.x, enemy.mDestinationIndex.y)->GetCenterPos();
					}
					else {
						std::cout << "ATTACK";
					}
					break;
				case 3: // left
					if (GetTile(enemy.mDestinationIndex.x - 1, enemy.mDestinationIndex.y)->GetTileType() == TileType::ROAD) {
						enemy.mDirection = 3;
						enemy.mDestinationIndex.x -= 1;
						enemy.mDestination = GetTile(enemy.mDestinationIndex.x, enemy.mDestinationIndex.y)->GetCenterPos();
					}
					else if (GetTile(enemy.mDestinationIndex.x, enemy.mDestinationIndex.y - 1)->GetTileType() == TileType::ROAD) {
						enemy.mDirection = 2;
						enemy.mDestinationIndex.y -= 1;
						enemy.mDestination = GetTile(enemy.mDestinationIndex.x, enemy.mDestinationIndex.y)->GetCenterPos();
					}
					else if (GetTile(enemy.mDestinationIndex.x, enemy.mDestinationIndex.y + 1)->GetTileType() == TileType::ROAD) {
						enemy.mDirection = 1;
						enemy.mDestinationIndex.y += 1;
						enemy.mDestination = GetTile(enemy.mDestinationIndex.x, enemy.mDestinationIndex.y)->GetCenterPos();
					}
					else {
						std::cout << "ATTACK";
					}
					break;
				}
			}
		}
	}	
}

