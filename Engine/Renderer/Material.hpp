#include <string>
#include <GLES2/gl2.h>
#include <EGL/egl.h>

class Material {
    public:
        Material(std::string &vertexSource, std::string &fragmentSource);
        void Use();

        GLuint getAttribLocation (const std::string& name);
        GLuint getUniformLoaction(const std::string& name);
    private:
        GLuint compileShader(GLenum type, std::string &source);
        void createProgram(std::string &vertexSource, std::string &fragmentSource);


        GLuint _programObject;
        GLuint _vertexShader;
        GLuint _fragmentShader;
};