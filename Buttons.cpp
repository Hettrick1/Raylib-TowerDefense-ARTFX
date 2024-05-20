#include "Buttons.h"

Buttons::Buttons()
{
}

Buttons::Buttons(Vector2 position, Vector2 size, Color buttonColor, std::string text, Color textColor, int fontSize)
{
	mPosition = position;
	mSize = size;
	mButtonColor = buttonColor;
	mTextColor = textColor;
	mText = text;
	mFontSize = fontSize;
	mIsHovered = false;
	mIsClicked = false;
	mEnable = true;
	mIsActive = true;
	mClickBool = false;
	mTimer = 0.5f;
	mPressedColor = { 128, 128, 128, 255 };
	mHoveredColor = { 220, 220, 220, 255 };
	mDisableColor = { 220, 220, 220 , 150 };
	mOutlineColor = BLACK;
	mSeeText = true;
	mTexture = Texture(); 
	float mTextureSize = 1;
	mBorderThickness = 2;
}

Buttons::Buttons(Rectangle rectangle, Color buttonColor, std::string text, Color textColor, int fontSize)
{
	mPosition = Vector2{ rectangle.x, rectangle.y };
	mSize = Vector2{ rectangle.width, rectangle.height };
	mButtonColor = buttonColor;
	mTextColor = textColor;
	mText = text;
	mFontSize = fontSize;
	mIsHovered = false;
	mIsClicked = false;
	mEnable = true;
	mIsActive = true;
	mClickBool = false;
	mTimer = 0.5f;
	mPressedColor = { 128, 128, 128, 255 };
	mHoveredColor = { 220, 220, 220, 255 };
	mDisableColor = { 55, 55, 55 , 150 };
	mOutlineColor = BLACK;
	mSeeText = true;
	mTexture = Texture();
	float mTextureSize = 1;
	mBorderThickness = 2;
}

Buttons::Buttons(Rectangle rectangle, Color buttonColor, Texture2D& texture, float textureSize)
{
	mPosition = Vector2{ rectangle.x, rectangle.y };
	mSize = Vector2{ rectangle.width, rectangle.height };
	mButtonColor = buttonColor;
	mTextColor = WHITE;
	mText = "";
	mFontSize = 0;
	mIsHovered = false;
	mIsClicked = false;
	mEnable = true;
	mIsActive = true;
	mClickBool = false;
	mTimer = 0.5f;
	mPressedColor = { 128, 128, 128, 255 };
	mHoveredColor = { 220, 220, 220, 255 };
	mDisableColor = { 55, 55, 55 , 150 };
	mOutlineColor = BLACK;
	mSeeText = false;
	mTexture = texture;
	mTextureSize = textureSize;
	mBorderThickness = 2;
}

Buttons::~Buttons()
{
}

void Buttons::SetButtonPosition(Vector2 newPos)
{
	mPosition = newPos;
}

void Buttons::SetButtonColor(Color color){
	mButtonColor = color;
}
void Buttons::SetHoveredColor(Color color) {
	mHoveredColor = color;
}
void Buttons::SetClickedColor(Color color) {
	mPressedColor = color;
}

void Buttons::SetDisableColor(Color color)
{
	color.a = 150;
	color.r -= color.r * 30/100;
	color.g -= color.g * 30/100;
	color.b -= color.b * 30/100;
	mDisableColor = color;
}

void Buttons::SetEnable(bool enable)
{
	mEnable = enable;
}

void Buttons::SetOutlineColor(Color color)
{
	mOutlineColor = color;
}

void Buttons::SetActive(bool isActive)
{
	mIsActive = isActive;
}

void Buttons::SetSeeText(bool text)
{
	mSeeText = text;
}

bool Buttons::GetClickedBool()
{
	return mClickBool;
}

void Buttons::SetClickedBool(bool click)
{
	mClickBool = click;
}
void Buttons::SetHoveredBool(bool hover)
{
	mIsHovered = hover;
}

void Buttons::SetTexture(Texture2D& texture, float size)
{
	mSeeText = false;
	mTextureSize = size;
	mTexture = texture;
}

void Buttons::SetText(std::string text)
{
	mText = text;
}

void Buttons::SetBorderThickness(float thickness)
{
	mBorderThickness = thickness;
}

void Buttons::ResetTimer()
{
	mTimer = 0.5;
	mIsClicked = false;
}

void Buttons::Update()
{
	if (mIsActive && mEnable) {
		Rectangle rect = { mPosition.x, mPosition.y, mSize.x, mSize.y };
		if (CheckCollisionPointRec(GetMousePosition(), rect)) {
			SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
			mIsHovered = true;
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				mIsClicked = true;
				mClickBool = true;
				mTimer = 0.5f;
			}
		}
		else if (mIsHovered) {
			SetMouseCursor(MOUSE_CURSOR_DEFAULT);
			mIsHovered = false;
		}
		if (mIsClicked) {
			float deltaTime = GetFrameTime();
			mTimer -= deltaTime;
			if (mTimer < 0) {
				mIsClicked = false;
			}
		}
	}
}

void Buttons::Draw()
{
	if (mIsActive) {
		DrawRectangle(mPosition.x, mPosition.y, mSize.x, mSize.y, mButtonColor);
		if (!mEnable) {
			DrawRectangle(mPosition.x, mPosition.y, mSize.x, mSize.y, mDisableColor);
		}
		if (mIsHovered && !mIsClicked) {
			Color color = mHoveredColor;
			DrawRectangle(mPosition.x, mPosition.y, mSize.x, mSize.y, color);
		}
		else {
			Color color = BLANK;
			DrawRectangle(mPosition.x, mPosition.y, mSize.x, mSize.y, color);
		}
		if (mIsClicked && mPressedColor.a != 0) {
			Color color = mPressedColor;
			color.a += 500 * mTimer;
			color.a = (color.a < 0) ? 0 : color.a;
			DrawRectangle(mPosition.x, mPosition.y, mSize.x, mSize.y, color);
		}
		DrawRectangleLinesEx({ mPosition.x, mPosition.y, mSize.x, mSize.y }, mBorderThickness, mOutlineColor);
		if (!mSeeText) {
			DrawTextureEx(mTexture, Vector2{ mPosition.x + (mSize.x - mTexture.width) / 2.0f, mPosition.y + (mSize.y - mTexture.height) / 2.0f }, 0, mTextureSize, WHITE);
		}
		if (mSeeText) {
			float textWidth = MeasureTextEx(GetFontDefault(), mText.c_str(), mFontSize, 3).x;
			float textHeight = MeasureTextEx(GetFontDefault(), mText.c_str(), mFontSize, 3).y;

			if (textWidth > mSize.x) {
				textWidth = mSize.x;
			}

			float textX = mPosition.x + (mSize.x - textWidth) / 2.0f;
			float textY = mPosition.y + (mSize.y - textHeight) / 2.0f;

			DrawTextEx(GetFontDefault(), mText.c_str(), Vector2{ textX, textY }, mFontSize, 3, mTextColor);
		}
	}
}

void Buttons::Unload()
{
	UnloadTexture(mTexture);
}

