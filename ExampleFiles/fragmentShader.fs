#version 300 es
precision mediump float;
out vec4 FragColor;

in vec2 fuv;
in float intensity;
in vec3 fnormal;
void main()
{ 
    FragColor = vec4(1.0,0.0,0.0, 1.0f)*intensity;
}