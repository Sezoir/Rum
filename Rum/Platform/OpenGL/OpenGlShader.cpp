#include "OpenGlShader.hpp"
#include "Core/Log.hpp"
#include "OpenGLUtilities.hpp"
#include <sstream>
#include <fstream>

namespace Rum::Platform::OpenGL
{
    OpenGLShader::OpenGLShader(const std::string& name, std::string& vertexPath, std::string& fragPath)
        : mName(name)
        , mVertexPath(vertexPath)
        , mFragPath(fragPath)
    {
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(mShaderID);
    }

    const std::string& OpenGLShader::getName()
    {
        return mName;
    }

    bool OpenGLShader::compile()
    {
        std::ifstream vertexFile, fragmentFile;
        std::stringstream vertexStream, fragmentStream;
        try
        {
            vertexFile.open(mVertexPath);
            fragmentFile.open(mFragPath);
            vertexStream << vertexFile.rdbuf();
            fragmentStream << fragmentFile.rdbuf();
            vertexFile.close();
            fragmentFile.close();
        }
        catch(std::ifstream::failure& e)
        {
            RUM_CORE_ERROR("Error: Failed to compile shader. One of the following files could not be read "
                           "successfully:\n {} \n {} \n with the following error: \n {}",
                           mVertexPath, mFragPath, e.what());
            return false;
        }

        return compile(vertexStream.str(), fragmentStream.str());
    }

    bool OpenGLShader::compile(const std::string& vertexCode, const std::string& fragmentCode)
    {
        createShaderProgram(vertexCode, fragmentCode);
        return true;
    }

    void OpenGLShader::bind()
    {
        glUseProgram(mShaderID);
    }

    void OpenGLShader::unbind()
    {
        glUseProgram(0);
    }

    void OpenGLShader::createShaderProgram(const std::string& vertexCode, const std::string& fragCode)
    {
        // Create base shaders
        GLuint vertexID = createShader(vertexCode, ShaderType::Vertex);
        GLuint fragID = createShader(fragCode, ShaderType::Fragment);

        // Create program
        mShaderID = glCreateProgram();
        glAttachShader(mShaderID, vertexID);
        glAttachShader(mShaderID, fragID);
        glLinkProgram(mShaderID);

        // Check for linker errors
        checkForCompileErrors(mShaderID, CompilationStage::Linking, ShaderType::Program);

        // Delete shaders
        glDeleteShader(vertexID);
        glDeleteShader(fragID);
    }

    GLuint OpenGLShader::createShader(const std::string& shaderCode, ShaderType type)
    {
        // Create shader
        GLuint shaderID = glCreateShader(getGLShaderType(type));
        const char* code = shaderCode.c_str();
        glShaderSource(shaderID, 1, &code, NULL);
        glCompileShader(shaderID);

        // Check for compilation errors
        checkForCompileErrors(shaderID, CompilationStage::Compile, type);

        return shaderID;
    }

    void OpenGLShader::checkForCompileErrors(GLuint id, CompilationStage compStage, ShaderType shaderType)
    {
        int success;
        switch(compStage)
        {
            case Renderer::Shader::CompilationStage::Compile:
                glGetShaderiv(id, getGLCompilationType(compStage), &success);
                break;
            case Renderer::Shader::CompilationStage::Linking:
                glGetProgramiv(id, getGLCompilationType(compStage), &success);
                break;
        }

        if(!success)
        {
            char infoLog[512];
            glGetProgramInfoLog(id, 512, NULL, infoLog);
            RUM_CORE_CRITICAL("Error: Shader of type: {} failed in the stage {} with error log:\n {}",
                              getShaderTypeName(shaderType), getCompilationStage(compStage), infoLog);
        }
    }

} // namespace Rum::Platform::OpenGL