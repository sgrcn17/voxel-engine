#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texturemap;
  
void main()
{
    FragColor = texture(texturemap, TexCoord);
}