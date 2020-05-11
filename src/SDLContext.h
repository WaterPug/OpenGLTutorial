#ifndef OPEN_GL_TUTORIAL_SDL_CONTEXT
#define OPEN_GL_TUTORIAL_SDL_CONTEXT

#include "SDL2/SDL.h"
#include "glad/glad.h"
#include "Shader.h"

#include <memory>

constexpr int SDL_SUCCESS = 0;

namespace OpenGLTutorial
{
    class SDLContext
    {
    public:
        SDLContext(const char* vertexShaderPath, const char* fragmentShaderPath);
        ~SDLContext();

        SDL_Window* getWindow() const { return m_window; }
        bool isRunning() const { return m_isRunning; }
        void quit() { m_isRunning = false; }

        bool isWireframeEnabled() const { return m_wireframeEnabled; }
        void toggleWireframe() { m_wireframeEnabled = !m_wireframeEnabled; }

        Shader* getShader() const { return m_shaders.get(); }

    private:
        SDL_Window* m_window;
        SDL_GLContext m_glContext;

        std::unique_ptr<Shader> m_shaders;

        bool m_isRunning = true;
        bool m_wireframeEnabled = false;
    };
}

#endif