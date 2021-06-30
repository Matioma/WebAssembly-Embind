#include <string>
#include "Material.hpp"

class Context {
public:
    Context (int width, int height, std::string id);
    ~Context (void);

    void run ();
    void LoadMaterial(std::string &vertexSource, std::string &fragmentSource);

private:


    Material* material;

    int width;
    int height;

    GLuint programObject;
    GLuint vertexShader;
    GLuint fragmentShader;



    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context;
};



