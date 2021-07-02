#include "./Mesh.hpp"
#include "iostream"



Mesh::Mesh( std::vector<float>& pVertices):vertices(&pVertices[0]){
    verticesCount = pVertices.size();
    bufferData();
}

void Mesh::bufferData(){
    glGenBuffers(1, &_vertexBuffer);  
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);  
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices)*verticesCount,vertices,GL_STATIC_DRAW);
}


void Mesh::StreamToOpenGL(GLint pVerticiesAttribute){
    if(pVerticiesAttribute != -1)
    {
        glBindBuffer(GL_ARRAY_BUFFER,_vertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    glDrawArrays(GL_TRIANGLES,0,verticesCount);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}