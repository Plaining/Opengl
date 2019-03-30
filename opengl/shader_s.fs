
#version 330 core
out vec4 FragColor;

in vec4 Pos;
in vec2 TexCoords;

uniform sampler2D texture1;
uniform sampler3D testTexture;
uniform float     StepSize;//采样步长
uniform vec2      ScreenSize;

void main() {
    
    FragColor = texture(texture1, TexCoords);
}