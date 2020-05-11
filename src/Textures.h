#ifndef OPEN_GL_TUTORIAL_TEXTURES
#define OPEN_GL_TUTORIAL_TEXTURES

#include "SDL2/SDL.h"
#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "SDLContext.h"
#include "Shader.h"

#include <iostream>

namespace OpenGLTutorial
{
    namespace Textures
    {
        constexpr const char* vertexShaderPath("..\\shaders\\Textures\\vertex.glsl");
        constexpr const char* fragmentShaderPath("..\\shaders\\Textures\\fragment.glsl");
        constexpr const char* containerJPGPath("..\\data\\container.jpg");
        constexpr const char* facePNGPath("..\\data\\face.png");

        // Update this fx --> Pass struct?
        unsigned char* loadContainerImage(int& width, int &height, int& nrChannels)
        {
            return stbi_load(containerJPGPath, &width, &height, &nrChannels, 0);
        }

        class RendererBase
        {
        public:
            RendererBase() = default;
            RendererBase(Shader* shader);
            virtual ~RendererBase() = default;

            virtual void drawTriangle1() = 0 {};
            virtual void drawTriangle2() {};
            virtual void drawRectangle() {};

        protected:
            virtual void initialize() = 0;
        };

        void processKeyDown(SDL_Event& sdlEvent, SDLContext* context, RendererBase* renderer)
        {
            if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
            {
                context->quit();
            }
            else if (sdlEvent.key.keysym.sym == SDLK_r)
            {
                std::cout << "R\n";
                glClearColor(0.7f, 0.0f, 0.0f, 0.7f);
                glClear(GL_COLOR_BUFFER_BIT);
            }
            else if (sdlEvent.key.keysym.sym == SDLK_g)
            {
                std::cout << "G\n";
                glClearColor(0.0f, 0.7f, 0.0f, 0.7f);
                glClear(GL_COLOR_BUFFER_BIT);
            }
            else if (sdlEvent.key.keysym.sym == SDLK_b)
            {
                std::cout << "B\n";
                glClearColor(0.0f, 0.0f, 0.7f, 0.7f);
                glClear(GL_COLOR_BUFFER_BIT);
            }
            else if (sdlEvent.key.keysym.sym == SDLK_1)
            {
                std::cout << "triangle with texture draw\n";
                renderer->drawTriangle1();
            }
            else if (sdlEvent.key.keysym.sym == SDLK_w)
            {
                std::cout << "toggle wireframe\n";
                context->toggleWireframe();
                glPolygonMode(GL_FRONT_AND_BACK, context->isWireframeEnabled() ? GL_LINE : GL_FILL);
            }
        }

        namespace Lesson
        {
            // Formated : X, Y, Z, R, G, B, S, T
            //            Pos    , Color  , texCoord
            //     bytes: 12     , 12     , 8
            constexpr float vertices[] = {
                // Pos               Colors             Tex coord
                -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,  // lower-left corner
                 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,  // lower-right corner
                 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.5f   // top-center corner
            };

            class Renderer : public RendererBase
            {
            public:
                Renderer() { initialize(); }
                Renderer(Shader* shader) : m_shader(shader) { initialize(); }
                virtual ~Renderer() = default;

                void drawTriangle1() override
                {
                    glBindTexture(GL_TEXTURE_2D, m_texture1);
                    glBindTexture(GL_TEXTURE_2D, m_texture2);
                    glBindVertexArray(m_vao);
                    glDrawArrays(GL_TRIANGLES, 0, 3);
                };

            protected:
                void initialize() override
                {
                    glGenVertexArrays(1, &m_vao);
                    glGenBuffers(1, &m_vbo);

                    glBindVertexArray(m_vao);

                    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

                    // position
                    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
                    glEnableVertexAttribArray(0);
                    // color
                    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
                    glEnableVertexAttribArray(1);
                    // texCoords
                    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
                    glEnableVertexAttribArray(2);

                    // Textures
                    // Container texture
                    glGenTextures(1, &m_texture1);
                    glActiveTexture(GL_TEXTURE0); // Should be active by default
                    glBindTexture(GL_TEXTURE_2D, m_texture1);

                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                    // Load Container texture
                    int width, height, nrChannels;
                    unsigned char* data = nullptr;
                    data = stbi_load(containerJPGPath, &width, &height, &nrChannels, 0);

                    if (data)
                    {
                        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                        glGenerateMipmap(GL_TEXTURE_2D);
                    }
                    else
                    {
                        throw "failed to load container.jpg";
                    }

                    stbi_image_free(data);

                    // Face texture
                    glGenTextures(1, &m_texture2);
                    glActiveTexture(GL_TEXTURE1); // Should be active by default
                    glBindTexture(GL_TEXTURE_2D, m_texture2);

                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                    data = nullptr;
                    stbi_set_flip_vertically_on_load(true);
                    data = stbi_load(facePNGPath, &width, &height, &nrChannels, 0);

                    if (data)
                    {
                        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                        glGenerateMipmap(GL_TEXTURE_2D);
                    }
                    else
                    {
                        throw "failed to load awesomeface.jpg";
                    }

                    stbi_image_free(data);

                    m_shader->setUniformInt("texture1", 0);
                    m_shader->setUniformInt("texture2", 1);
                }

            private:
                uint32_t m_vao;
                uint32_t m_vbo;

                uint32_t m_texture1;
                uint32_t m_texture2;

                Shader* m_shader;
            };
        }
    }
}

#endif