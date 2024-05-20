#include "raylib.h"
#include "MapManager.h"
#include "WaveManager.h"
#include "Buttons.h"
#include <iostream>

MapManager map;
WaveManager wave;

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
    InitWindow(1300, 1000, "Bloons TD 8");
    SetTargetFPS(60);
    wave.AddMap(&map);
    map.Load();
}

void Start()
{
    wave.CreateNewWave();
}

void Update()
{
    wave.Update();
    map.Update();
}

void Draw()
{
    BeginDrawing();
    ClearBackground(Color({ 255, 255, 255, 255 }));
    map.Draw();
    wave.Draw();
    EndDrawing();
}

void Unload()
{
    map.Unload();
    wave.Unload();
    CloseWindow();
}