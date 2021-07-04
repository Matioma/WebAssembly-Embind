#include "./Mesh.hpp"
#include "iostream"
#include <stdio.h>
#include <sstream> 

std::vector<float > verticesList={
   -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,

    0.5f, 0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
}; 

Mesh::Mesh( 
    std::vector<float>& pVertices,
    std::vector<float>& pNormals,
    std::vector<float>& pUvs,
    std::vector<float>& pIndicies 
    ):vertices(&pVertices[0]),_normals(&pNormals[0]),_uvs(&pUvs[0]) ,indicies(&pIndicies[0]){
        verticesCount = pVertices.size();
        normalsCount = pNormals.size();
        uvsCount = pUvs.size();
        indiciesCount = pIndicies.size();
            bufferData();
}

Mesh* Mesh::MeshFromObj(std::string& meshData){
    std::vector<float> meshVertexData;
    std::vector<float> meshNormalData;
    std::vector<float> meshUvCoordsData;
    std::vector<float> meshIndiciesData;


    std::vector<float> pVertices;
    std::vector<float> pNormals;
    std::vector<float> pUvCoords;

    std::stringstream ss;
    ss<<meshData;
    std::string line;

    while(std::getline(ss,line,'\n')){
        char cmd[10];
        cmd[0] = 0;
        sscanf (line.c_str(), "%10s", cmd);

        int counter =0;

        //Read all vertex positions
        if(strcmp(cmd,"v")==0){
            float x,y,z;
            sscanf(line.c_str(), "%10s %f %f %f ", cmd, &x, &y, &z);
            pVertices.push_back(x);
            pVertices.push_back(y);
            pVertices.push_back(z);
        }
        //Read all vertex normals
        else if(strcmp(cmd,"vn")==0){
            float x,y,z;
            sscanf(line.c_str(), "%10s %f %f %f ", cmd, &x, &y, &z);
            pNormals.push_back(x);
            pNormals.push_back(y);
            pNormals.push_back(z);
        }
        //Read all vertex uvs
        else if(strcmp(cmd,"vt")==0){
            float x,y;
            sscanf(line.c_str(), "%10s %f %f ", cmd, &x, &y);
            pUvCoords.push_back(x);
            pUvCoords.push_back(y);
        }
        //Assemble fragments
        else if(strcmp(cmd,"f")==0){
            std::cout <<line <<std::endl;

            int vertex0;
            int vertex1;
            int vertex2;

            int normal0;
            int normal1;
            int normal2;

            int uv0;
            int uv1;
            int uv2;

            int count = sscanf(line.c_str(), "%10s %d/%d/%d %d/%d/%d %d/%d/%d",
                cmd, 
                &vertex0, &normal0, &uv0,
                &vertex1, &normal1, &uv1,
                &vertex2, &normal2, &uv2);

            if(count ==10){
                unsigned int index;
                //First triplet 
                index =counter;
                counter++;
                meshIndiciesData.push_back(index);
                meshVertexData.push_back(pVertices[vertex0 -1]);
                meshNormalData.push_back(pNormals[normal0-1]);
                meshUvCoordsData.push_back(pUvCoords[uv0-1]);

                //First triplet 
                index =counter;
                counter++;
                meshIndiciesData.push_back(index);
                meshVertexData.push_back(pVertices[vertex1 -1]);
                meshNormalData.push_back(pNormals[normal1-1]);
                meshUvCoordsData.push_back(pUvCoords[uv1-1]);

                //First triplet 
                index =counter;
                counter++;
                meshIndiciesData.push_back(index);
                meshVertexData.push_back(pVertices[vertex2 -1]);
                meshNormalData.push_back(pNormals[normal2-1]);
                meshUvCoordsData.push_back(pUvCoords[uv2-1]);
            }else{
                std::cout<<"Fragment data is not entirely correct"<< std::endl;
                return NULL;
            }
            
        }
    }
    return new Mesh(meshVertexData,meshNormalData,meshUvCoordsData,meshIndiciesData);
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