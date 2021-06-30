#include "Context.h"

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};  


Context::Context (int w, int h, std::string id) {
    width = w;
    height = h;

    // Context configurations
    EmscriptenWebGLContextAttributes attrs;
    attrs.explicitSwapControl = 0;
    attrs.depth = 1;
    attrs.stencil = 1;
    attrs.antialias = 1;
    attrs.majorVersion = 2;
    attrs.minorVersion = 0;

    std::string id_str = id;
    std::string sharp_id_str = "#" + id_str;

    context = emscripten_webgl_create_context(sharp_id_str.c_str(), &attrs);
    emscripten_webgl_make_context_current(context);
}

Context::~Context (void) {
    emscripten_webgl_destroy_context(context);
}

void Context::LoadMaterial(std::string &vertexSource, std::string &fragmentSource){
    this->material = new Material(vertexSource,fragmentSource);
}


void Context::run () {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // // Make the context current and use the program
    emscripten_webgl_make_context_current(context);

    unsigned int VBO;
    glGenBuffers(1, &VBO);  
    glBindBuffer(GL_ARRAY_BUFFER, VBO);  
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  
    // glUseProgram(programObject);
    this->material->Use();

    glDrawArrays(GL_TRIANGLES,0,sizeof(vertices));
}
