#ifndef MY_VECTOR3
#define MY_VECTOR3

#include <../emscripten/bind.h>


using namespace emscripten;

struct Vector3 {
    public:
        float x;
        float y;
        float z;

    public:
        Vector3();
        Vector3(const Vector3& vec2 );
        Vector3(float x, float y, float z);
       

        float Magnitude() const;
        float SqrMagnitude() const;

        Vector3 Normalized() const;
        bool Normalize();

        static float Dot(const Vector3& vec1, const Vector3& vec2);
        static Vector3 Cross(const Vector3& vec1, const Vector3& vec2);

        Vector3 operator+( const Vector3& vec2) const;
        Vector3 operator-( const Vector3& vec2) const;
        Vector3 operator*(float value) const;
        void operator=(const Vector3& vec2);
        bool operator==(const Vector3& vec2) const;
};
#endif