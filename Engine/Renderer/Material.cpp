#include "Material.hpp"
#include <iostream>

Material::Material(std::string &vertexSource, std::string &fragmentSource){
    this->createProgram(vertexSource, fragmentSource);
}

void Material::Use(){
    if(_programObject != -1){
        glUseProgram(_programObject);
    }
}

GLuint Material::compileShader (GLenum type, std::string &source) {
    // Create shader object
    const GLchar* sourceString[1];
    GLint sourceStringLengths[1];

    sourceString[0] = source.c_str();
    sourceStringLengths[0] = source.length();
    GLuint shader = glCreateShader(type);

    if (shader == 0) {
        return 0;
    }

    // Assign and compile the source to the shader object
    glShaderSource(shader, 1, sourceString, sourceStringLengths);
    glCompileShader(shader);

    // Check if there were errors
    int infoLen = 0;
    glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &infoLen );

    if (infoLen > 1) {

        char infoLog[infoLen];

        // And print them out
        glGetShaderInfoLog( shader, infoLen, NULL, infoLog );
        printf("%s\n", infoLog);

        free ( infoLog );
    }
    return shader;
}


void Material::createProgram(std::string &vertexSource, std::string &fragmentSource){
    _vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
    _fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

     // Build program
    _programObject = glCreateProgram();

    glAttachShader(_programObject, _vertexShader);
    glAttachShader(_programObject, _fragmentShader);

    // glBindAttribLocation(programObject, 0, "position");
    glLinkProgram(_programObject);
    glValidateProgram(_programObject);
    glDeleteShader(_vertexShader);
    glDeleteShader(_fragmentShader);  
}