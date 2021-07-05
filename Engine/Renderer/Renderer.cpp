#include "Renderer.hpp"
#include <math.h> 

Renderer::Renderer (int w, int h, std::string id) {
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

Renderer::~Renderer (void) {
    emscripten_webgl_destroy_context(context);
}

void Renderer::LoadMaterial(std::string &vertexSource, std::string &fragmentSource){
    std::cout<<"Loading a new Material \n" <<std::endl;
    // std::cout<<vertexSource <<std::endl;
    // std::cout<<fragmentSource <<std::endl;
    if(this->material != nullptr){
        std::cout<<"old material still here, deleting" <<std::endl;
        delete this->material;
    }
    this->material = new Material(vertexSource,fragmentSource);
}

void Renderer::LoadMeshData(std::string &meshData){
    this->mesh = Mesh::MeshFromObj(meshData);
}


void Renderer::Draw (float deltaTime) {
    emscripten_webgl_make_context_current(context);
    this->deltaTime = deltaTime;
    // std::cout<<deltaTime<<std::endl;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    DrawMesh(*mesh);
}

void Renderer::DrawMesh(Mesh& mesh){
    emscripten_webgl_make_context_current(context);

    timer += deltaTime;



    
    this->material->Use();

    float scale = sin(timer);
    glUniform1f(this->material->getUniformLoaction("scale"),scale);


    mesh.StreamToOpenGL(
        this->material->getAttribLocation("aPos"),
        this->material->getAttribLocation("aNormal"),
        this->material->getAttribLocation("aUV")
    );

}
