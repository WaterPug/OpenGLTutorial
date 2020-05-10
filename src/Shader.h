#ifndef OPEN_GL_TUTORIAL_SHADER
#define OPEN_GL_TUTORIAL_SHADER

#include <string>

namespace OpenGLTutorial
{
    class Shader
    {
    public:
        Shader() = delete;
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader();
      
        void use() const;

        void setUniformBool(const std::string& name, bool value) const;
        void setUniformInt(const std::string& name, int value) const;
        void setUniformFloat(const std::string& name, float value) const;

    private:
        uint32_t m_vertexShader;
        uint32_t m_fragmentShader;
        uint32_t m_shaderProgram;

        void compile(uint32_t shader, const char* data) const;
        void linkShaders() const;
    };
}

#endif