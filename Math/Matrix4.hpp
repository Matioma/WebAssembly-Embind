
#ifndef MY_MATRIX4
#define MY_MATRIX4

#include <../emscripten/bind.h>
#include <stdlib.h>
#include <iostream>
#include "./Vector3.hpp"
#include <mutex>
using namespace emscripten;

//Row matrices
class Matrix4{
    public:
        std::vector<float> vectorValues;
    public:
        Matrix4();
        Matrix4(std::vector<float> values);
        Matrix4(const Vector3& v1,const Vector3& v2, const Vector3& v3, const Vector3& v4);
        Matrix4(const Matrix4& mat);

        static Matrix4 Identity();



        Matrix4 operator+(const Matrix4& mat2) const;
        Matrix4 operator-(const Matrix4& mat2) const;
        Matrix4 operator*(float value) const;
        Matrix4 operator*(const Matrix4& mat2) const;
};
#endif