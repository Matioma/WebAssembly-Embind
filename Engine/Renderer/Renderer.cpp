#include "Renderer.hpp"
#include <math.h> 
#include "../Math/Matrix4.hpp"

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


    _scale = Vector3(1,1,1);
}

Renderer::~Renderer (void) {
    emscripten_webgl_destroy_context(context);
}

void Renderer::LoadMaterial(std::string &vertexSource, std::string &fragmentSource){
    std::cout<<"Loading a new Material \n" <<std::endl;
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

    glEnable(GL_DEPTH_TEST);

	glFrontFace(GL_CCW);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);



    DrawMesh(*mesh);
}

void Renderer::DrawMesh(Mesh& mesh){
    emscripten_webgl_make_context_current(context);

    this->_rotation =this->_rotation+(_rotationSpeed* deltaTime);


    this->material->Use();

    Matrix4 translation(Vector3(1,0,0),Vector3(0,1,0), Vector3(0,0,1), Vector3(0,0,0));
    Matrix4 scale = Matrix4::ScaleMatrix(_scale.x,_scale.y,_scale.z);

    Matrix4 RotateX = Matrix4::RotationX(_rotation.x);
    Matrix4 RotateY = Matrix4::RotationY(_rotation.y);
    Matrix4 RotateZ = Matrix4::RotationZ(_rotation.z);

    Matrix4 Model = translation*RotateY*RotateX*RotateZ*scale;

    glUniformMatrix4fv(this->material->getUniformLoaction("modelMatrix"),1,false, &Model.getValues()[0]);


    mesh.StreamToOpenGL(
        this->material->getAttribLocation("aPos"),
        this->material->getAttribLocation("aNormal"),
        this->material->getAttribLocation("aUV")
    );

}

void Renderer::SetRotation(Vector3 pRotation){
    this->_rotation = pRotation;
}

void Renderer::SetScale(Vector3 pScale){
    this->_scale = pScale;
}

void Renderer::SetRotationSpeed(Vector3 pRotationSpeed){
    this->_rotationSpeed = pRotationSpeed;
    std::cout<< pRotationSpeed.x << pRotationSpeed.y << pRotationSpeed.z <<std::endl;
}