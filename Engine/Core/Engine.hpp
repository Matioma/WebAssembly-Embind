#include <../../emscripten/bind.h>

// #include "../Renderer/Renderer.hpp"
#include <iostream>
using namespace emscripten;

class Engine{
    public:
        Engine();
        void Start();
        void Stop();
};