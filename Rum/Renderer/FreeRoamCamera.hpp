#pragma once
// External dependencies
#include <glm/glm.hpp>
// Project files
#include "Camera.hpp"
#include "Core/KeyCodes.hpp"

namespace Rum::Renderer
{
    class FreeRoamCamera : public Camera
    {
    public:
        FreeRoamCamera(float fov, float nearClip, float farClip, float x, float y, float z, float pitch, float yaw,
                       float roll);
        FreeRoamCamera(float fov, float nearClip, float farClip);
        FreeRoamCamera(float fov, float nearClip, float farClip, float x, float y, float z);
        ~FreeRoamCamera() = default;
        void updateProjection() override;
        void updateView() override;
        void updatePosition();
        void updateDirection();
        void onEvent(const Events::Event& event) override;
        void update(const Core::TimeStep& timestep) override;
        void setFov(float fov);
        void setPosition(float x, float y, float z);
        void setDirection(float pitch, float yaw, float roll);
        const glm::vec3& getPosition() const;
        const glm::vec3& getDirection() const;

    private:
        glm::vec3 calculateDirection(const glm::vec3& eulerAngles /* pitch, yaw, roll */);

        float mFov;
        float mNearClip;
        float mFarClip;
        float mSpeed = 0.01f;
        float mMouseSensitivity = 0.1f;
        uint32_t mHeight;
        uint32_t mWidth;
        bool mFocusGuard;
        glm::vec3 mPosition;      // x, y, z
        glm::vec3 mEulerAngles;   // pitch, yaw, roll
        glm::vec3 mDirection;     // x, y, z
        glm::vec2 mPrevCursorPos; // x, y
        glm::vec3 mRightDir;
        glm::vec3 mUpDir;

        Core::Keyboard::Key mForward = Core::Keyboard::Key::W;
        Core::Keyboard::Key mBack = Core::Keyboard::Key::S;
        Core::Keyboard::Key mLeft = Core::Keyboard::Key::A;
        Core::Keyboard::Key mRight = Core::Keyboard::Key::D;
    };
} // namespace Rum::Renderer
