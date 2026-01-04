#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextureNormal; 

uniform mat4 u_ViewProjection;
uniform mat4 u_ModelMatrix;
out vec2 textureNormal;

void main() {
    gl_Position = u_ViewProjection * u_ModelMatrix * vec4(aPos, 1.0f);
    textureNormal = aTextureNormal;
}