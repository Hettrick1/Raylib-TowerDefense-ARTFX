#include "raylib.h"
#include <iostream>

void Load();
void Start();
void Update();
void Draw();
void Unload();

int main() {
    Load();
    Start();
    while (!WindowShouldClose())
    {
        Update();
        Draw();
    }
    Unload();
    return 0;
}
void Load()
{
    InitWindow(1080, 720, "Bloons TD 8");
    SetTargetFPS(60);
}

void Start()
{
}

void Update()
{
}

void Draw()
{
    BeginDrawing();
    ClearBackground(Color({ 255, 255, 255, 255 }));
    EndDrawing();
}

void Unload()
{
    CloseWindow();
}