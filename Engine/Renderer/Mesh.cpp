#include "./Mesh.hpp"
#include "iostream"


float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};  

Mesh::Mesh( std::vector<float>& pVertices){
    for(int i=0; i< pVertices.size();i+=3){
        std::cout<<pVertices.at(i) << ";" << pVertices.at(i+1) << ";" <<pVertices.at(i+2) <<std::endl;
        _verticies.push_back(Vector3(pVertices.at(i),pVertices.at(i+1),pVertices.at(i+2)));
    }
    bufferData();
    // _vertices =new float[pVertex.length];
    // vertices =new float[pVertex.length];
}

void Mesh::bufferData(){
    
    // unsigned int VBO;
    // glGenBuffers(1, &VBO);  
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glGenBuffers(1, &_vertexBuffer);  
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);    
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);




    // glGenBuffers(1, &_vertexBuffer);  
    // glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);  
    // glBufferData(GL_ARRAY_BUFFER,_verticies.size()*sizeof(Vector3),&_verticies,GL_STATIC_DRAW);
}


void Mesh::StreamToOpenGL(GLint pVerticiesAttribute){
    if(pVerticiesAttribute != -1)
    {
        glBindBuffer(GL_ARRAY_BUFFER,_vertexBuffer);
        // glEnableVertexAttribArray(pVerticiesAttribute);
        // glVertexAttribPointer(pVerticiesAttribute, 3, GL_FLOAT, GL_FALSE, 12, 0 );

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    glDrawArrays(GL_TRIANGLES,0,_verticies.size());
    glBindBuffer(GL_ARRAY_BUFFER,0);
}