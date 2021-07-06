#version 300 es
precision mediump float;
in vec3 aPos; 
in vec3 aNormal;
in vec2 aUV;

uniform mat4 modelMatrix;

out vec2 fuv;
out float intensity;
out vec3 fnormal;
void main()
{
    gl_Position =modelMatrix* vec4(aPos.x, aPos.y, aPos.z, 1.0);

    vec3 lightDirection =vec3(1.0,0.0,0.0);

    // vec4 test = modelMatrix*vec4(aNormal.xyz,1.0);

    vec4 newNormal = modelMatrix*vec4(aNormal.xyz,1.0);


    intensity =dot(newNormal.xyz,vec3(1.0,0.0,1.0));
    fnormal = aNormal;
    fuv = aUV;
}