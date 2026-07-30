#pragma once

namespace baseplate {

    struct Color4f;

    enum class ColorPressets {
        
        WHITE,
        BLACK,
        RED,
        GREEN,
        BLUE,
        TRANSPARENT
    };

    struct Color4 {

        unsigned int R, G, B, A;

        //

        Color4(unsigned int r, unsigned int g, unsigned int b, unsigned int a) : R(r), G(g), B(b), A(a) {}
        Color4(unsigned int grey_scale) : R(grey_scale), G(grey_scale), B(grey_scale), A(255) {}
        Color4(ColorPressets presset) {

            switch (presset) {
                case ColorPressets::WHITE:       {R = 255; G = 255; B = 255; A = 255;} break;
                case ColorPressets::BLACK:       {R =   0; G =   0; B =   0; A = 255;} break;
                case ColorPressets::RED:         {R = 255; G =   0; B =   0; A = 255;} break;
                case ColorPressets::GREEN:       {R =   0; G = 255; B =   0; A = 255;} break;
                case ColorPressets::BLUE:        {R =   0; G =   0; B = 255; A = 255;} break;
                case ColorPressets::TRANSPARENT: {R =   0; G =   0; B =   0; A =   0;} break;
            }
        }

        Color4f Normalize();
    };

    // Color4f ---------------

    struct Color4f {

        float R, G, B, A;

        //

        Color4f(float r, float g, float b, float a) : R(r), G(g), B(b), A(a) {}
        Color4f(float grey_scale) : R(grey_scale), G(grey_scale), B(grey_scale), A(255) {}
        Color4f(ColorPressets presset) {

            switch (presset) {
                case ColorPressets::WHITE:       {R = 1.f; G = 1.f; B = 1.f; A = 1.f;} break;
                case ColorPressets::BLACK:       {R =   0; G =   0; B =   0; A = 1.f;} break;
                case ColorPressets::RED:         {R = 1.f; G =   0; B =   0; A = 1.f;} break;
                case ColorPressets::GREEN:       {R =   0; G = 1.f; B =   0; A = 1.f;} break;
                case ColorPressets::BLUE:        {R =   0; G =   0; B = 1.f; A = 1.f;} break;
                case ColorPressets::TRANSPARENT: {R =   0; G =   0; B =   0; A =   0;} break;
            }
        }
    };

    // Conversão Color4 ---

    inline Color4f Color4::Normalize() {

        return Color4f((float)R / 255, (float)G / 255, (float)B / 255, (float)A / 255);
    }
}