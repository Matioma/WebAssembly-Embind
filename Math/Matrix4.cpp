#include "./Matrix4.hpp"

Matrix4::Matrix4(const Vector3& v1,const Vector3& v2, const Vector3& v3, const Vector3& v4){
    this->vectorValues.push_back(v1.x);
    this->vectorValues.push_back(v2.x);
    this->vectorValues.push_back(v3.x);
    this->vectorValues.push_back(v4.x);
    this->vectorValues.push_back(v1.y);
    this->vectorValues.push_back(v2.y);
    this->vectorValues.push_back(v3.y);
    this->vectorValues.push_back(v4.y);
    this->vectorValues.push_back(v1.z);
    this->vectorValues.push_back(v2.z);
    this->vectorValues.push_back(v3.z);
    this->vectorValues.push_back(v4.z);
    this->vectorValues.push_back(0);
    this->vectorValues.push_back(0);
    this->vectorValues.push_back(0);
    this->vectorValues.push_back(0);
}

Matrix4::Matrix4(const Matrix4& mat){
    for(int i=0; i<16;i++){
        this->vectorValues.push_back(mat.vectorValues[i]);
    }
}


Matrix4::Matrix4(std::vector<float> values){
    int counter;
    for(counter =0;counter<values.size();counter++){
        this->vectorValues.push_back(values[counter]);
        if(counter>=15) return;
    }
    while(counter<16){
        this->vectorValues.push_back(0);
        counter++;
    }
}



Matrix4::Matrix4(){
    this->vectorValues.push_back(0);
    this->vectorValues.push_back(0);
    this->vectorValues.push_back(0);
    this->vectorValues.push_back(0);
    this->vectorValues.push_back(0);
    this->vectorValues.push_back(0);
    this->vectorValues.push_back(0);
    this->vectorValues.push_back(0);
    this->vectorValues.push_back(0);
    this->vectorValues.push_back(0);
    this->vectorValues.push_back(0);
    this->vectorValues.push_back(0);
    this->vectorValues.push_back(0);
    this->vectorValues.push_back(0);
    this->vectorValues.push_back(0);
    this->vectorValues.push_back(0);
}

Matrix4 Matrix4::Identity(){
    Matrix4 matrix;
    matrix.vectorValues[0] = 1;
    matrix.vectorValues[5] = 1;
    matrix.vectorValues[10] = 1;
    matrix.vectorValues[15] =1;
    return matrix;
}

Matrix4 Matrix4::operator+(const Matrix4& matrix2) const{
    Matrix4 mat;

    for(int i=0; i< mat.vectorValues.size();i++){
        mat.vectorValues[i] = this->vectorValues[i]+ matrix2.vectorValues[i];
    }
    return mat;
}

