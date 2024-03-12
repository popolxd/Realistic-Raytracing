#include "level.h"
#include "player.h"
#include "mymath.h"
#include "collisions.h"
#include "main.h"
#include "save.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>

#define USE_DOF 0
#define USE_REFRACTION 0

void LEVEL_InitLevel1(LEVEL_Level* level, PLAYER_Player* player)
{
    level->objectsLen = 4;
    level->objects = (LEVEL_Object*)malloc(sizeof(LEVEL_Object)*level->objectsLen);

    // level->objects[0].shape.disk = (LEVEL_Disk){(Vector3){0, -5, 10}, (Vector3){0, 0, 1}, 3};
    level->objects[0].shape.triangle.vertices[0] = (Vector3){0, -5, 10};
    level->objects[0].shape.triangle.vertices[1] = (Vector3){2, -3, 10};
    level->objects[0].shape.triangle.vertices[2] = (Vector3){-1, -2, 10};
    level->objects[0].type = TRIANGLE;
    level->objects[0].albedo = (Vector3){1, 1, 1};
    level->objects[0].roughness = 0;
    level->objects[0].specularChance = 0;
    level->objects[0].specularColor = (Vector3){1, 1, 1};
    level->objects[0].emissionColor = (Vector3){1, 1, 1};
    level->objects[0].emissionPower = 4;
    level->objects[0].transparency = 0;
    level->objects[0].refractiveIndex = 1;

    level->objects[1].shape.plane = (LEVEL_Plane){(Vector3){0, 1, 0}, (Vector3){0, -1, 0}};
    level->objects[1].type = PLANE;
    level->objects[1].albedo = (Vector3){0.1, 0.8, 0.1};
    level->objects[1].roughness = 1;
    level->objects[1].specularChance = 0;
    level->objects[1].specularColor = (Vector3){1, 1, 1};
    level->objects[1].emissionColor = (Vector3){0, 0, 0};
    level->objects[1].emissionPower = 0;
    level->objects[1].transparency = 0;
    level->objects[1].refractiveIndex = 1;

    level->objects[2].shape.sphere = (LEVEL_Sphere){(Vector3){0, 0, 3}, 1};
    level->objects[2].type = SPHERE;
    level->objects[2].albedo = (Vector3){0.5, 0.5, 0.8};
    level->objects[2].roughness = 0.1;
    level->objects[2].specularChance = 0.3;
    level->objects[2].specularColor = (Vector3){1, 1, 1};
    level->objects[2].emissionColor = (Vector3){1, 1, 1};
    level->objects[2].emissionPower = 0;
    level->objects[2].transparency = 0;
    level->objects[2].refractiveIndex = 1;

    level->objects[3].shape.sphere = (LEVEL_Sphere){(Vector3){3, 0, 6}, 1};
    level->objects[3].type = SPHERE;
    level->objects[3].albedo = (Vector3){0.8, 0.5, 0.5};
    level->objects[3].roughness = 0.3;
    level->objects[3].specularChance = 0.2;
    level->objects[3].specularColor = (Vector3){1, 1, 1};
    level->objects[3].emissionColor = (Vector3){1, 1, 1};
    level->objects[3].emissionPower = 0;
    level->objects[3].transparency = 0;
    level->objects[3].refractiveIndex = 1;

    level->skyLightColor = (Vector3){0.6, 0.6, 0.6};
    level->skyLightIntensity = 0;

    PLAYER_InitPlayer(player, (Vector3){0, 0, 0}, 1, 1);

    level->currentAccumulationFrame = 0;

    level->accumulationMap = (Vector3**)malloc(sizeof(Vector3*)*player->numOfRays.y);
    level->rayDirStorage = (Vector3**)malloc(sizeof(Vector3*)*player->numOfRays.y);

    for (int i = 0; i < player->numOfRays.y; i++) {
        level->accumulationMap[i] = (Vector3*)malloc(sizeof(Vector3)*player->numOfRays.x);
        level->rayDirStorage[i] = (Vector3*)malloc(sizeof(Vector3)*player->numOfRays.x);

        for (int j = 0; j < player->numOfRays.x; j++) {
            level->accumulationMap[i][j] = (Vector3){0, 0, 0};
        }
    }
}

void LEVEL_UpdateLevel1(LEVEL_Level* level, PLAYER_Player* player)
{
    PLAYER_MovePlayer(player);

     // reset the accumulation
    if (player->speed.x != 0 || player->speed.z != 0 || player->speed.z != 0 || player->angularSpeed.x != 0 || player->angularSpeed.y != 0) {
        level->currentAccumulationFrame = 0;
        for (int i = 0; i < player->numOfRays.y; i++) {
            for (int j = 0; j < player->numOfRays.x; j++) {
                level->accumulationMap[i][j] = (Vector3){0, 0, 0};
            }
        }
    }

    if (IsKeyPressed(KEY_P)) {
        char fileName[20] = "first.txt";
        SAVE_SaveAccumulationMap(level->accumulationMap, player->numOfRays, level->currentAccumulationFrame, fileName);
    }

    level->currentAccumulationFrame++;
    
    LEVEL_UpdatePixelsLevel1(level, player);
}

