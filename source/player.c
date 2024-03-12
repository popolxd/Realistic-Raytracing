#include "player.h"
#include "raylib.h"
#include "main.h"
#include "mymath.h"

void PLAYER_InitPlayer(PLAYER_Player* player, Vector3 pos, float maxSpeed, float maxAngularSpeed)
{
    player->pos = pos;
    player->rotation = (Vector2){0, 0};
    player->speed = (Vector3){0, 0, 0};
    player->angularSpeed = (Vector2){0, 0};
    player->maxSpeed = maxSpeed;
    player->maxAngularSpeed = maxAngularSpeed;
    player->raySize = 5;
    player->numOfRays = (Vector2){SCREEN_WIDTH/player->raySize, SCREEN_HEIGHT/player->raySize};
    player->fov = PI/2;
    player->numOfBounces = 5;

    player->blurriness = 0.2;
    player->focalDist = 5;
}

void PLAYER_MovePlayer(PLAYER_Player* player)
{
    // player defaultne kuka do z osi kladnym smerom
    if (IsKeyDown(KEY_W)) player->speed.z = player->maxSpeed;
    else if (IsKeyDown(KEY_S)) player->speed.z = -player->maxSpeed;
    else player->speed.z = 0;
    if (IsKeyDown(KEY_A)) player->speed.x = -player->maxSpeed;
    else if (IsKeyDown(KEY_D)) player->speed.x = player->maxSpeed;
    else player->speed.x = 0;

    if (IsKeyDown(KEY_UP)) player->angularSpeed.x = player->maxAngularSpeed;
    else if (IsKeyDown(KEY_DOWN)) player->angularSpeed.x = -player->maxAngularSpeed;
    else player->angularSpeed.x = 0;
    if (IsKeyDown(KEY_LEFT)) player->angularSpeed.y = -player->maxAngularSpeed;
    else if (IsKeyDown(KEY_RIGHT)) player->angularSpeed.y = player->maxAngularSpeed;
    else player->angularSpeed.y = 0;

    player->rotation.x += player->angularSpeed.x*ELAPSED;
    if (player->rotation.x < -PI/2) player->rotation.x = -PI/2;
    else if (player->rotation.x > PI/2) player->rotation.x = PI/2;

    player->rotation.y += player->angularSpeed.y*ELAPSED;

    // otocit to podla rotacie
    Vector3 trueSpeed = MY3DLIB_MATH_GetRotatedVecYAxis(MY3DLIB_MATH_GetRotatedVecXAxis(player->speed, player->rotation.x), player->rotation.y);
    define_MultiplyVecBy(trueSpeed, ELAPSED);

    MY3DLIB_MATH_AddToVec(&player->pos, trueSpeed);
}