Matrix4 Matrix4::operator*(const Matrix4& mat2) const{
    Matrix4 mat;
    mat.vectorValues[0] = (this->vectorValues[0]*mat2.vectorValues[0]) + (this->vectorValues[1]*mat2.vectorValues[4]) +(this->vectorValues[2]*mat2.vectorValues[8])+(this->vectorValues[3]*mat2.vectorValues[12]);
    mat.vectorValues[1] = this->vectorValues[0]*mat2.vectorValues[1] + this->vectorValues[1]*mat2.vectorValues[5] +this->vectorValues[2]*mat2.vectorValues[9]+this->vectorValues[3]*mat2.vectorValues[13];
    mat.vectorValues[2] = this->vectorValues[0]*mat2.vectorValues[2] + this->vectorValues[1]*mat2.vectorValues[6] +this->vectorValues[2]*mat2.vectorValues[10]+this->vectorValues[3]*mat2.vectorValues[14];
    mat.vectorValues[3] = this->vectorValues[0]*mat2.vectorValues[3] + this->vectorValues[1]*mat2.vectorValues[7] +this->vectorValues[2]*mat2.vectorValues[11]+this->vectorValues[3]*mat2.vectorValues[15];

    mat.vectorValues[4] = this->vectorValues[4]*mat2.vectorValues[0] + this->vectorValues[5]*mat2.vectorValues[4] +this->vectorValues[6]*mat2.vectorValues[8]+this->vectorValues[7]*mat2.vectorValues[12];
    mat.vectorValues[5] = this->vectorValues[4]*mat2.vectorValues[1] + this->vectorValues[5]*mat2.vectorValues[5] +this->vectorValues[6]*mat2.vectorValues[9]+this->vectorValues[7]*mat2.vectorValues[13];
    mat.vectorValues[6] = this->vectorValues[4]*mat2.vectorValues[2] + this->vectorValues[5]*mat2.vectorValues[6] +this->vectorValues[6]*mat2.vectorValues[10]+this->vectorValues[7]*mat2.vectorValues[14];
    mat.vectorValues[7] = this->vectorValues[4]*mat2.vectorValues[3] + this->vectorValues[5]*mat2.vectorValues[7] +this->vectorValues[6]*mat2.vectorValues[11]+this->vectorValues[7]*mat2.vectorValues[15];

    mat.vectorValues[8] = this->vectorValues[8]*mat2.vectorValues[0] + this->vectorValues[9]*mat2.vectorValues[4] +this->vectorValues[10]*mat2.vectorValues[8]+this->vectorValues[11]*mat2.vectorValues[12];
    mat.vectorValues[9] = this->vectorValues[8]*mat2.vectorValues[1] + this->vectorValues[9]*mat2.vectorValues[5] +this->vectorValues[10]*mat2.vectorValues[9]+this->vectorValues[11]*mat2.vectorValues[13];
    mat.vectorValues[10] = this->vectorValues[8]*mat2.vectorValues[2] + this->vectorValues[9]*mat2.vectorValues[6] +this->vectorValues[10]*mat2.vectorValues[10]+this->vectorValues[11]*mat2.vectorValues[14];
    mat.vectorValues[11] = this->vectorValues[8]*mat2.vectorValues[3] + this->vectorValues[9]*mat2.vectorValues[7] +this->vectorValues[10]*mat2.vectorValues[11]+this->vectorValues[11]*mat2.vectorValues[15];

    mat.vectorValues[12] = this->vectorValues[12]*mat2.vectorValues[0] + this->vectorValues[13]*mat2.vectorValues[4] +this->vectorValues[14]*mat2.vectorValues[8]+this->vectorValues[15]*mat2.vectorValues[12];
    mat.vectorValues[13] = this->vectorValues[12]*mat2.vectorValues[1] + this->vectorValues[13]*mat2.vectorValues[5] +this->vectorValues[14]*mat2.vectorValues[9]+this->vectorValues[15]*mat2.vectorValues[13];
    mat.vectorValues[14] = this->vectorValues[12]*mat2.vectorValues[2] + this->vectorValues[13]*mat2.vectorValues[6] +this->vectorValues[14]*mat2.vectorValues[10]+this->vectorValues[15]*mat2.vectorValues[14];
    mat.vectorValues[15] = this->vectorValues[12]*mat2.vectorValues[3] + this->vectorValues[13]*mat2.vectorValues[7] +this->vectorValues[14]*mat2.vectorValues[11]+this->vectorValues[15]*mat2.vectorValues[15];
    return mat;
}

Matrix4 Matrix4::operator*(float scale) const{
    Matrix4 mat;
    
    for(int i =0; i< this->vectorValues.size();i++){
        mat.vectorValues[i] = this->vectorValues[i]*scale;
    }
    return mat;
}



EMSCRIPTEN_BINDINGS(wrappers){
    register_vector<float>("VectorFloat");
}

EMSCRIPTEN_BINDINGS(matrix){
    class_<Matrix4>("Matrix4")
    .constructor<>()
    .constructor<std::vector<float>>()
    .constructor<Vector3,Vector3,Vector3,Vector3>()
    .property("values", &Matrix4::vectorValues)
    .function("Add",&Matrix4::operator+)
    .function("MultiplyMatrix",select_overload<Matrix4(const Matrix4&) const>(&Matrix4::operator*))
    .function("MultiplyValue", select_overload<Matrix4(float) const>(&Matrix4::operator*))
    .class_function("Identity", &Matrix4::Identity);
}