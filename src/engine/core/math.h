#ifndef ENGINE_CORE_MATH_H
#define ENGINE_CORE_MATH_H

// ============================
// @Region: Vec2.
// ============================

typedef union Vec2
{
    struct
    {
        F32 x;
        F32 y;
    };

    F32 v[2];
} 
Vec2;

// ============================
// @Region: Vec3.
// ============================

typedef union Vec3
{
    struct
    {
        F32 x;
        F32 y;
        F32 z;
    };

    struct
    {
        Vec2 xy;
        F32 _z;
    };

    struct
    {
        F32 _x;
        Vec2 yz;
    };
    
    F32 v[3];
}
Vec3;

// ============================
// @Region: Vec4.
// ============================

typedef union Vec4
{
    struct
    {
        F32 x;
        F32 y;
        F32 z;
        F32 w;
    };
    
    struct
    {
        Vec2 xy;
        Vec2 zw;
    };
    
    struct
    {
        Vec3 xyz;
        F32 _w;
    };
    
    struct
    {
        F32 _x;
        Vec3 yzw;
    };

    F32 v[4];
} Vec4;

// ============================
// @Region: Colors. (Vec4)
// ============================

#define Color_White            (Vec4) { 1.000, 1.000, 1.000, 1.000 }
#define Color_White_Faded      (Vec4) { 1.000, 1.000, 1.000, 0.000 }
#define Color_Black            (Vec4) { 0.000, 0.000, 0.000, 1.000 }
#define Color_Corn_Flower_Blue (Vec4) { 0.388, 0.584, 0.933, 1.000 }
#define Color_Blue             (Vec4) { 0.000, 0.000, 1.000, 1.000 }
#define Color_Light_Blue       (Vec4) { 0.300, 0.300, 1.000, 1.000 }
#define Color_Cyan             (Vec4) { 0.000, 1.000, 1.000, 1.000 }
#define Color_Gray             (Vec4) { 0.500, 0.500, 0.500, 1.000 }
#define Color_Dark_Gray        (Vec4) { 0.200, 0.200, 0.200, 1.000 }
#define Color_Green            (Vec4) { 0.000, 1.000, 0.000, 1.000 }
#define Color_Light_Green      (Vec4) { 0.300, 1.000, 0.300, 1.000 }
#define Color_Chill_Green      (Vec4) { 0.047, 0.651, 0.408, 1.000 }
#define Color_Magenta          (Vec4) { 1.000, 0.000, 1.000, 1.000 }
#define Color_Red              (Vec4) { 1.000, 0.000, 0.000, 1.000 }
#define Color_Light_Red        (Vec4) { 1.000, 0.300, 0.300, 1.000 }
#define Color_Yellow           (Vec4) { 1.000, 0.920, 0.016, 1.000 }
#define Color_Orange           (Vec4) { 0.970, 0.600, 0.110, 1.000 }

#endif // ENGINE_CORE_MATH_H.