#include "./RendererAPI.hpp"


RenderAPI::RenderAPI(){
    std::cout<<"Renderer Created"<<std::endl;
}

void RenderAPI::LoadMaterial(std::string vertexSource, std::string fragmentSource){
    context->LoadMaterial(vertexSource,fragmentSource);
}

void RenderAPI::LoadMeshData(std::string meshData){
    this->context->LoadMeshData(meshData);
}

void RenderAPI::CreateContext(int width, int height, std::string id, int index){
    this->context = new Renderer(width, height, id);
}

void RenderAPI::Update(float deltaTime){
    this->context->Draw(deltaTime);
}

void RenderAPI::SetRotationSpeed(float x, float y, float z){
    this->context->SetRotationSpeed(Vector3(x,y,z));
}
void RenderAPI::SetScale(float x, float y, float z){
    this->context->SetScale(Vector3(x,y,z));
    std::cout<<x<< ": "<<y<< ":"<<z <<std::endl;
}

EMSCRIPTEN_BINDINGS(renderer){
    class_<RenderAPI>("RendererAPI")
    .constructor<>()
    .function("CreateContext", &RenderAPI::CreateContext)
    .function("Update",&RenderAPI::Update)
    .function("LoadMaterial",&RenderAPI::LoadMaterial)
    .function("LoadMeshData", &RenderAPI::LoadMeshData)
    .function("SetRotationSpeed",&RenderAPI::SetRotationSpeed)
    .function("SetScale",&RenderAPI::SetScale);
}