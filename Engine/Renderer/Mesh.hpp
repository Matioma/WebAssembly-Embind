
#include "../Math/Vector3.hpp"
#include <list>
#include <vector>
#include <GLES2/gl2.h>
#include <EGL/egl.h>

class Mesh{
    public:
    Mesh( std::vector<float>& vertices);
    void StreamToOpenGL(GLint pVerticiesAttribute);

    private:
    void bufferData();

    std::list<Vector3> _verticies;
    float* vertices;
    int verticesCount;

    unsigned int _vertexBuffer;
};