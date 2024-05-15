#include "Shop.h"

Shop::Shop()
{
	mBuyShopButtons = {

	};
	mUpgradeShopButtons = {

	};
}

Shop::~Shop()
{
}

void Shop::Load()
{
}

void Shop::UpdateBuyShop()
{
}

void Shop::UpdateUpgradeShop()
{
}

void Shop::DrawBuyShop()
{
	DrawRectangle(1000, 0, 400, 1000, GRAY);
}

void Shop::DrawUpgradeShop()
{
}

void Shop::Unload()
{
}
