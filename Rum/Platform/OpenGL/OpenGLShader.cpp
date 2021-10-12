#include "OpenGLShader.hpp"
#include "Core/Log.hpp"
#include "OpenGLUtilities.hpp"
#include <sstream>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

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
        if(!mTextures.empty())
        {
            for(auto& it : mTextures)
            {
                it.second->bind(it.first);
            }
        }
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

        if(success == GL_FALSE)
        {
            char infoLog[512];
            glGetProgramInfoLog(id, 512, NULL, infoLog);
            RUM_CORE_CRITICAL("Error: Shader of type: {} failed in the stage {} with error log:\n {}",
                              getShaderTypeName(shaderType), getCompilationStage(compStage), infoLog);
        }
    }

    void OpenGLShader::setBool(const std::string& name, const bool& value)
    {
        const GLint location = glGetUniformLocation(mShaderID, name.c_str());
        glUniform1i(location, static_cast<int>(value));
    }

    void OpenGLShader::setInt(const std::string& name, const int& value)
    {
        const GLint location = glGetUniformLocation(mShaderID, name.c_str());
        glUniform1i(location, value);
    }

    void OpenGLShader::setFloat(const std::string& name, const float& value)
    {
        const GLint location = glGetUniformLocation(mShaderID, name.c_str());
        glUniform1f(location, value);
    }

    void OpenGLShader::setFloat2(const std::string& name, const glm::vec2& value)
    {
        const GLint location = glGetUniformLocation(mShaderID, name.c_str());
        glUniform2f(location, value.x, value.y);
    }

    void OpenGLShader::setFloat3(const std::string& name, const glm::vec3& value)
    {
        const GLint location = glGetUniformLocation(mShaderID, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void OpenGLShader::setFloat4(const std::string& name, const glm::vec4& value)
    {
        const GLint location = glGetUniformLocation(mShaderID, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::setMat4(const std::string& name, const glm::mat4& value)
    {
        const GLint location = glGetUniformLocation(mShaderID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }

    void OpenGLShader::setTexture(const std::string& name, const std::shared_ptr<Rum::Renderer::Texture2D> value)
    {
        int maxTextureUnits;
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnits);
        if(mTextures.size() <= GL_MAX_TEXTURE_IMAGE_UNITS)
        {
            const uint8_t textureUnit = mTextures.size();
            setInt(name, textureUnit);
            mTextures.emplace(textureUnit, std::move(value));
        }
        else
        {
            RUM_CORE_ERROR("Maximum number of texture units reached!");
        }
    }

} // namespace Rum::Platform::OpenGL