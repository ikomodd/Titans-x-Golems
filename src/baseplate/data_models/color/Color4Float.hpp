#pragma once

struct Color4f {

    enum COLORF_Pressets {
        
        WHITE,
        BLACK,
        RED,
        GREEN,
        BLUE,
        TRANSPARENT
    };

    float R, G, B, A;

    //

    Color4f(float r, float g, float b, float a) : R(r), G(g), B(b), A(a) {}
    Color4f(float grey_scale) : R(grey_scale), G(grey_scale), B(grey_scale), A(255) {}
    Color4f(COLORF_Pressets presset) {

        switch (presset) {
            case WHITE:       {R = 1.f; G = 1.f; B = 1.f; A = 1.f;} break;
            case BLACK:       {R =   0; G =   0; B =   0; A = 1.f;} break;
            case RED:         {R = 1.f; G =   0; B =   0; A = 1.f;} break;
            case GREEN:       {R =   0; G = 1.f; B =   0; A = 1.f;} break;
            case BLUE:        {R =   0; G =   0; B = 1.f; A = 1.f;} break;
            case TRANSPARENT: {R =   0; G =   0; B =   0; A =   0;} break;
        }
    }
};