#include "MapManager.h"

MapManager::MapManager()
{
	mMapImage = Image();
	mMapIndex = 1;
	mSpawnIndex = {0,0};
	mTileClickedIndex = {0,0};
	mShowBuyShop = false;
	mLoose = true;
	mBuyShopButtons = {
		Buttons({1050, 250, 200, 200}, YELLOW, "Turret 1", BLACK, 30),
		Buttons({1050, 550, 200, 200}, YELLOW, "Turret 2", BLACK, 30),
		Buttons({1050, 850, 200, 50}, RED, "Quit shop", BLACK, 30)
	};
	mUpgradeShopButtons = {

	};
	mDartMonkeyTexture = Texture2D();
	mTackShooterTexture = Texture2D();
	mBloonTexture = Texture2D();
	mCastleTexture = Texture2D();
}

MapManager::~MapManager()
{
}

void MapManager::Load()
{
	mShowBuyShop = false;
	mLoose = false;
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
			else if (colors[index].b == 255 && colors[index].r == 255 && colors[index].g == 255) {
				mMap[i][j]->ChangeType(TileType::GRASS);
				mCastlePos = mMap[i][j]->GetCenterPos();
			}
			index += 1;
		}
	}
	UnloadImageColors(colors);
	UnloadImage(mMapImage);
	mDartMonkeyTexture = LoadTexture("resources/sprites/DartMonkey.png");
	mTackShooterTexture = LoadTexture("resources/sprites/TackShooter.png");
	mBloonTexture = LoadTexture("resources/sprites/bloons.png");
	mCastleTexture = LoadTexture("resources/sprites/Castle.png");
	ResetLife();
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
	for (DartMonkey& turret : mDartMonkeyTurrets) {
		if (mEnemies.size() > 0) {
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
		}
		else {
			turret.SetCanShoot(false);
		}
		turret.Update();
	}
	for (TackShooter& turret : mTackShooterTurrets) {
		if (mEnemies.size() > 0) {
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
		}
		else {
			turret.SetCanShoot(false);
		}
		turret.Update();
	}
	MoveEnemies();
	if (AreAllEnemiesDead()) {
		mEnemies.clear();
	}
	if (Getlife() <= 0) {
		mLoose = true;
		mEnemies.clear();
		mTackShooterTurrets.clear();
		mDartMonkeyTurrets.clear();

	}
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
		button.SetHoveredBool(false);
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
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
	else {
		DrawText(TextFormat("%i", GetMoney()), GetMoneyPos().x, GetMoneyPos().y, 50, BLACK);
		DrawText(TextFormat("%i", Getlife()), GetMoneyPos().x + MeasureText(TextFormat("%i", Getlife()), 50)/2, GetMoneyPos().y + 150, 50, RED);
	}
	for (DartMonkey& turret : mDartMonkeyTurrets) {
		turret.Draw();
	}
	for (TackShooter& turret : mTackShooterTurrets) {
		turret.Draw();
	}
	for (Enemy& enemy : mEnemies) {
		if (!enemy.mIsDead) {
			DrawTexture(mBloonTexture,enemy.mPosition.x - mBloonTexture.width/2, enemy.mPosition.y - mBloonTexture.height/2, WHITE);
		}
	}
	SetMoneyPos({ (float)(1150 - MeasureText(TextFormat("%i", GetMoney()), 50) / 2), GetMoneyPos().y });
	DrawTextureEx(mCastleTexture, { mCastlePos.x - mCastleTexture.width / 2, mCastlePos.y - mCastleTexture.height / 2 }, 0 ,1,WHITE);
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
	UnloadTexture(mDartMonkeyTexture);
	UnloadTexture(mTackShooterTexture);
	UnloadTexture(mBloonTexture);
	UnloadTexture(mCastleTexture);
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

void MapManager::CreateNewEnemy(int wave)
{
	Enemy newEnemy;

	newEnemy.mCoins = 100;
	newEnemy.mDamage = 0 + wave;
	newEnemy.mDestination = GetTile((int)mSpawnIndex.x, (int)mSpawnIndex.y)->GetCenterPos();
	newEnemy.mDestinationIndex = mSpawnIndex;
	newEnemy.mDirection = 0;
	newEnemy.mHealth = 0 + wave;
	newEnemy.mSpawnPos = GetTile((int)mSpawnIndex.x, (int)mSpawnIndex.y)->GetCenterPos();
	newEnemy.mPosition = { (float)newEnemy.mSpawnPos.x - 10, (float)newEnemy.mSpawnPos.y };
	newEnemy.mSpeed = 80 + wave * 10;
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
					else { //ATTACK
						enemy.mIsDead = true;
						AddLife(-enemy.mDamage);
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
					else { //ATTACK
						enemy.mIsDead = true;
						AddLife(-enemy.mDamage);
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
					else { //ATTACK
						enemy.mIsDead = true;
						AddLife(-enemy.mDamage);
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
					else { //ATTACK
						enemy.mIsDead = true;
						AddLife(-enemy.mDamage);
					}
					break;
				}
			}
		}
	}	
}

int MapManager::GetEnemiesRemaining()
{
	return mEnemies.size();
}

bool MapManager::AreAllEnemiesDead()
{
	for (Enemy& enemy : mEnemies) {
		if (!enemy.mIsDead) {
			return false;
		}
	}
	return true;
}

bool MapManager::GetShowBuyShop()
{
	return mShowBuyShop;
}

bool MapManager::GetLoose()
{
	return mLoose;
}

