#version 330 core

uniform sampler2D u_Texture;
uniform vec4 u_Color;

in vec2 textureNormal;

out vec4 FragColor;

void main() {
   // FragColor = mix(texture(texture1, textureNormal), texture(texture2, textureNormal), 0.8);
    // FragColor =  u_Color;
   FragColor = texture(u_Texture, textureNormal) * u_Color;
}
