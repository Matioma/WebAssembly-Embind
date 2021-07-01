#include <string>
#include "Material.hpp"
#include "Mesh.hpp"
#include "iostream"
#include <vector>

class Context {
public:
    Context (int width, int height, std::string id);
    ~Context (void);

    void run ();
    void LoadMaterial(std::string &vertexSource, std::string &fragmentSource);
    void DrawMesh(Mesh& mesh);
private:


    Material* material;
    Mesh* mesh;

    int width;
    int height;

    GLuint programObject;
    GLuint vertexShader;
    GLuint fragmentShader;



    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context;
};



