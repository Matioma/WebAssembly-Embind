#include "./Vector3.hpp"

Vector3::Vector3():x(0),y(0),z(0){
}

Vector3:: Vector3(float x, float y, float z):x(x),y(y),z(z){
}

Vector3::Vector3(const Vector3& vec2){
    this->x = vec2.x;
    this->y = vec2.y;
    this->z = vec2.z;
}

float Vector3::Magnitude() const{
    return sqrt(SqrMagnitude());
}

float Vector3::SqrMagnitude() const{
    return (this->x*this->x) + (this->y*this->y) +(this->z*this->z);
}

Vector3 Vector3::Normalized() const{
    Vector3 vec(0,0,0);
    float magnitude = this->Magnitude();
    if(magnitude ==0) return vec;

    vec = (*this)* (1/magnitude);
    return vec;
}

bool Vector3::Normalize(){
    float magnitude = this->Magnitude();
    if(magnitude == 0) return false;

    *this = (*this)* (1/magnitude);
    return true;
}

float Vector3::Dot(const Vector3& vec1, const Vector3& vec2){
    return (vec1.x * vec2.x + vec1.y*vec2.y + vec1.z*vec2.z);
}

Vector3 Vector3::Cross(const Vector3& vec1, const Vector3& vec2){
    Vector3 vector(0,0,0);
    vector.x = vec1.y*vec2.z - vec1.z*vec2.y;
    vector.y =vec1.z*vec2.x - vec1.x*vec2.z;
    vector.z = vec1.x*vec2.y - vec1.y*vec2.x;

    return vector;
}

Vector3 Vector3::operator+( const Vector3& vec2) const{
    Vector3 vec(0,0,0);
    vec.x = this->x + vec2.x;
    vec.y = this->y + vec2.y;
    vec.z = this->z + vec2.z;
    return vec;
}

Vector3 Vector3::operator-(const Vector3& vec2) const{
    Vector3 vec(0,0,0);
    vec.x = this->x - vec2.x;
    vec.y = this->y - vec2.y;
    vec.z = this->z - vec2.z;
    return vec;
}

Vector3 Vector3::operator*(float value) const{
    Vector3 vec(0,0,0);
    vec.x = this->x *value;
    vec.y = this->y *value;
    vec.z = this->z *value;
    return vec;
}

void Vector3::operator=(const Vector3& vec2){
    this->x = vec2.x;
    this->y = vec2.y;
    this->z = vec2.z;
}

bool Vector3::operator==(const Vector3& vec2) const{
    return (vec2.x==this->x)&& 
           (vec2.y == this->y) &&
           (vec2.z ==this->z);
}


 EMSCRIPTEN_BINDINGS(vector3_class){
        class_<Vector3>("Vector3")
        .constructor<>()
        .constructor<Vector3>()
        .constructor<float,float,float>()
        .property("x", &Vector3::x)
        .property("y", &Vector3::y)
        .property("z", &Vector3::z)
        .function("Magnitude", &Vector3::Magnitude)
        .function("SqrMagnitude", &Vector3::SqrMagnitude)
        .function("Normalized", &Vector3::Normalized)
        .function("Normalize", &Vector3::Normalize)
        .function("Add", &Vector3::operator+)
        .function("Subtract", &Vector3::operator-)
        .function("Scale", &Vector3::operator*)
        .function("Set", &Vector3::operator=)
        .function("IsEqual",&Vector3::operator==)
        .class_function("Dot", &Vector3::Dot)
        .class_function("Cross", &Vector3::Cross);
    }