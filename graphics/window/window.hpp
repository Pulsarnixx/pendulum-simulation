#pragma once

//Forward dec.
class GLFWwindow;

class Window{

public:
    //Constr, Destr.
    Window();
    Window(unsigned int height, unsigned int width);
    ~Window();

    //Copy constr.
    Window(Window &) = delete;
    Window& operator = (const Window &) = delete;

    //Move constr.
    Window(Window &&) = delete;
    Window& operator = (Window &&) = delete;

    //Access
    unsigned int GetHeight() const { return m_Height; }
    unsigned int GetWidth() const { return m_Width; }
    GLFWwindow* GetWindowGLFW() const { return m_Window; }
    bool ShouldClose() const;
    void onUpdate() const;
    // void SetHeight(unsigned int height) { m_Height = height; }
    // void SetWidth(unsigned int width) { m_Width = width; }
    // void SetWindowSize(unsigned int height, unsigned width) { m_Height = height; m_Width = width;} 
private:

    unsigned int m_Height;
    unsigned int m_Width;
    GLFWwindow* m_Window;


};