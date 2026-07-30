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

        GLuint Texture;
        Vector2i TextureSize = 0;

        TextureAsset(std::string texture_path) {

            std::string FullPath = "../" + texture_path;
            SDL_Surface* OriginalSurface = IMG_Load(FullPath.c_str());

            if (!OriginalSurface) {
                std::cerr << "[baseplate::asset::TextureAsset] Falha ao carregar: " << texture_path << ": \n" << SDL_GetError() << "\n";
                Texture = 0;
                return;
            }

            SDL_Surface* ConvertedSurface = SDL_ConvertSurface(OriginalSurface, SDL_PIXELFORMAT_RGBA32);
            SDL_DestroySurface(OriginalSurface);

            TextureSize = Vector2i(ConvertedSurface->w, ConvertedSurface->h);

            glGenTextures(1, &Texture);
            glBindTexture(GL_TEXTURE_2D, Texture);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ConvertedSurface->w, ConvertedSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, ConvertedSurface->pixels);

            SDL_DestroySurface(ConvertedSurface);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    };

    //

    struct ShaderAsset : public AssetModel {

        GLuint Program;

        ShaderAsset(std::string vertex_source, std::string fragment_source) {

            GLuint VertexShader = CompileShader(GL_VERTEX_SHADER, vertex_source.c_str());
            GLuint FragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragment_source.c_str());

            Program = glCreateProgram();
            glAttachShader(Program, VertexShader);
            glAttachShader(Program, FragmentShader);
            glLinkProgram(Program);

            GLint Success;
            glGetProgramiv(Program, GL_LINK_STATUS, &Success);
            if (!Success) {
                char Log[512];
                glGetProgramInfoLog(Program, 512, nullptr, Log);
                std::cerr << "[ASSET_ShaderAsset] Erro ao criar programa: " << Log << "\n";
            }

            glDeleteShader(VertexShader);
            glDeleteShader(FragmentShader);
        }

        void Bind() {

            glUseProgram(Program);
        }

    private:

        GLuint CompileShader(GLenum type, std::string source_path) {

            std::ifstream File("../" + source_path);
            std::stringstream Buffer;
            Buffer << File.rdbuf();
            std::string StringSource = Buffer.str();
            const char* Source = StringSource.c_str();

            //

            GLuint Shader = glCreateShader(type);
            glShaderSource(Shader, 1, &Source, nullptr);
            glCompileShader(Shader);

            GLint Success;
            glGetShaderiv(Shader, GL_LINK_STATUS, &Success);
            if (!Success) {
                char Log[512];
                glGetShaderInfoLog(Program, 512, nullptr, Log);
                std::cerr << "[ASSET_ShaderAsset] Erro ao criar compilar shader: " << Log << "\n";
            }

            return Shader;
        }
    };
}