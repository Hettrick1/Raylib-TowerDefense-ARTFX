#include "raylib.h"
#include "MapManager.h"
#include "WaveManager.h"
#include "Buttons.h"
#include <iostream>

MapManager map;
WaveManager wave;
Buttons button = Buttons({ 500, 450, 300, 100 }, WHITE, "Start Game", BLACK, 40);

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
}

void Start()
{
}

void Update()
{
    if (map.GetLoose()) {
        button.Update();
        DrawText("Bloons TD 8", (1300 - MeasureText("Bloons TD 8", 80)) / 2, 300, 80, WHITE);
        if (button.GetClickedBool()) {
            button.SetClickedBool(false);
            map.Unload();
            map.Load();
            wave.CreateNewWave();
        }
    }
    else {
        wave.Update();
        map.Update();
    }

}

void Draw()
{
    BeginDrawing();
    if (map.GetLoose()) {
        ClearBackground(Color({ 0, 0, 0, 255 }));
        button.Draw();
    }
    else {
        ClearBackground(Color({ 255, 255, 255, 255 }));
        map.Draw();
        wave.Draw();
    }
    
    EndDrawing();
}

void Unload()
{
    map.Unload();
    wave.Unload();
    CloseWindow();
}