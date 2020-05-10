
#include "glad/glad.h"
#include "Shader.h"
#include <fstream>
#include <iostream>

namespace OpenGLTutorial
{
    // TODO: Put in Utility class if needed...
    namespace Utility
    {
        inline std::string getFileContent(const std::string& path)
        {
            std::ifstream file(path);

            std::string content((std::istreambuf_iterator<char>(file)),
                (std::istreambuf_iterator<char>()));
            return content;
        }
    }

    Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
    {
        m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
        m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        compile(m_vertexShader, Utility::getFileContent(vertexPath).c_str());
        compile(m_fragmentShader, Utility::getFileContent(fragmentPath).c_str());

        m_shaderProgram = glCreateProgram();
        glAttachShader(m_shaderProgram, m_vertexShader);
        glAttachShader(m_shaderProgram, m_fragmentShader);

        linkShaders();
    }

    Shader::~Shader()
    {
        glDeleteShader(m_vertexShader);
        glDeleteShader(m_fragmentShader);
    }

    void Shader::use() const 
    { 
        glUseProgram(m_shaderProgram); 
    }

    void Shader::setUniformBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(m_shaderProgram, name.c_str()), static_cast<int>(value));
    }
    void Shader::setUniformInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(m_shaderProgram, name.c_str()), value);
    }
    void Shader::setUniformFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(m_shaderProgram, name.c_str()), value);
    }

    void Shader::compile(uint32_t shader, const char* data) const
    {
        glShaderSource(shader, 1, &data, nullptr);
        glCompileShader(shader);

        int  success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }

    void Shader::linkShaders() const
    {
        glLinkProgram(m_shaderProgram);
        int  success;
        char infoLog[512];
        glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
        }
    }
}