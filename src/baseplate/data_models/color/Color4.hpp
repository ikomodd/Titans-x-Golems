#pragma once

struct Color4f;

struct Color4 {

    enum COLOR_Pressets {
        
        WHITE,
        BLACK,
        RED,
        GREEN,
        BLUE,
        TRANSPARENT
    };

    unsigned int R, G, B, A;

    //

    Color4(unsigned int r, unsigned int g, unsigned int b, unsigned int a) : R(r), G(g), B(b), A(a) {}
    Color4(unsigned int grey_scale) : R(grey_scale), G(grey_scale), B(grey_scale), A(255) {}
    Color4(COLOR_Pressets presset) {

        switch (presset) {
            case WHITE:       {R = 255; G = 255; B = 255; A = 255;} break;
            case BLACK:       {R =   0; G =   0; B =   0; A = 255;} break;
            case RED:         {R = 255; G =   0; B =   0; A = 255;} break;
            case GREEN:       {R =   0; G = 255; B =   0; A = 255;} break;
            case BLUE:        {R =   0; G =   0; B = 255; A = 255;} break;
            case TRANSPARENT: {R =   0; G =   0; B =   0; A =   0;} break;
        }
    }

    Color4f Normalize();
};