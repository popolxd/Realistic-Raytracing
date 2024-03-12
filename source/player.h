#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct {
    Vector3 pos;
    Vector2 rotation; // around x and y axis

    Vector3 speed;
    Vector2 angularSpeed;

    float maxSpeed;
    float maxAngularSpeed;

    int raySize;
    Vector2 numOfRays;
    int numOfBounces;
    
    float fov; // calculated from width;
    float blurriness;
    float focalDist;
} PLAYER_Player;

void PLAYER_InitPlayer(PLAYER_Player* player, Vector3 pos, float maxSpeed, float maxAngularSpeed);
void PLAYER_MovePlayer(PLAYER_Player* player);

#endif