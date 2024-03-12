#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "raylib.h"

float COLLISIONS3D_RaySphereIntersection(Vector3 rayOrigin, Vector3 rayDir, Vector3 spherePos, float radius);
float COLLISIONS3D_RaySphereIntersectionEx(Vector3 rayOrigin, Vector3 rayDir, Vector3 spherePos, float radius, Vector3* normal);

float COLLISIONS3D_RayPlaneIntersection(Vector3 rayOrigin, Vector3 rayDir, Vector3 planePoint, Vector3 planeNormal);
float COLLISIONS3D_RayPlaneIntersectionEx(Vector3 rayOrigin, Vector3 rayDir, Vector3 planePoint, Vector3 planeNormal, Vector3* normal);

float COLLISIONS3D_RayDiskIntersection(Vector3 rayOrigin, Vector3 rayDir, Vector3 diskOrigin, Vector3 diskNormal, float radius);
float COLLISIONS3D_RayDiskIntersectionEx(Vector3 rayOrigin, Vector3 rayDir, Vector3 diskOrigin, Vector3 diskNormal, float radius, Vector3* normal);

float COLLISIONS3D_RayTriangleIntersection(Vector3 rayOrigin, Vector3 rayDir, Vector3 vertices[3]);
float COLLISIONS3D_RayTriangleIntersectionEx(Vector3 rayOrigin, Vector3 rayDir, Vector3 vertices[3], Vector3* normal);

#endif