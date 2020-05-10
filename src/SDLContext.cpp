#include "SDLContext.h"

#include <iostream>
#include <stdexcept>

namespace
{
    static int frameBufferSizeCallback(void* data, SDL_Event* event)
    {
        if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_RESIZED)
        {
            SDL_Window* windows = SDL_GetWindowFromID(event->window.windowID);
            if (windows == (SDL_Window*)data)
            {
                glViewport(0, 0, event->window.data1, event->window.data2);
            }
        }
        return 0;
    }
}

namespace OpenGLTutorial
{
    SDLContext::SDLContext(const char* vertexShaderPath, const char* fragmentShaderPath)
    {
        if (SDL_Init(SDL_INIT_VIDEO) != SDL_SUCCESS)
        {
            throw std::runtime_error("failed to initialize SDL video");
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

        m_window = SDL_CreateWindow("OpenGL Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
        m_glContext = SDL_GL_CreateContext(m_window);

        gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

        glViewport(0, 0, 800, 600);

        SDL_AddEventWatch(frameBufferSizeCallback, m_window);

        SDL_GL_SwapWindow(m_window);

        // Shaders
        m_shaders = std::make_unique<Shader>(vertexShaderPath, fragmentShaderPath);
        m_shaders->use();
    }

    SDLContext::~SDLContext()
    {
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }
}
