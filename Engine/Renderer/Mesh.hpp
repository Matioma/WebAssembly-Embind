
#include "../Math/Vector3.hpp"
#include <list>
#include <vector>
#include <GLES2/gl2.h>
#include <EGL/egl.h>

class Mesh{
    public:
    Mesh( 
        std::vector<float>& vertices,
        std::vector<float>& pNormals,
        std::vector<float>& pUvs,
        std::vector<float>& indicies);

    void StreamToOpenGL(GLint pVerticiesAttribute);

    static Mesh* MeshFromObj(std::string& meshData);


    private:
    void bufferData();

    float* vertices;
    int verticesCount;

    float* indicies;
    int indiciesCount;

    float* _normals;
    int normalsCount;

    float* _uvs;
    int uvsCount;

    unsigned int _vertexBuffer;
};