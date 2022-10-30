#include "FreeRoamCamera.hpp"
// External dependencies
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
// Project files
#include <Core/Application.hpp>
#include <Events/WindowEvent.hpp>

namespace Rum::Renderer
{
    FreeRoamCamera::FreeRoamCamera(float fov, float nearClip, float farClip, float x, float y, float z, float pitch,
                                   float yaw, float roll)
        : mFov(glm::radians(fov))
        , mNearClip(nearClip)
        , mFarClip(farClip)
        , mFocusGuard(true)
        , mPosition(glm::vec3(x, y, z))
        , mEulerAngles(glm::vec3(pitch, yaw, roll))
        , mDirection(calculateDirection(mEulerAngles))
        , mPrevCursorPos(glm::vec2(0, 0))
        , mRightDir(glm::vec3(0, 0, 0))
        , mUpDir(glm::vec3(0, 0, 0))
    {
        Core::Window& window = Core::Application::getInstance().getWindow();
        mHeight = window.getConfig().mHeight;
        mWidth = window.getConfig().mWidth;
        window.addSubject(*this);
        window.setCursorControl({false, false});

        updateProjection();
        updateView();
    }

    FreeRoamCamera::FreeRoamCamera(float fov, float nearClip, float farClip)
        : FreeRoamCamera(fov, nearClip, farClip, 0, 0, 0, 0, 0, 0)
    {
    }

    FreeRoamCamera::FreeRoamCamera(float fov, float nearClip, float farClip, float x, float y, float z)
        : FreeRoamCamera(fov, nearClip, farClip, x, y, z, 0, 0, 0)
    {
    }

    void FreeRoamCamera::updateProjection()
    {
        float aspectRatio = mWidth / mHeight;
        mProjection = glm::perspective(mFov, aspectRatio, mNearClip, mFarClip);
    }

    void FreeRoamCamera::updateView()
    {
        constexpr glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        mRightDir = glm::normalize(glm::cross(mDirection, up));
        mUpDir = glm::cross(mDirection, mRightDir);
        mView = glm::lookAt(mPosition, mPosition + mDirection, up);
    }

    void FreeRoamCamera::updateDirection()
    {
        const bool focus = Core::Application::getInstance().isFocused();
        const auto& input = Core::Application::getInstance().getInput();
        const glm::vec2 cursorPos = input.getCursorPosition();
        if(focus && mFocusGuard)
        {
            mPrevCursorPos = glm::vec2(cursorPos.x, cursorPos.y);
            mFocusGuard = false;
        }
        else if(!focus)
        {
            mFocusGuard = true;
            return;
        }
        glm::vec2 cursorOffset = {cursorPos.x - mPrevCursorPos.x, cursorPos.y - mPrevCursorPos.y};
        mPrevCursorPos = cursorPos;

        cursorOffset *= mMouseSensitivity; // @TODO: Separate sensitivity values

        mEulerAngles.x -= cursorOffset.y;
        mEulerAngles.y += cursorOffset.x;

        if(mEulerAngles.x > 89.0f)
            mEulerAngles.x = 89.0f;
        if(mEulerAngles.x < -89.0f)
            mEulerAngles.x = -89.0f;

        mDirection = calculateDirection(mEulerAngles);
    }

    void FreeRoamCamera::updatePosition()
    {
        const auto input = Core::Application::getInstance().getInput();
        if(input.isKeyPressed(mForward))
            mPosition += mDirection * mSpeed;
        if(input.isKeyPressed(mBack))
            mPosition -= mDirection * mSpeed;
        if(input.isKeyPressed(mRight))
            mPosition += mRightDir * mSpeed;
        if(input.isKeyPressed(mLeft))
            mPosition -= mRightDir * mSpeed;
    }

    void FreeRoamCamera::update(const Core::TimeStep& timestep)
    {
        updateDirection();
        updatePosition();
        updateView();
        updateProjection();
    }

    void FreeRoamCamera::onEvent(const Events::Event& event)
    {
        switch(event.getEventType())
        {
            case Events::EventType::WindowResize:
            {
                auto windowEvent = event.convert<Events::WindowResizeEvent>();
                mHeight = windowEvent.getHeight();
                mWidth = windowEvent.getWidth();
                break;
            }
            default:
                return;
        }
    }

    void FreeRoamCamera::setFov(float fov)
    {
        mFov = glm::radians(fov);
    }

    void FreeRoamCamera::setPosition(float x, float y, float z)
    {
        mPosition = glm::vec3(x, y, z);
    }

    void FreeRoamCamera::setDirection(float pitch, float yaw, float roll)
    {
        mDirection = glm::normalize(glm::vec3(pitch, yaw, roll));
    }

    const glm::vec3& FreeRoamCamera::getPosition() const
    {
        return mPosition;
    }

    const glm::vec3& FreeRoamCamera::getDirection() const
    {
        return mDirection;
    }

    glm::vec3 FreeRoamCamera::calculateDirection(const glm::vec3& eulerAngles /* pitch, yaw, roll */)
    {
        return glm::normalize(glm::vec3(cos(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x)),
                                        sin(glm::radians(eulerAngles.x)),
                                        sin(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x))));
    }
}; // namespace Rum::Renderer