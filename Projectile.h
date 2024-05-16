#pragma once
#include "raylib.h"

struct Projectile {
    Vector2 startPosition;
    Vector2 position;
    Vector2 velocity;
    float range;
    bool isDestroyed;
};