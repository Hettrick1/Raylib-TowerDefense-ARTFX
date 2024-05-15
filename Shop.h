#pragma once
#include "Buttons.h"
#include <vector>
class Shop
{
private:
	std::vector<Buttons> mBuyShopButtons;
	std::vector<Buttons> mUpgradeShopButtons;
public:
	Shop();
	~Shop();
	void Load();
	void UpdateBuyShop();
	void UpdateUpgradeShop();
	void DrawBuyShop();
	void DrawUpgradeShop();
	void Unload();
};