#include "./Engine.hpp"


Engine::Engine(){
    std::cout<<"Engine Created" <<std::endl;
}

void Engine::Start(){
}

void Engine::Stop(){
}


EMSCRIPTEN_BINDINGS(engine){
    class_<Engine>("Engine")
    .constructor<>()
    .function("Start", &Engine::Start)
    .function("Stop",&Engine::Stop);
}
