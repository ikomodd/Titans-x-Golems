#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D uTexture;
uniform vec4 uBackgroundColor = vec4(0, 0, 0, 0);

void main() {

    FragColor = texture(uTexture, TexCoord);

    if (FragColor.a == 0)
        FragColor = uBackgroundColor;
}