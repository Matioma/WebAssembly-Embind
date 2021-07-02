#include "./Renderer.hpp"


Renderer::Renderer(){
    std::cout<<"Renderer Created"<<std::endl;
}

void Renderer::LoadMaterial(std::string vertexSource, std::string fragmentSource){
    context->LoadMaterial(vertexSource,fragmentSource);
}

void Renderer::LoadMeshData(std::string meshData){
    this->context->LoadMeshData(meshData);
}

void Renderer::CreateContext(int width, int height, std::string id, int index){
    this->context = new Context(width, height, id);
}

void Renderer::run(){
    this->context->run();
}

EMSCRIPTEN_BINDINGS(renderer){
    class_<Renderer>("Renderer")
    .constructor<>()
    .function("CreateContext", &Renderer::CreateContext)
    .function("Run",&Renderer::run)
    .function("LoadMaterial",&Renderer::LoadMaterial)
    .function("LoadMeshData", &Renderer::LoadMeshData);
}