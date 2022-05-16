#include "SceneManager.hpp"

namespace Rum::Scene
{
    Scene& SceneManager::getScene(const std::string_view& name)
    {
        return *mScenes.find(name)->second;
    }

    void SceneManager::setMainScene(const std::string_view& name)
    {
        mMainScene = mScenes.find(name)->second;
        mSubScenes.clear();
    }

    void SceneManager::setActiveScene(const std::string_view& name)
    {
        mSubScenes.push_back(mScenes.find(name)->second);
    }

    void SceneManager::setActiveScenes(const std::vector<std::string>& names)
    {
        for(auto name : names)
        {
            mSubScenes.push_back(mScenes.find(name)->second);
        }
    }

    void SceneManager::onUpdate(const Core::TimeStep& timestep)
    {
        mMainScene->onUpdate(timestep);
        for(auto scene : mSubScenes)
        {
            scene->onUpdate(timestep);
        }
    }

    void SceneManager::onDraw()
    {
        mMainScene->onDraw();
        for(auto scene : mSubScenes)
        {
            scene->onDraw();
        }
    }

} // namespace Rum::Scene
