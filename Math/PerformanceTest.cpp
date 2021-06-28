#include <../../emscripten/bind.h>
#include <stdlib.h>
#include <iostream>
#include "./Vector3.hpp"
class PerformanceTest{
    public:
    std::vector<float> vectorValues;
    PerformanceTest(std::vector<float> values){
        for(int i=0;i< values.size();i++){
            vectorValues.push_back(values[0]);
        }
    }
    
    void SumVectors(){
        for(int i=0; i< vectorValues.size()-3;i+=3){
            Vector3 vec2(vectorValues[i],vectorValues[i+1],vectorValues[i+2]);
            Vector3 vec3(vectorValues[i+3],vectorValues[i+4],vectorValues[i+5]);
            float value = (vec2-vec3).Magnitude();
        }
    }
};

EMSCRIPTEN_BINDINGS(PerformanceTest){
    class_<PerformanceTest>("PerformanceTest")
    .constructor<std::vector<float>>()
    .property("values", &PerformanceTest::vectorValues)
    .function("SumVectors",&PerformanceTest::SumVectors);
}