void LEVEL_UpdatePixelsLevel1(LEVEL_Level* level, PLAYER_Player* player)
{

    Vector3 rayDir, pixelColor;
    float heightOverWidth = (float)SCREEN_HEIGHT/SCREEN_WIDTH;
    float tanOfFov = tan(player->fov/2);
    #if USE_DOF
        Vector3 newOrigin, convergencePoint, nudge;
    #endif

    for (int i = 0; i < player->numOfRays.y; i++) {
        for (int j = 0; j < player->numOfRays.x; j++) {

            if (level->currentAccumulationFrame == 1) { // hrac sa pohol
                rayDir = MY3DLIB_MATH_GetNormalizedVec((Vector3){
                    -tanOfFov + ((j+0.5)/player->numOfRays.x)*2*tanOfFov,
                    -heightOverWidth*tanOfFov + ((i+0.5)/player->numOfRays.y)*2*heightOverWidth*tanOfFov,
                    1
                });
                rayDir = MY3DLIB_MATH_GetRotatedVecYAxis(MY3DLIB_MATH_GetRotatedVecXAxis(rayDir, player->rotation.x), player->rotation.y); // getting ray into correct direction
                level->rayDirStorage[i][j] = rayDir;

            } else {
                rayDir = level->rayDirStorage[i][j];
            }

            #if USE_DOF
                convergencePoint = define_GetMultipliedVec(rayDir, player->focalDist);
                define_AddToVec(convergencePoint, player->pos);

                nudge = MY3DLIB_MATH_GetInUnitCircle();
                define_MultiplyVecBy(nudge, player->blurriness);

                newOrigin = MY3DLIB_MATH_GetRotatedVecYAxis(MY3DLIB_MATH_GetRotatedVecXAxis(nudge, player->rotation.x), player->rotation.y);
                define_AddToVec(newOrigin, player->pos);

                rayDir = define_GetSubtractedVec(convergencePoint, newOrigin);
                rayDir = MY3DLIB_MATH_GetNormalizedVec(rayDir);

                pixelColor = LEVEL_ReturnPixel(level, player, newOrigin, rayDir, j, i);
            #else
                pixelColor = LEVEL_ReturnPixel(level, player, player->pos, rayDir, j, i);
            #endif

            define_AddToVec(level->accumulationMap[i][j], pixelColor);
            float divisor = (float)1/level->currentAccumulationFrame;
            DrawRectangle(j*player->raySize, i*player->raySize, player->raySize, player->raySize, LEVEL_ToneMapAndConvert(define_GetMultipliedVec(level->accumulationMap[i][j], divisor)));

        }
    }
}

