#include <../../emscripten/bind.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <string>
#include <iostream>

extern "C" {
    #include "html5.h"
}
#include "Context.cpp"

using namespace emscripten;


class Renderer{
    private:
        Context* context;

    public:
        Renderer();
        void CreateContext (int width, int height, std::string id, int index);
        void LoadMaterial(std::string vertexSource, std::string fragmentSource);
        void LoadMeshData(std::string meshData);
        void run();
};
