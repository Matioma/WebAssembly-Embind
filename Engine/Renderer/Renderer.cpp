#include "./Renderer.hpp"


Renderer::Renderer(){
    std::cout<<"Cool"<<std::endl;
}

void Renderer::LoadMaterial(std::string vertexSource, std::string fragmentSource){
    context->LoadMaterial(vertexSource,fragmentSource);
}

void Renderer::CreateContext(int width, int height, std::string id, int index){
    std::cout<<"CreateContext " << id <<std::endl;
    this->context = new Context(width, height, id);
}
void Renderer::run(){
    std::cout<<"Run"<<std::endl;
    this->context->run();
}

EMSCRIPTEN_BINDINGS(renderer){
    class_<Renderer>("Renderer")
    .constructor<>()
    .function("CreateContext", &Renderer::CreateContext)
    .function("Run",&Renderer::run)
    .function("LoadMaterial",&Renderer::LoadMaterial);
}