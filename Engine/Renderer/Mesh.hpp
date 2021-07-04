
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
        std::vector<unsigned>& indicies);

    void StreamToOpenGL(GLint pVerticiesAttribute, GLint pNoramlsAttribute, GLint pUVsAttribute);

    static Mesh* MeshFromObj(std::string& meshData);


    private:
    void bufferData();

    float* vertices;
    int verticesCount;

    unsigned* indicies;
    int indiciesCount;

    float* _normals;
    int normalsCount;

    float* _uvs;
    int uvsCount;

    //BUffers
    unsigned int _vertexBufferid;
    unsigned int _normalsBufferid;
    unsigned int _uvsBufferid;
    unsigned int _indexBufferid;

    class FaceIndexTriplet {
        public:
            unsigned v; //vertex
            unsigned uv;//uv
            unsigned n; //normal
            FaceIndexTriplet( unsigned pV, unsigned pUV, unsigned pN )
            :	v(pV),uv(pUV),n(pN) {
            }
            //needed for use as key in map
            bool operator<(const FaceIndexTriplet other) const{
                return memcmp((void*)this, (void*)&other, sizeof(FaceIndexTriplet))>0;
            }
    };
};