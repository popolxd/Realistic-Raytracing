#include "main.h"
#include "raylib.h"
#include "player.h"
#include "level.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int SCREEN_WIDTH;
int SCREEN_HEIGHT;
float ELAPSED;

Vector2 OFF = (Vector2){0, 0};

int main(void)
{
    SCREEN_WIDTH = 1200;
    SCREEN_HEIGHT = 850;
    ELAPSED = 1;

    srand((unsigned int)time(NULL));

    LEVEL_Level level1;
    PLAYER_Player player;

    LEVEL_InitLevel1(&level1, &player);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Test!");

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {
        ELAPSED = GetFrameTime();

        BeginDrawing();
        ClearBackground(BLACK);

        LEVEL_UpdateLevel1(&level1, &player);
        DrawText(TextFormat("%.3f\n", ELAPSED*1000), 20, 20, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}