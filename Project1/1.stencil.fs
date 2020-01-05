#version 330 core

out vec4 FragColor;

uniform sampler2D texture1;

in vec2 TexCoords;
in vec3 FragPos;

void main(){
    vec4 texColor = texture(texture1, TexCoords);
    if(texColor.a < 0.1)
        discard;
    FragColor = texColor;
}