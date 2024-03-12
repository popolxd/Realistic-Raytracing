#ifndef MYMATH_H
#define MYMATH_H

#include "raylib.h"
#include <stdint.h>

#define square(x) ((x)*(x))
#define define_GetMultipliedVec(vec, value) (Vector3){vec.x*value, vec.y*value, vec.z*value}
#define define_GetMulitpliedVecByVec(vec, value) (Vector3){vec.x*value.x, vec.y*value.y, vec.z*value.z}
#define define_GetSubtractedVec(vec, values) (Vector3){vec.x-values.x, vec.y-values.y, vec.z-values.z}
#define define_GetAddedVec(vec, values) (Vector3){vec.x+values.x, vec.y+values.y, vec.z+values.z}

#define define_AddToVec(vec, values) vec.x += values.x; vec.y += values.y; vec.z += values.z
#define define_SubtractFromVec(vec, values) vec.x -= values.x; vec.y -= values.y; vec.z -= values.z
#define define_MultiplyVecBy(vec, value) vec.x *= value; vec.y *= value; vec.z *= value
#define define_MultiplyVecByVec(vec, value) vec.x *= value.x; vec.y *= value.y; vec.z *= value.z

#define define_DotProd(vec1, vec2) (vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z)
#define define_CrossProd(vec1, vec2) (Vector3){vec1.y*vec2.z - vec1.z*vec2.y, vec1.z*vec2.x - vec1.x*vec2.z, vec1.x*vec2.y - vec1.y*vec2.x}

#define define_GetRandomUnitFloat() ((float)rand() / (float)RAND_MAX)

Vector3 MY3DLIB_MATH_GetMultipliedVec(Vector3 vec, float value);
Vector3 MY3DLIB_MATH_GetMultipliedVecByVec(Vector3 vec, Vector3 value);
Vector3 MY3DLIB_MATH_GetSubtractedVec(Vector3 vec, Vector3 values);
Vector3 MY3DLIB_MATH_GetAddedVec(Vector3 vec, Vector3 values);

void MY3DLIB_MATH_AddToVec(Vector3* vec, Vector3 values);
void MY3DLIB_MATH_SubtractFromVec(Vector3* vec, Vector3 values);
void MY3DLIB_MATH_MultiplyVecBy(Vector3* vec, float value);
void MY3DLIB_MATH_MultiplyVecByVec(Vector3* vec, Vector3 value);

float MY3DLIB_MATH_DotProd(Vector3 vec1, Vector3 vec2);
Vector3 MY3DLIB_MATH_CrossProd(Vector3 vec1, Vector3 vec2);

Vector3 MY3DLIB_MATH_GetNormalizedVec(Vector3 vec);

Vector3 MY3DLIB_MATH_GetRotatedVecXAxis(Vector3 vec, float angle);
Vector3 MY3DLIB_MATH_GetRotatedVecYAxis(Vector3 vec, float angle);
Vector3 MY3DLIB_MATH_GetRotatedVecZAxis(Vector3 vec, float angle);

Vector3 MY3DLIB_MATH_GetReflectedVecAlongNormal(Vector3 vec, Vector3 normal);
Vector3 MY3DLIB_MATH_GetReflectedVecInRandomDir(Vector3 vec, Vector3 normal);
Vector3 MY3DLIB_MATH_GetVecInBetween(Vector3 vec1, Vector3 vec2, float distFromPoint1);

Vector3 MY3DLIB_MATH_GetRefractedVec(Vector3 rayDir, float currentRefractionIndex, float newRefractionIndex, Vector3 normal);

float MY3DLIB_MATH_GetRandomUnitFloat();
float MY3DLIB_MATH_GetRandomFloatNormalDistr();

Vector3 MY3DLIB_MATH_GetInUnitCircle();
#endif