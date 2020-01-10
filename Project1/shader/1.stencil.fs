#version 330 core

out vec4 FragColor;

uniform sampler2D texture1;

in vec2 TexCoords;
in vec3 FragPos;

void main()
{             
    FragColor = texture(texture1, TexCoords);
}