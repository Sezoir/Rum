#pragma once
// Std libs
#include <vector>
#include <memory>
#include <string_view>
#include <map>
// Project files
#include "Scene.hpp"
#include "Core/Assert.hpp"

namespace Rum::Scene
{
    /**
     * Manager for all the scenes in a game. This is also used for controlling the main scene viewpoint (e.g: main menu,
     * game world, etc), and sub scene viewpoints (e.g: hud gui, pause menu, etc).
     */
    class SceneManager
    {
    public:
        SceneManager() = default;
        ~SceneManager() = default;

        Scene& makeScene(const std::string_view name)
        {
            auto result = mScenes.emplace(name, std::make_shared<Scene>());
            RUM_CORE_ASSERT(result.second,
                            (std::stringstream() << "Scene with name '" << name
                                                 << "' already exists. Returning the existing Scene instead.")
                                .str());
            return *result.first->second;
        }

        Scene& getScene(const std::string_view& name);

        /**
         * Sets the main scenes for the window. Note that this will also automatically clear all of the subscenes.
         * This should only really be called when visually transferring between scenes. The new scene should already
         * be loaded before this is called.
         * @param name
         */
        void setMainScene(const std::string_view& name);

        void setActiveScene(const std::string_view& name);

        void setActiveScenes(const std::vector<std::string>& names);

        void onUpdate(const Core::TimeStep& timestep);

        void onDraw();

    private:
        std::shared_ptr<Scene> mMainScene = nullptr;
        std::vector<std::shared_ptr<Scene>> mSubScenes;
        std::map<std::string, std::shared_ptr<Scene>, std::less<>> mScenes;
    };
} // namespace Rum::Scene
