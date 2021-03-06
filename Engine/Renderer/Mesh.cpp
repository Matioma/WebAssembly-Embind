#include "./Mesh.hpp"
#include "iostream"
#include <stdio.h>
#include <sstream> 

Mesh::Mesh( 
    std::vector<float>& pVertices,
    std::vector<float>& pNormals,
    std::vector<float>& pUvs,
    std::vector<unsigned>& pIndicies 
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
    std::vector<unsigned> meshIndiciesData;

    std::map <FaceIndexTriplet, unsigned int> mappedTriplets;

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

            int vertexIndex[3];
            int normalIndex[3];
            int uvIndex[3];

            int count = sscanf(line.c_str(), "%10s %d/%d/%d %d/%d/%d %d/%d/%d",
                cmd, 
                &vertexIndex[0], &uvIndex[0],&normalIndex[0],
                &vertexIndex[1], &uvIndex[1],&normalIndex[1],
                &vertexIndex[2], &uvIndex[2],&normalIndex[2]);

            if(count ==10){
                for(int i=0;i<3;i++){
                    FaceIndexTriplet triplet(vertexIndex[i], uvIndex[i], normalIndex[i]);
                    std::map<FaceIndexTriplet, unsigned int>::iterator found =mappedTriplets.find(triplet);

                    if (found == mappedTriplets.end()){
                        unsigned int index =mappedTriplets.size();
                        mappedTriplets[triplet] = index;

                        meshIndiciesData.push_back(index);

                        meshVertexData.push_back(pVertices[3*(vertexIndex[i]-1)]);
                        meshVertexData.push_back(pVertices[3*(vertexIndex[i]-1)+1]);
                        meshVertexData.push_back(pVertices[3*(vertexIndex[i]-1)+2]);
                        
                        meshNormalData.push_back(pNormals[3*(normalIndex[i]-1)]);
                        meshNormalData.push_back(pNormals[3*(normalIndex[i]-1)+1]);
                        meshNormalData.push_back(pNormals[3*(normalIndex[i]-1)+2]);

                        meshUvCoordsData.push_back(pUvCoords[2*(uvIndex[i]-1)]);
                        meshUvCoordsData.push_back(pUvCoords[2*(uvIndex[i]-1)+1]);

                    }else{
                        unsigned int index = found->second;
                        meshIndiciesData.push_back(index);
                    }
                }
                counter++;

            }else{
                std::cout<<"Fragment data is not entirely correct"<< std::endl;
                return NULL;
            }
        }
    }
    std::cout << "Mesh loaded and buffered:" << (meshIndiciesData.size()/3.0f) << " triangles." << std::endl;
    return new Mesh(meshVertexData,meshNormalData,meshUvCoordsData,meshIndiciesData);
}

void Mesh::bufferData(){
    glGenBuffers(1, &_indexBufferid);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_indexBufferid);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indicies)*indiciesCount,&indicies[0],GL_STATIC_DRAW);

    glGenBuffers(1, &_vertexBufferid);  
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferid);  
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices)*verticesCount,&vertices[0],GL_STATIC_DRAW);

    glGenBuffers(1,&_normalsBufferid);
    glBindBuffer(GL_ARRAY_BUFFER, _normalsBufferid);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*normalsCount,&_normals[0],GL_STATIC_DRAW);

    glGenBuffers(1,&_uvsBufferid);
    glBindBuffer(GL_ARRAY_BUFFER, _uvsBufferid);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*uvsCount,&_uvs[0],GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER,0);
}


void Mesh::StreamToOpenGL(GLint pVerticiesAttribute, GLint pNoramlsAttribute, GLint pUVsAttribute){
    if(pVerticiesAttribute != -1)
    {
        glBindBuffer(GL_ARRAY_BUFFER,_vertexBufferid);
        glEnableVertexAttribArray(pVerticiesAttribute);
        glVertexAttribPointer(pVerticiesAttribute, 3, GL_FLOAT, GL_TRUE, 0, (void*)0);
    }

    if(pNoramlsAttribute != -1){
        glBindBuffer(GL_ARRAY_BUFFER,_normalsBufferid);
        glEnableVertexAttribArray(pNoramlsAttribute);
        glVertexAttribPointer(pNoramlsAttribute,3,GL_FLOAT,GL_FALSE,0,(void*)0);
    }
    if(pUVsAttribute != -1){
        glBindBuffer(GL_ARRAY_BUFFER,_uvsBufferid);
        glEnableVertexAttribArray(pUVsAttribute);
        glVertexAttribPointer(pUVsAttribute,2, GL_FLOAT,GL_FALSE, 0,(void*)0);
    }

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _indexBufferid );
    glDrawElements(GL_TRIANGLES,indiciesCount, GL_UNSIGNED_INT, 0);
}