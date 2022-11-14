#pragma once
// Std libs
#include <vector>
#include <memory>
#include <string_view>
// External libs
// Project files
#include "Shader.hpp"

namespace Rum::Renderer
{
    class ShaderManager
    {
    public:
        ShaderManager();
        ~ShaderManager() = default;

        std::shared_ptr<Shader> createShader(const std::string_view name, const std::string_view vertexPath,
                                             const std::string_view fragPath);
        std::shared_ptr<Shader> getShader(const std::string_view name);
        void removeShader(const std::string_view name);

    private:
        std::vector<std::shared_ptr<Shader>> mShaders;
    };
} // namespace Rum::Renderer