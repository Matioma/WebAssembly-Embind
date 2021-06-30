#include "./Renderer.hpp"


std::string vertex=
    "#version 300 es \n"
    "precision mediump float; \n"
    "in vec3 aPos; \n"
    "void main() \n"
    "{ \n"
    "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\n";
std::string fragment=
    "#version 300 es \n"
    "precision mediump float; \n"
    "out vec4 FragColor; \n"
    "void main() \n"
    "{ \n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n"
    "} \n";

Renderer::Renderer(){
    std::cout<<"Cool"<<std::endl;
}

void Renderer::LoadMaterial(std::string vertexSource, std::string fragmentSource){
    context->LoadMaterial(vertexSource,fragmentSource);
}

void Renderer::newContext(int width, int height, std::string id, int index){
    std::cout<<"CreateContext " << id <<std::endl;
    this->context = new Context(width, height, id);
    LoadMaterial(vertex,fragment);
}
void Renderer::run(){
    std::cout<<"Run"<<std::endl;
    this->context->run();
}

EMSCRIPTEN_BINDINGS(renderer){
    class_<Renderer>("Renderer")
    .constructor<>()
    .function("CreateContext", &Renderer::newContext)
    .function("Run",&Renderer::run)
    .function("LoadMaterial",&Renderer::LoadMaterial);
}