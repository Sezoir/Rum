#include <catch.hpp>
#include <Rum.hpp>
#include <Platform/Windows/WindowsWindow.hpp>

class WindowTest : public Rum::Core::Window
{
public:
    ~WindowTest() = default;

    bool init() override
    {
        return mWindow.init();
    }

    [[nodiscard]] bool isOpen() const override
    {
        return mWindow.isOpen();
    }

    void pollInput() override
    {
        mWindow.pollInput();
    }

    void update() override
    {
        mWindow.update();
    }

    void keyPress(Key key)
    {
        Rum::Events::KeyEvent event;
        event.code = key;
        notify(Rum::Events::KeyPressedEvent(event));
    }

    void keyReleased(Key key)
    {
        Rum::Events::KeyEvent event;
        event.code = key;
        notify(Rum::Events::KeyReleasedEvent(event));
    }

    void cursorPosition(glm::vec2 pos)
    {
        notify(Rum::Events::MouseMoveEvent(pos.x, pos.y));
    }

    void mouseOffset(glm::vec2 offset)
    {
        notify(Rum::Events::MouseScrolledEvent(offset.x, offset.y));
    }

private:
    Rum::Platform::WindowsWindow mWindow{Rum::Core::WindowConfig{}};
};

TEST_CASE("Testing key input", "[WindowPlatform][Input]")
{
    WindowTest window;
    Rum::Core::Input input;
    input.init(&window);

    SECTION("'A' Key Pressed")
    {
        window.keyPress(Key::A);
        REQUIRE(input.isKeyPressed(Key::A));
    }

    SECTION("'6' Key Pressed")
    {
        window.keyPress(Key::Num6);
        REQUIRE(input.isKeyPressed(Key::Num6));
    }

    SECTION("'A' Key Released")
    {
        window.keyReleased(Key::A);
        REQUIRE_FALSE(input.isKeyPressed(Key::A));
    }

    SECTION("'6' Key Released")
    {
        window.keyReleased(Key::Num6);
        REQUIRE_FALSE(input.isKeyPressed(Key::Num6));
    }
}

TEST_CASE("Testing mouse input", "[WindowPlatform][Input]")
{
    WindowTest window;
    Rum::Core::Input input;
    input.init(&window);

    SECTION("Cursor position")
    {
        glm::vec2 pos{0.76, 0.34};
        window.cursorPosition(pos);
        REQUIRE(input.getCursorPosition() == pos);
    }

    SECTION("Scroll wheel position")
    {
        glm::vec2 pos{0.23, 0.75};
        window.mouseOffset(pos);
        REQUIRE(input.getMouseOffset() == pos);
    }
}