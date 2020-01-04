#version 330 core

out vec4 FragColor;

uniform sampler2D texture1;

in vec2 TexCoords;
in vec3 FragPos;

void main(){
    vec3 result = vec3( texture(texture1, TexCoords));
    FragColor = vec4(result, 1.0f);
}