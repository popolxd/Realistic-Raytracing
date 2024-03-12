#include "mymath.h"
#include <math.h>
#include <stdlib.h>
#include "raylib.h"
#include <stdint.h>
// #include <immintrin.h>

// general stuff
Vector3 MY3DLIB_MATH_GetMultipliedVec(Vector3 vec, float value)
{
    return (Vector3){vec.x*value, vec.y*value, vec.z*value};
}

Vector3 MY3DLIB_MATH_GetMultipliedVecByVec(Vector3 vec, Vector3 value)
{
    return (Vector3){vec.x*value.x, vec.y*value.y, vec.z*value.z};
}

Vector3 MY3DLIB_MATH_GetSubtractedVec(Vector3 vec, Vector3 values)
{
    return (Vector3){vec.x-values.x, vec.y-values.y, vec.z-values.z};
}

Vector3 MY3DLIB_MATH_GetAddedVec(Vector3 vec, Vector3 values)
{
    return (Vector3){vec.x + values.x, vec.y + values.y, vec.z + values.z};
}

void MY3DLIB_MATH_AddToVec(Vector3* vec, Vector3 values)
{
    vec->x += values.x;
    vec->y += values.y;
    vec->z += values.z;
}

void MY3DLIB_MATH_SubtractFromVec(Vector3* vec, Vector3 values)
{
    vec->x -= values.x;
    vec->y -= values.y;
    vec->z -= values.z;
}

void MY3DLIB_MATH_MultiplyVecBy(Vector3* vec, float value)
{
    vec->x *= value;
    vec->y *= value;
    vec->z *= value;
}

void MY3DLIB_MATH_MultiplyVecByVec(Vector3* vec, Vector3 value)
{
    vec->x *= value.x;
    vec->y *= value.y;
    vec->z *= value.z;
}

Vector3 MY3DLIB_MATH_GetNormalizedVec(Vector3 vec)
{
    float divisor = sqrt(square(vec.x) + square(vec.y) + square(vec.z));
    return (Vector3){vec.x/divisor, vec.y/divisor, vec.z/divisor};
}

float MY3DLIB_MATH_DotProd(Vector3 vec1, Vector3 vec2)
{
    return vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z;
}

Vector3 MY3DLIB_MATH_CrossProd(Vector3 vec1, Vector3 vec2)
{
    return (Vector3){
        vec1.y*vec2.z - vec1.z*vec2.y,
        vec1.z*vec2.x - vec1.x*vec2.z,
        vec1.x*vec2.y - vec1.y*vec2.x
    };
}

Vector3 MY3DLIB_MATH_GetRotatedVecXAxis(Vector3 vec, float angle)
{
    float sinOfAngle = sin(angle);
    float cosOfAngle = cos(angle);
    return (Vector3){
        vec.x,
        vec.y * cosOfAngle - vec.z * sinOfAngle,
        vec.y * sinOfAngle + vec.z * cosOfAngle
    };
}

Vector3 MY3DLIB_MATH_GetRotatedVecYAxis(Vector3 vec, float angle)
{
    float sinOfAngle = sin(angle);
    float cosOfAngle = cos(angle);
    return (Vector3){
        vec.x * cosOfAngle + vec.z * sinOfAngle,
        vec.y,
        - vec.x * sinOfAngle + vec.z * cosOfAngle
    };
}

Vector3 MY3DLIB_MATH_GetRotatedVecZAxis(Vector3 vec, float angle)
{
    float sinOfAngle = sin(angle);
    float cosOfAngle = cos(angle);
    return (Vector3){
        vec.x * cosOfAngle - vec.y * sinOfAngle,
        vec.x * sinOfAngle + vec.y * cosOfAngle,
        vec.z
    };
}

// float MY3DLIB_MATH_GetRandomFloat(float from, float to) {
//     float range = fabs(from - to); // distance between both numbers
//     float randNum = ((float)rand() / (float)RAND_MAX) * range;
//     return randNum + from;
// }

// float MY3DLIB_MATH_GetFastRandomFloat(float from, float to, uint32_t* seed)
// {
//     float range = fabs(from - to);
//     *seed = MY3DLIB_MATH_PCGHash(*seed);

//     float randNum = ((float)MY3DLIB_MATH_PCGHash(*seed) / (float)UINT32_MAX) * range;
//     return randNum + from;
// }

float MY3DLIB_MATH_GetRandomUnitFloat()
{
    return ((float)rand() / (float)RAND_MAX);
}

// float MY3DLIB_MATH_GetFastRandomUnitFloat(uint32_t* seed)
// {
//     *seed = MY3DLIB_MATH_PCGHash(*seed);
//     return ((float)MY3DLIB_MATH_PCGHash(*seed) / (float)UINT32_MAX);
// }

// uint32_t MY3DLIB_MATH_PCGHash(uint32_t seed)
// {
//     uint32_t state = seed * 747796405u + 2891336453u;
//     uint32_t word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
//     return (word >> 22u) ^ word;
// }

float normalNumStorage = INFINITY;

float MY3DLIB_MATH_GetRandomFloatNormalDistr() // this will maybe not work for the multithreading
{
    if (normalNumStorage == INFINITY) {
        float randNum1 = define_GetRandomUnitFloat();
        float randNum2 = define_GetRandomUnitFloat();

        float r = sqrt(-2*log(randNum1));

        normalNumStorage = r*sin(2*PI*randNum2);

        return r*cos(2*PI*randNum2);
    }
    float buff = normalNumStorage;
    normalNumStorage = INFINITY;
    return buff;
}

