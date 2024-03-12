#ifndef LEVEL_H
#define LEVEL_H

#include "raylib.h"
#include "player.h"

typedef struct {
    float r, g, b, a;
} LEVEL_FloatColor;

typedef struct {
    Vector3 pos;
    float radius;
} LEVEL_Sphere;

typedef struct {
    Vector3 point;
    Vector3 normal;
} LEVEL_Plane;

typedef struct {
    Vector3 pos;
    Vector3 normal;
    float radius;
} LEVEL_Disk;

typedef struct triangle {
    Vector3 vertices[3];
} LEVEL_Triangle;

typedef union {
    LEVEL_Sphere sphere;
    LEVEL_Plane plane;
    LEVEL_Disk disk;
    LEVEL_Triangle triangle;
} LEVEL_ObjectShape;

typedef enum {
    SPHERE,
    PLANE,
    DISK,
    TRIANGLE
} LEVEL_ObjectType;

typedef struct {
    float collisionDist;
    Vector3 normal;

    Vector3 albedo;
    float roughness;

    float specularChance;
    Vector3 specularColor;

    float transparency;
    float refractiveIndex;

    Vector3 emissionColor;
    float emissionPower;
} LEVEL_CollisionInfo;

typedef struct {
    LEVEL_ObjectShape shape;
    LEVEL_ObjectType type;

    Vector3 albedo;
    float roughness;

    Vector3 specularColor;
    float specularChance;

    float transparency;
    float refractiveIndex;

    Vector3 emissionColor;
    float emissionPower;

} LEVEL_Object;

typedef struct {
    LEVEL_Object* objects;
    int objectsLen;

    Vector3 skyLightColor;
    float skyLightIntensity;

    int currentAccumulationFrame;
    Vector3** accumulationMap;

    Vector3** rayDirStorage;
    float** distanceMap;
} LEVEL_Level;


typedef struct {
    int from, to;
    LEVEL_Level* level;
    PLAYER_Player* player;
} LEVEL_ArgPackage;

void LEVEL_InitLevel1(LEVEL_Level* level, PLAYER_Player* player);

void LEVEL_UpdateLevel1(LEVEL_Level* level, PLAYER_Player* player);
void LEVEL_UpdatePixelsLevel1(LEVEL_Level* level, PLAYER_Player* player);

Vector3 LEVEL_ReturnPixel(LEVEL_Level* level, PLAYER_Player* player, Vector3 rayOrigin, Vector3 rayDir, int xIndex, int yIndex);
void LEVEL_GetCollisionInfo(LEVEL_Level* level, Vector3 rayOrigin, Vector3 rayDir, LEVEL_CollisionInfo* collisionInfo);

Color LEVEL_ToneMapAndConvert(Vector3 color);

#endif