#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform bool uIsMotionTile;
uniform bool uIsAttackTile;

uniform sampler2D uTexture;

void main() {

    vec4 TexColor = texture(uTexture, TexCoord);

    vec4 Highlight = vec4(0.0f, 0.0f, 0.0f, 0.0f);

    if (uIsAttackTile) Highlight = vec4(0.3f, 0.0f, 0.0f, 0.0f);
    else if (uIsMotionTile) Highlight = vec4(0.0f, 0.0f, 0.3f, 0.0f);

    FragColor = TexColor + Highlight;
}