// float MY3DLIB_MATH_GetFastRandomFloatNormalDistr(uint32_t* seed)
// {
//     if (normalNumStorage == INFINITY) {
//         float randNum1 = MY3DLIB_MATH_GetFastRandomUnitFloat(seed);
//         float randNum2 = MY3DLIB_MATH_GetFastRandomUnitFloat(seed);

//         float r = sqrt(-2*log(randNum1));
//         normalNumStorage = r*sin(2*PI*randNum2);

//         return r*cos(2*PI*randNum2);
//     }
//     float buff = normalNumStorage;
//     normalNumStorage = INFINITY;
//     return buff;
// }


// raytracing specific stuff
Vector3 MY3DLIB_MATH_GetReflectedVecAlongNormal(Vector3 vec, Vector3 normal)
{
    float dotProdTimes2 = 2*define_DotProd(vec, normal);
    Vector3 valueToReverseDir = define_GetMultipliedVec(normal, dotProdTimes2);

    return define_GetSubtractedVec(vec, valueToReverseDir);
}

Vector3 MY3DLIB_MATH_GetReflectedVecInRandomDir(Vector3 vec, Vector3 normal)
{
    Vector3 inUnitSphere = MY3DLIB_MATH_GetNormalizedVec((Vector3){
        MY3DLIB_MATH_GetRandomFloatNormalDistr(),
        MY3DLIB_MATH_GetRandomFloatNormalDistr(),
        MY3DLIB_MATH_GetRandomFloatNormalDistr()
    });

    define_AddToVec(inUnitSphere, normal);
    return MY3DLIB_MATH_GetNormalizedVec(inUnitSphere);
}

// Vector3 MY3DLIB_MATH_GetFastReflectedVecInRandomDir(Vector3 vec, Vector3 normal, uint32_t* seed)
// {
//     Vector3 inUnitSphere = MY3DLIB_MATH_GetNormalizedVec((Vector3){
//         MY3DLIB_MATH_GetFastRandomFloatNormalDistr(seed),
//         MY3DLIB_MATH_GetFastRandomFloatNormalDistr(seed),
//         MY3DLIB_MATH_GetFastRandomFloatNormalDistr(seed)
//     });

//     define_AddToVec(inUnitSphere, normal);
//     return MY3DLIB_MATH_GetNormalizedVec(inUnitSphere);
// }

Vector3 MY3DLIB_MATH_GetVecInBetween(Vector3 vec1, Vector3 vec2, float distFromPoint1)
{
    Vector3 result = define_GetSubtractedVec(vec2, vec1);
    define_MultiplyVecBy(result, distFromPoint1);
    define_AddToVec(result, vec1);

    return MY3DLIB_MATH_GetNormalizedVec(result);
}

// additional stuff
Vector3 MY3DLIB_MATH_GetInUnitCircle()
{
    float randAngle = define_GetRandomUnitFloat() * 2 * PI;
    float len = sqrt(define_GetRandomUnitFloat());

    Vector3 circle = (Vector3){cos(randAngle) * len, sin(randAngle) * len, 0};
    return circle;
    // return MY3DLIB_MATH_GetNormalizedVec((Vector3) {
    //     MY3DLIB_MATH_GetRandomFloatNormalDistr(),
    //     MY3DLIB_MATH_GetRandomFloatNormalDistr(),
    //     0
    // });
}

// Vector3 MY3DLIB_MATH_GetRefractedVec(Vector3 vec, float currentRefractionIndex, float newRefractionIndex, Vector3 normal)
// {
//     float refractionRatio = currentRefractionIndex / newRefractionIndex;
//     float dotprod = MY3DLIB_MATH_DotProd(MY3DLIB_MATH_GetMultipliedVec(vec, -1), normal);
//     return MY3DLIB_MATH_GetSubtractedVec(
//         MY3DLIB_MATH_GetMultipliedVec(
//             MY3DLIB_MATH_GetAddedVec(vec, MY3DLIB_MATH_GetMultipliedVec(normal, dotprod)), refractionRatio
//         ), MY3DLIB_MATH_GetMultipliedVec(
//             normal, sqrt(
//                 1 - square(refractionRatio) * (1 - square(dotprod))
//             )
//         )
//     );
// }

Vector3 MY3DLIB_MATH_GetRefractedVec(Vector3 rayDir, float currentRefractionIndex, float newRefractionIndex, Vector3 normal) {
    float refractionRatio = currentRefractionIndex / newRefractionIndex;
    Vector3 inverseRayDir = define_GetMultipliedVec(rayDir, -1);
    float cos1 = define_DotProd(inverseRayDir, normal); // Cosine of angle of incidence
    float sin1Squared = 1 - square(cos1); // Sine squared of angle of incidence

    float sin2Squared = square(refractionRatio) * sin1Squared; // Sine squared of angle of refraction
    float cos2 = sqrt(1 - sin2Squared); // Cosine of angle of refraction

    // Compute the refracted ray direction
    float value = (refractionRatio * cos1 - cos2);
    Vector3 refractedRay;
    refractedRay.x = refractionRatio * rayDir.x + value * normal.x;
    refractedRay.y = refractionRatio * rayDir.y + value * normal.y;
    refractedRay.z = refractionRatio * rayDir.z + value * normal.z;

    return refractedRay;
}