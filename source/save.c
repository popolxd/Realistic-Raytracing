#include "save.h"
#include "raylib.h"
#include <stdio.h>

void SAVE_SaveAccumulationMap(Vector3** accumulationMap, Vector2 numOfRays, int currentAccumulationFrame, char filename[20])
{

    FILE* filePtr = fopen(filename, "w");

    fprintf(filePtr, "%d %d\n", (int)numOfRays.x, (int)numOfRays.y);

    for (int i = 0; i < numOfRays.y; i++) {

        for (int j = 0; j < numOfRays.x; j++) {
            fprintf(filePtr, "%f %f %f\n", accumulationMap[i][j].x/currentAccumulationFrame, accumulationMap[i][j].y/currentAccumulationFrame, accumulationMap[i][j].z/currentAccumulationFrame);
        }
    }
    fclose(filePtr);
}