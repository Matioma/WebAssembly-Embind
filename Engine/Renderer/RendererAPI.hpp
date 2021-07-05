#include <../../emscripten/bind.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <string>
#include <iostream>

extern "C" {
    #include "html5.h"
}
#include "Renderer.cpp"

using namespace emscripten;
class RenderAPI{
    private:
        Renderer* context;

    public:
        RenderAPI();
        void CreateContext (int width, int height, std::string id, int index);
        void LoadMaterial(std::string vertexSource, std::string fragmentSource);
        void LoadMeshData(std::string meshData);
        void Update(float deltaTime);
};
