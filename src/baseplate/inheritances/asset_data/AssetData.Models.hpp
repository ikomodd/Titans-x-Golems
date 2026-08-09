#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <glad/glad.h>

#include "../../data_models/vector/Vector2.hpp"

//

namespace baseplate::asset {

    struct AssetModel {
    protected:

        AssetModel() {}
        virtual ~AssetModel() {}
    };

    struct TextureAsset : public AssetModel {

        GLuint texture;
        Vector2i textureSize = 0;

        TextureAsset(std::string texture_path) {

            std::string fullPath = "../" + texture_path;
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
    };

    //

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
}