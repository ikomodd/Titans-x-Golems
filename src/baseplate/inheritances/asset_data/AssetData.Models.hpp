#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glad/glad.h>

#include "../../data_models/vector/Vector2.hpp"

//

namespace baseplate::asset {

    struct AssetModel {
    protected:

        AssetModel() {}
        virtual ~AssetModel() {}
    };

    // Textura

    struct TextureAsset : public AssetModel {

        GLuint texture;
        Vector2i textureSize = 0;

        bool isDynamic = false;

        // Cria o asset a partir de um path

        TextureAsset(std::string texture_path) {

            std::string fullPath = "../" + texture_path; // <- tem que tirar isso
            SDL_Surface* originalSurface = IMG_Load(fullPath.c_str());

            if (!originalSurface) {
                std::cerr << "[baseplate::asset::TextureAsset] Falha ao carregar: " << texture_path << ": \n" << SDL_GetError() << "\n";
                texture = 0;
                return;
            }

            SDL_Surface* convertedSurface = SDL_ConvertSurface(originalSurface, SDL_PIXELFORMAT_RGBA32);
            SDL_DestroySurface(originalSurface);

            textureSize = Vector2i(convertedSurface->w, convertedSurface->h);

            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, convertedSurface->w, convertedSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, convertedSurface->pixels);

            SDL_DestroySurface(convertedSurface);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        // Cria o asset a partir de um texto para um asset de texto

        TextureAsset(std::string text, Color4 color, TTF_Font* font) {

            isDynamic = true;

            SDL_Color textColor = {(Uint8)color.R, (Uint8)color.G, (Uint8)color.B, (Uint8)color.A};
            SDL_Surface* originalTextSurface = TTF_RenderText_Blended(font, text.c_str(), 0, textColor);
            
            if (!originalTextSurface) {
                std::cerr << "[baseplate::asset::TextureAsset] Falha ao gerar texto: " << text << "\n" << SDL_GetError() << "\n";
                texture = 0;
                return;
            }

            SDL_Surface* convertedTextSurface = SDL_ConvertSurface(originalTextSurface, SDL_PIXELFORMAT_RGBA32);
            SDL_DestroySurface(originalTextSurface);

            textureSize = Vector2i(convertedTextSurface->w, convertedTextSurface->h);

            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, convertedTextSurface->w, convertedTextSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, convertedTextSurface->pixels);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        ~TextureAsset() {

            glDeleteTextures(1, &texture);
        }
    };

    // Shader

    struct ShaderAsset : public AssetModel {

        GLuint program;

        ShaderAsset(std::string vertex_source, std::string fragment_source) {

            GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertex_source.c_str());
            GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragment_source.c_str());

            program = glCreateProgram();
            glAttachShader(program, vertexShader);
            glAttachShader(program, fragmentShader);
            glLinkProgram(program);

            GLint success;
            glGetProgramiv(program, GL_LINK_STATUS, &success);
            if (!success) {
                char log[512];
                glGetProgramInfoLog(program, 512, nullptr, log);
                std::cerr << "[baseplate::asset::ShaderAsset] Erro ao criar programa: " << log << "\n";
            }

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
        }

        ~ShaderAsset() {

            glDeleteProgram(program);
        }

    private:

        GLuint CompileShader(GLenum type, std::string source_path) {

            std::ifstream file("../" + source_path);
            std::stringstream buffer;
            buffer << file.rdbuf();

            std::string stringSource = buffer.str();
            const char* source = stringSource.c_str();

            //

            GLuint shader = glCreateShader(type);
            glShaderSource(shader, 1, &source, nullptr);
            glCompileShader(shader);

            GLint success;
            glGetShaderiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                char log[512];
                glGetShaderInfoLog(program, 512, nullptr, log);
                std::cerr << "[baseplate::asset::ShaderAsset] Erro ao criar compilar shader: " << log << "\n";
            }

            return shader;
        }
    };

    struct FontAsset : public AssetModel {

        TTF_Font* font;

        FontAsset(std::string font_path, float size) {

            std::string fullPath = "../" + font_path;
            font = TTF_OpenFont(fullPath.c_str(), size);

            if (font == nullptr)
                std::cerr << "[baseplate::asset::FontAsset] Erro ao criar font: " << font_path << "\n" << SDL_GetError() << "\n";
        }
        ~FontAsset() {

            TTF_CloseFont(font);
        }
    };
}