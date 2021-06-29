#include <string>

class Context {
public:
    Context (int width, int height, std::string id);
    ~Context (void);

    void run ();

private:
    int width;
    int height;

    GLuint programObject;
    GLuint vertexShader;
    GLuint fragmentShader;

    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context;
};



