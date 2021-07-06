#include <string>
#include "Material.hpp"
#include "Mesh.hpp"
#include "iostream"
#include <vector>

class Renderer {
public:
    Renderer (int width, int height, std::string id);
    ~Renderer (void);

    void Draw (float deltaTime);
    void LoadMaterial(std::string &vertexSource, std::string &fragmentSource);
    void LoadMeshData(std::string &meshData);
    void DrawMesh(Mesh& mesh);

    void SetRotation(Vector3 rotation);
    void SetScale(Vector3 scale);
    void SetRotationSpeed(Vector3 rotationSpeed);
private:
    float deltaTime=0;
    float timer =0;

    float rotationX=0;
    float rotationY=0;
    float rotationZ=0;

    Vector3 _rotation;
    Vector3 _scale;
    Vector3 _rotationSpeed;


    Material* material;
    Mesh* mesh;

    int width;
    int height;

    GLuint programObject;
    GLuint vertexShader;
    GLuint fragmentShader;



    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context;
};



