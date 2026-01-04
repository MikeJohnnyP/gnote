#version 330 core

uniform sampler2D texture1;
uniform sampler2D texture2;

in vec2 textureNormal;

out vec4 FragColor;

void main() {
//    FragColor = mix(texture(texture1, textureNormal), texture(texture2, textureNormal), 0.8);
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
