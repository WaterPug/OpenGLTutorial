
#include "SDL2/SDL.h"
#include "SDLContext.h"
#include "HelloTriangle.h"
#include "Textures.h"
#include "Shader.h"

#include <iostream>
#include <memory>

using namespace OpenGLTutorial;

enum class Section
{
    Lesson = 1,
    Exercice1 = 2,
    Exercice2 = 3,
    Exercice3 = 4,
    Exercice4 = 5
};

enum class Course
{
    HelloTriangle = 1,
    Textures = 2 
};

void runHelloTriangle(Section section)
{
    std::unique_ptr<SDLContext> context = std::make_unique<SDLContext>(HelloTriangle::vertexShaderPath, HelloTriangle::fragmentShaderPath);
    std::unique_ptr<HelloTriangle::RendererBase> renderer;

    switch (section)
    {
    case Section::Lesson:
        renderer = std::make_unique<HelloTriangle::Lesson::Renderer>();
        break;
    case Section::Exercice1:
        renderer = std::make_unique<HelloTriangle::Exercice1::Renderer>();
        break;
    case Section::Exercice2:
        renderer = std::make_unique<HelloTriangle::Exercice2::Renderer>();
        break;
    default:
        std::cout << "Invalid Section\n";
    }

    SDL_Event sdlEvent;
    while (context->isRunning())
    {
        if (SDL_PollEvent(&sdlEvent) != SDL_SUCCESS)
        {
            switch (sdlEvent.type)
            {
            case SDL_QUIT: context->quit(); break;
            case SDL_KEYDOWN: processKeyDown(sdlEvent, context.get(), renderer.get()); break;
            default:
                std::cout << "Unhandled event\n";
            }
        }

        SDL_GL_SwapWindow(context->getWindow());
    }
}

void runTextures(Section section)
{
    std::unique_ptr<SDLContext> context = std::make_unique<SDLContext>(Textures::vertexShaderPath, Textures::fragmentShaderPath);
    std::unique_ptr<Textures::RendererBase> renderer;

    switch (section)
    {
    case Section::Lesson:
        renderer = std::make_unique<Textures::Lesson::Renderer>(context->getShader());
        break;
    default:
        std::cout << "Invalid Section\n";
    }

    SDL_Event sdlEvent;
    while (context->isRunning())
    {
        if (SDL_PollEvent(&sdlEvent) != SDL_SUCCESS)
        {
            switch (sdlEvent.type)
            {
            case SDL_QUIT: context->quit(); break;
            case SDL_KEYDOWN: processKeyDown(sdlEvent, context.get(), renderer.get()); break;
            default:
                std::cout << "Unhandled event\n";
            }
        }

        SDL_GL_SwapWindow(context->getWindow());
    }
}


void run(Course course, Section section)
{
    switch (course)
    {
    case Course::HelloTriangle: runHelloTriangle(section); break;
    case Course::Textures: runTextures(section); break;
    default: std::cout << "Invalid course\n";
    }
}

int main(int /*argc*/, char** /*argv[]*/)
{
    Course selectedCourse = Course::Textures;
    Section selectedSection = Section::Lesson;

    run(selectedCourse, selectedSection);

    return -1;
}