#include "./Renderer.hpp"

Renderer::Renderer(){
    std::cout<<"Cool"<<std::endl;
}

void Renderer::newContext(int width, int height, std::string id, int index){
    std::cout<<"CreateContext " << id <<std::endl;
    this->context = new Context(width, height, id);
    // free(id);
}
void Renderer::run(){
    std::cout<<"Run"<<std::endl;
    this->context->run();
}

EMSCRIPTEN_BINDINGS(renderer){
    class_<Renderer>("Renderer")
    .constructor<>()
    .function("CreateContext", &Renderer::newContext,allow_raw_pointers())
    .function("Run",&Renderer::run);
}