#pragma once

#include "raylib.h"
#include <iostream>

class Buttons
{
private:
    Vector2 mPosition;
    Vector2 mSize;
    Color mButtonColor;
    Color mTextColor;
    Color mOutlineColor;
    std::string mText;
    int mFontSize;
    bool mIsHovered;
    bool mIsClicked;
    bool mEnable;
    bool mIsActive;
    bool mClickBool;
    bool mSeeText;
    float mTimer;
    Color mPressedColor;
    Color mHoveredColor;
    Color mDisableColor;
    Texture2D mTexture;
    float mTextureSize;
    float mBorderThickness;
public:
    Buttons();
    Buttons(Vector2 position, Vector2 size, Color buttonColor, std::string text, Color textColor, int fontSize);
    Buttons(Rectangle rectangle, Color buttonColor, std::string text, Color textColor, int fontSize);
    Buttons(Rectangle rectangle, Color buttonColor, Texture2D& texture, float textureSize);
    ~Buttons();
    void SetButtonPosition(Vector2 newPos);
    void SetButtonColor(Color color);
    void SetHoveredColor(Color color);
    void SetClickedColor(Color color);
    void SetDisableColor(Color color);
    void SetOutlineColor(Color color);
    void SetEnable(bool enable);
    void SetActive(bool isActive);
    void SetSeeText(bool text);
    bool GetClickedBool();
    void SetClickedBool(bool click);
    void SetHoveredBool(bool hover);
    void SetTexture(Texture2D& texture, float size);
    void SetText(std::string text);
    void SetBorderThickness(float thickness);
    void ResetTimer();
    void Update();
    void Draw();
    void Unload();
};

