#include "./Mesh.hpp"
#include "iostream"
#include <stdio.h>
#include <sstream> 

std::vector<float > verticesList={
    0.0f, -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, -1.0f, -1.0f,
    0.0f, 1.0f, -1.0f,
    0.195090f, -1.0f, -0.980785f,
    0.195090f, 1.0f, -0.980785f

    // 0.5f,  0.5f, 0.0f,  // top right
    // 0.5f, -0.5f, 0.0f,  // bottom right
    // -0.5f, -0.5f, 0.0f,  // bottom left
    // -0.5f,  0.5f, 0.0f   // top left 
}; 
// float verticesList[] = {
//      0.5f,  0.5f, 0.0f,  // top right
//      0.5f, -0.5f, 0.0f,  // bottom right
//     -0.5f, -0.5f, 0.0f,  // bottom left
//     -0.5f,  0.5f, 0.0f   // top left 
// };

std::vector<unsigned int > testindices = {  // note that we start from 0!
    // 0, 1, 3,   // first triangle
    // 1, 2, 3    // second triangle


    // 0, 2, 4,   // first triangle
    1, 5, 3    // second triangle
}; 

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
            // std::cout<<line <<std::endl;
            sscanf(line.c_str(), "%10s %f %f %f ", cmd, &x, &y, &z);
            pVertices.push_back(x);
            pVertices.push_back(y);
            pVertices.push_back(z);

            // meshVertexData.push_back(x);
            // meshVertexData.push_back(y);
            // meshVertexData.push_back(z);
        }
        //Read all vertex normals
        else if(strcmp(cmd,"vn")==0){
            float x,y,z;

            // std::cout<<line<<std::endl;
            sscanf(line.c_str(), "%10s %f %f %f ", cmd, &x, &y, &z);
            pNormals.push_back(x);
            pNormals.push_back(y);
            pNormals.push_back(z);


            // std::cout << x << ":" << y << ": " << z <<std::endl;
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
            // std::cout <<line <<std::endl;

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

                    // std::cout<<vertexIndex[i]-1 <<std::endl;
                    if (found == mappedTriplets.end()){
                        unsigned int index =mappedTriplets.size();
                        mappedTriplets[triplet] = index;

                        meshIndiciesData.push_back(index);
                        // std::cout<< index<<std::endl;

                        meshVertexData.push_back(pVertices[3*(vertexIndex[i]-1)]);
                        meshVertexData.push_back(pVertices[3*(vertexIndex[i]-1)+1]);
                        meshVertexData.push_back(pVertices[3*(vertexIndex[i]-1)+2]);

                        // std::cout<<"vertex Data" <<std::endl;
                        // std::cout << ":" << pVertices[3*(vertexIndex[i]-1)] <<":" <<pVertices[3*(vertexIndex[i]-1)+1] << ":"<< pVertices[3*(vertexIndex[i]-1)+2]<<std::endl;
                        meshNormalData.push_back(pNormals[3*(normalIndex[i]-1)]);
                        meshNormalData.push_back(pNormals[3*(normalIndex[i]-1)+1]);
                        meshNormalData.push_back(pNormals[3*(normalIndex[i]-1)+2]);

                        //std::cout << ":" << pNormals[3*(normalIndex[i]-1)] <<":" <<pNormals[3*(normalIndex[i]-1)+1] << ":"<< pNormals[3*(normalIndex[i]-1)+2]<<std::endl;

                        meshUvCoordsData.push_back(pUvCoords[2*(uvIndex[i]-1)]);
                        meshUvCoordsData.push_back(pUvCoords[2*(uvIndex[i]-1)+1]);

                        // std::cout << ":" << pNormals[3*(normalIndex[i]-1)] <<":" <<pNormals[3*(normalIndex[i]-1)+1] << ":"<< pNormals[3*(normalIndex[i]-1)+2]<<std::endl;
                    }else{
                        unsigned int index = found->second;
                        meshIndiciesData.push_back(index);
                        // std::cout<< index<<std::endl;
                    }
                        // unsigned int index =mappedTriplets.size();
                        // mappedTriplets[triplet] = index;

                        // meshIndiciesData.push_back(index);
                        // std::cout<< index<<std::endl;

                        // meshVertexData.push_back(pVertices[3*(vertexIndex[i]-1)]);
                        // meshVertexData.push_back(pVertices[3*(vertexIndex[i]-1)+1]);
                        // meshVertexData.push_back(pVertices[3*(vertexIndex[i]-1)+2]);

                        // meshNormalData.push_back(pNormals[3*(vertexIndex[i]-1)]);
                        // meshNormalData.push_back(pNormals[3*(vertexIndex[i]-1)+1]);
                        // meshNormalData.push_back(pNormals[3*(vertexIndex[i]-1)+2]);

                        // meshUvCoordsData.push_back(pUvCoords[3*(vertexIndex[i]-1)]);
                        // meshUvCoordsData.push_back(pUvCoords[2*(vertexIndex[i]-1)+1]);

                }
                // std::cout<<":" <<std::endl;
                counter++;

            }else{
                std::cout<<"Fragment data is not entirely correct"<< std::endl;
                return NULL;
            }


            //     unsigned int index;
            //     //First triplet 
            //     index =counter;
            //     counter++;
            //     meshIndiciesData.push_back(index);
            //     meshVertexData.push_back(pVertices[vertex0 -1]);
            //     meshNormalData.push_back(pNormals[normal0-1]);
            //     meshUvCoordsData.push_back(pUvCoords[uv0-1]);

            //     //First triplet 
            //     index =counter;
            //     counter++;
            //     meshIndiciesData.push_back(index);
            //     meshVertexData.push_back(pVertices[vertex1 -1]);
            //     meshNormalData.push_back(pNormals[normal1-1]);
            //     meshUvCoordsData.push_back(pUvCoords[uv1-1]);

            //     //First triplet 
            //     index =counter;
            //     counter++;
            //     meshIndiciesData.push_back(index);
            //     meshVertexData.push_back(pVertices[vertex2 -1]);
            //     meshNormalData.push_back(pNormals[normal2-1]);
            //     meshUvCoordsData.push_back(pUvCoords[uv2-1]);
            // }else{
            //     std::cout<<"Fragment data is not entirely correct"<< std::endl;
            //     return NULL;
            // }
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
    // unsigned int VAO;
    // glGenBuffers(1,&VAO);

    // glBindBuffer(GL_ARRAY_BUFFER, VAO);
    // glBufferData(GL_ARRAY_BUFFER,sizeof(verticesList)*18,&verticesList[0],GL_STATIC_DRAW);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);  

    // unsigned int EBO;
    // glGenBuffers(1, &EBO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*3, &testindices[0], GL_STATIC_DRAW);
    // glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

    
    
    
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

   



    // // std::cout<<verticesCount<<std::endl;
    // // glDrawArrays(GL_TRIANGLES,0,verticesCount);
    // glBindBuffer(GL_ARRAY_BUFFER,0);
}