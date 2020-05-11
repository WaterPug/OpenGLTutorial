#ifndef OPEN_GL_TUTORIAL_HELLO_TRIANGLE
#define OPEN_GL_TUTORIAL_HELLO_TRIANGLE

#include "SDL2/SDL.h"
#include "glad/glad.h"

#include "SDLContext.h"

#include <iostream>

namespace OpenGLTutorial
{
    namespace HelloTriangle
    {
        constexpr const char* vertexShaderPath("..\\shaders\\HelloTriangle\\vertex.glsl");
        constexpr const char* fragmentShaderPath("..\\shaders\\HelloTriangle\\fragment.glsl");

        class RendererBase
        {
        public:
            RendererBase() = default;
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
                std::cout << "triangle 1 draw\n";
                renderer->drawTriangle1();
            }
            else if (sdlEvent.key.keysym.sym == SDLK_2)
            {
                std::cout << "triangle 2 draw\n";
                renderer->drawTriangle2();
            }
            else if (sdlEvent.key.keysym.sym == SDLK_3)
            {
                std::cout << "rectangle using ebo\n";
                renderer->drawRectangle();
            }
            else if (sdlEvent.key.keysym.sym == SDLK_w)
            {
                std::cout << "toggle wireframe\n";
                context->toggleWireframe();
                glPolygonMode(GL_FRONT_AND_BACK, context->isWireframeEnabled() ? GL_LINE : GL_FILL);
            }
        }

        namespace Exercice1
        {
            constexpr float rectangleVertices[] = {
                 0.5f,  0.5f, 0.0f,  // top right
                 0.5f, -0.5f, 0.0f,  // bottom right
                -0.5f, -0.5f, 0.0f,  // bottom left

                 0.5f, -0.5f, 0.0f,  // bottom right
                -0.5f, -0.5f, 0.0f,  // bottom left
                -0.5f,  0.5f, 0.0f   // top left 
            };

            class Renderer : public RendererBase
            {
            public:
                Renderer() { initialize(); };
                virtual ~Renderer() = default;

                void drawTriangle1() override
                {
                    glBindVertexArray(m_vao);
                    glDrawArrays(GL_TRIANGLES, 0, 6);
                };

            protected:
                void initialize() override
                {
                    // Create VBO && VAO
                    glGenBuffers(1, &m_vbo);
                    glGenVertexArrays(1, &m_vao);
                    // Bind vertex array first, then vertex buffer(s), then configure vertex attributes
                    glBindVertexArray(m_vao);

                    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), rectangleVertices, GL_STATIC_DRAW);

                    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
                    glEnableVertexAttribArray(0);
                }

            private:
                uint32_t m_vao;
                uint32_t m_vbo;
            };
        }

        namespace Exercice2
        {
            constexpr float triangleVertices1[] = {
                 0.5f,  0.5f, 0.0f,  // top right
                 0.5f, -0.5f, 0.0f,  // bottom right
                -0.5f, -0.5f, 0.0f   // bottom left
            };

            constexpr float triangleVertices2[] = {
                 0.5f, -0.5f, 0.0f,  // bottom right
                -0.5f, -0.5f, 0.0f,  // bottom left
                -0.5f,  0.5f, 0.0f   // top left 
            };

            class Renderer : public RendererBase
            {
            public:
                Renderer() { initialize(); };
                virtual ~Renderer() = default;

                void drawTriangle1() override
                {
                    glBindVertexArray(m_vao1);
                    glDrawArrays(GL_TRIANGLES, 0, 3);
                };

                void drawTriangle2() override
                {
                    glBindVertexArray(m_vao2);
                    glDrawArrays(GL_TRIANGLES, 0, 3);
                };

                void drawRectangle() override
                {
                    glBindVertexArray(m_vao1);
                    glDrawArrays(GL_TRIANGLES, 0, 3);
                    glBindVertexArray(m_vao2);
                    glDrawArrays(GL_TRIANGLES, 0, 3);
                };

            protected:
                void initialize() override
                {
                    // Create first VBO && VAO pair
                    glGenBuffers(1, &m_vbo1);
                    glGenVertexArrays(1, &m_vao1);
                    // Bind vertex array first, then vertex buffer(s), then configure vertex attributes
                    glBindVertexArray(m_vao1);

                    glBindBuffer(GL_ARRAY_BUFFER, m_vbo1);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices1), triangleVertices1, GL_STATIC_DRAW);

                    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
                    glEnableVertexAttribArray(0);

                    // Create second VBO && VAO pair
                    glGenBuffers(1, &m_vbo2);
                    glGenVertexArrays(1, &m_vao2);
                    // Bind vertex array first, then vertex buffer(s), then configure vertex attributes
                    glBindVertexArray(m_vao2);

                    glBindBuffer(GL_ARRAY_BUFFER, m_vbo2);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices2), triangleVertices2, GL_STATIC_DRAW);

                    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
                    glEnableVertexAttribArray(0);
                }

            private:
                uint32_t m_vao1;
                uint32_t m_vao2;
                uint32_t m_vbo1;
                uint32_t m_vbo2;
            };
        }

        namespace Lesson
        {
            constexpr float rectangleVertices[] = {
                 0.5f,  0.5f, 0.0f,  // top right
                 0.5f, -0.5f, 0.0f,  // bottom right
                -0.5f, -0.5f, 0.0f,  // bottom left
                -0.5f,  0.5f, 0.0f   // top left 
            };

            constexpr uint32_t rectangleIndices[] = {  // note that we start from 0!
                0, 1, 3,   // first triangle
                1, 2, 3    // second triangle
            };

            class Renderer : public RendererBase
            {
            public:
                Renderer() { initialize(); };
                virtual ~Renderer() = default;

                void drawTriangle1() override
                {
                    glBindVertexArray(m_vao);
                    glDrawArrays(GL_TRIANGLES, 0, 3);
                };

                void drawTriangle2() override
                {
                    glBindVertexArray(m_vao);
                    glDrawArrays(GL_TRIANGLES, 1, 3);
                };

                void drawRectangle() override
                {
                    glBindVertexArray(m_vao);
                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                    glBindVertexArray(0);
                };

            protected:
                void initialize() override
                {
                    // Create VBO, VAO && EBO
                    glGenBuffers(1, &m_vbo);
                    glGenBuffers(1, &m_ebo);
                    glGenVertexArrays(1, &m_vao);
                    // Bind vertex array first, then vertex buffer(s), then configure vertex attributes
                    glBindVertexArray(m_vao);

                    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), rectangleVertices, GL_STATIC_DRAW);

                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
                    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangleIndices), rectangleIndices, GL_STATIC_DRAW);

                    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
                    glEnableVertexAttribArray(0);
                }

            private:
                uint32_t m_vao;
                uint32_t m_vbo;
                uint32_t m_ebo;
            };
        }
    }
}

#endif