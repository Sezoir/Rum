#include "ShaderManager.hpp"
#include "Core/Log.hpp"
#include <algorithm>

namespace Rum::Renderer
{
    ShaderManager::ShaderManager()
    {
        mShaders.reserve(30);
    }

    std::shared_ptr<Shader> ShaderManager::createShader(const std::string_view name, const std::string_view vertexPath,
                                                        const std::string_view fragPath)
    {
        if(auto shad = *std::find_if(mShaders.begin(), mShaders.end(),
                                     [name](std::shared_ptr<Shader> shader) { return shader->getName() == name; }))
        {
            RUM_CORE_WARN("Shader with name '{}' already exists. Returning existing shader.", name);
            return shad;
        }
        mShaders.push_back(Shader::create(name.data(), vertexPath.data(), fragPath.data()));
        return mShaders.back();
    }

    std::shared_ptr<Shader> ShaderManager::getShader(const std::string_view name)
    {
        for(auto shader : mShaders)
            if(shader->getName() == name)
                return shader;
        RUM_CORE_ERROR("Shader with name '{}' does not exist.", name);
        return nullptr;
    }

    void ShaderManager::removeShader(const std::string_view name)
    {
        mShaders.erase(std::remove_if(mShaders.begin(), mShaders.end(),
                                      [name](std::shared_ptr<Shader> shader) { return shader->getName() == name; }),
                       mShaders.end());
    }
} // namespace Rum::Renderer