Vector3 LEVEL_ReturnPixel(LEVEL_Level* level, PLAYER_Player* player, Vector3 rayOrigin, Vector3 rayDir, int xIndex, int yIndex)
{
    Vector3 currentRayOrigin = rayOrigin;
    Vector3 currentRayDir = rayDir;
    #if USE_REFRACTION
        float currentRefractiveIndex = 1;
    #endif

    Vector3 light = (Vector3){0, 0, 0};
    Vector3 contribution = (Vector3){1, 1, 1};

    Vector3 diffuseDir, specularDir, skyLight, collisionPoint, emissionLight, nudge;

    // uint32_t randomSeed = (((level->currentAccumulationFrame*SCREEN_HEIGHT + yIndex)*SCREEN_WIDTH + xIndex)*player->numOfBounces)*2; // (yIndex, xIndex, currentBounce, specific random func)

    LEVEL_CollisionInfo collisionInfo;

    for (int i = 0; i < player->numOfBounces; i++) {
        LEVEL_GetCollisionInfo(level, currentRayOrigin, currentRayDir, &collisionInfo);

        if (collisionInfo.collisionDist == INFINITY) { // no more collisions found
            skyLight = define_GetMultipliedVec(level->skyLightColor, level->skyLightIntensity);
            define_MultiplyVecByVec(skyLight, contribution);
            define_AddToVec(light, skyLight);
            break;
        };

        collisionPoint = define_GetMultipliedVec(currentRayDir, collisionInfo.collisionDist);
        nudge = define_GetMultipliedVec(collisionInfo.normal, EPSILON);

        define_AddToVec(currentRayOrigin, collisionPoint);

        // randNum = MY3DLIB_MATH_GetFastRandomUnitFloat(&randomSeed);

        if (define_GetRandomUnitFloat() >= collisionInfo.specularChance) { // nie je specular bounce

            if (define_GetRandomUnitFloat() >= collisionInfo.transparency) { // neprechadza cez material, je diffuse
                // currentRayDir = MY3DLIB_MATH_GetFastReflectedVecInRandomDir(currentRayDir, collisionInfo.normal, &randomSeed);
                currentRayDir = MY3DLIB_MATH_GetReflectedVecInRandomDir(currentRayDir, collisionInfo.normal);
                define_AddToVec(currentRayOrigin, nudge);

            } else { // refraction happening
                #if USE_REFRACTION
                    if (currentRefractiveIndex == 1) { // docasne riesenie
                        currentRayDir = MY3DLIB_MATH_GetRefractedVec(rayDir, currentRefractiveIndex, collisionInfo.refractiveIndex, collisionInfo.normal);
                        currentRefractiveIndex = collisionInfo.refractiveIndex;
                    } else {
                        currentRayDir = MY3DLIB_MATH_GetRefractedVec(rayDir, collisionInfo.refractiveIndex, 1, collisionInfo.normal);
                        currentRefractiveIndex = 1;
                    }
                #endif

                define_SubtractFromVec(currentRayOrigin, nudge);
            }

            define_MultiplyVecByVec(contribution, collisionInfo.albedo);

        } else { // je specular bounce
            // diffuseDir = MY3DLIB_MATH_GetFastReflectedVecInRandomDir(currentRayDir, collisionInfo.normal, &randomSeed);
            diffuseDir = MY3DLIB_MATH_GetReflectedVecInRandomDir(currentRayDir, collisionInfo.normal);
            specularDir = MY3DLIB_MATH_GetReflectedVecAlongNormal(currentRayDir, collisionInfo.normal);

            currentRayDir = MY3DLIB_MATH_GetVecInBetween(specularDir, diffuseDir, collisionInfo.roughness);
            define_MultiplyVecByVec(contribution, collisionInfo.specularColor);
            define_AddToVec(currentRayOrigin, nudge);
        }

        emissionLight = define_GetMultipliedVec(collisionInfo.emissionColor, collisionInfo.emissionPower);
        define_MultiplyVecByVec(emissionLight, contribution);
        define_AddToVec(light, emissionLight);
    }
    
    return light;
}

void LEVEL_GetCollisionInfo(LEVEL_Level* level, Vector3 rayOrigin, Vector3 rayDir, LEVEL_CollisionInfo* collisionInfo)
{
    collisionInfo->collisionDist = INFINITY;
    Vector3 normal;

    float collisionDist;
    for (int i = 0; i < level->objectsLen; i++) {
        switch (level->objects[i].type) {
            case SPHERE:
                collisionDist = COLLISIONS3D_RaySphereIntersectionEx(rayOrigin, rayDir, level->objects[i].shape.sphere.pos, level->objects[i].shape.sphere.radius, &normal);
                break;
            case PLANE:
                collisionDist = COLLISIONS3D_RayPlaneIntersectionEx(rayOrigin, rayDir, level->objects[i].shape.plane.point, level->objects[i].shape.plane.normal, &normal);
                break;
            case DISK:
                collisionDist = COLLISIONS3D_RayDiskIntersectionEx(rayOrigin, rayDir, level->objects[i].shape.disk.pos, level->objects[i].shape.disk.normal, level->objects[i].shape.disk.radius, &normal);
                break;
            case TRIANGLE:
                collisionDist = COLLISIONS3D_RayTriangleIntersectionEx(rayOrigin, rayDir, level->objects[i].shape.triangle.vertices, &normal);
                break;
        }

        if (collisionDist < collisionInfo->collisionDist) {
            collisionInfo->collisionDist = collisionDist;
            collisionInfo->normal = normal;
            collisionInfo->albedo = level->objects[i].albedo;
            collisionInfo->roughness = level->objects[i].roughness;
            collisionInfo->specularChance = level->objects[i].specularChance;
            collisionInfo->specularColor = level->objects[i].specularColor;
            collisionInfo->emissionColor = level->objects[i].emissionColor;
            collisionInfo->emissionPower = level->objects[i].emissionPower;
            collisionInfo->transparency = level->objects[i].transparency;
            collisionInfo->refractiveIndex = level->objects[i].refractiveIndex;
        }
    }
}

#define maxSceneLuminanceSquared square(10)

Color LEVEL_ToneMapAndConvert(Vector3 color)
{
    // channel-wise clamp
    return (Color){
        ((color.x > 1) ? 1 : color.x) * 255,
        ((color.y > 1) ? 1 : color.y) * 255,
        ((color.z > 1) ? 1 : color.z) * 255,
        255
    };
}