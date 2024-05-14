#include "raylib.h"
#include "MapManager.h"
#include "Enemy.h"
#include <vector>
#include <iostream>

MapManager map;
std::vector<Enemy> enemies;

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
    InitWindow(1000, 1000, "Bloons TD 8");
    SetTargetFPS(60);
    map.Load();
    enemies = {
    Enemy(map.GetTile(map.GetSpawnTileIndex().x, map.GetSpawnTileIndex().y)->GetCenterPos(), map.GetSpawnTileIndex())
    };
}

void Start()
{
}

void Update()
{
    for (Enemy& enemy : enemies) {
        enemy.Update(map);
    }
}

void Draw()
{
    BeginDrawing();
    ClearBackground(Color({ 255, 255, 255, 255 }));
    map.Draw();
    for (Enemy& enemy : enemies) {
        enemy.Draw();
    }
    EndDrawing();
}

void Unload()
{
    CloseWindow();
}