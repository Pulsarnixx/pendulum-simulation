#pragma once

#include <string>


#define DEFAULT_HEIGHT 1080
#define DEFAULT_WEIGHT 1920
#define DEFAULT_TITLE  "Title"

//Forward dec.
class GLFWwindow;

class Window{

public:
    //Constr, Destr.
    Window();
    Window(unsigned int width, unsigned int height, const std::string& title);
    ~Window();

    //Copy constr.
    Window(Window &) = delete;
    Window& operator = (const Window &) = delete;

    //Move constr.
    Window(Window &&) = delete;
    Window& operator = (Window &&) = delete;

    //Access
    GLFWwindow* GetWindowGLFW() const { return m_Window; }

    unsigned int GetHeight() const { return m_Height; }
    unsigned int GetWidth() const { return m_Width; }

    bool ShouldWindowClose() const;
    void onEvents() const;
    void onUpdate() const;
    void SetWindowDetails(unsigned int width, unsigned int height, const std::string& title);
private:

    GLFWwindow* m_Window;
    unsigned int m_Width;
    unsigned int m_Height;
    std::string  m_Title;


};