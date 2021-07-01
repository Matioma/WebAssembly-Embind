
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
    // std::vector<float>& vertices;
    float* vertices;

    unsigned int _vertexBuffer;
};