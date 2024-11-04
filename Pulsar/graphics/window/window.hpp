#pragma once

#include <string>


#define DEFAULT_HEIGHT 900
#define DEFAULT_WEIGHT 1600
#define DEFAULT_TITLE  "Title"

//Forward dec.
class GLFWwindow;
typedef void (*GLFWframebuffersizefun)(GLFWwindow*, int, int);
typedef void (* GLFWkeyfun)(GLFWwindow*,int,int,int,int);
typedef void (* GLFWcursorposfun)(GLFWwindow*,double,double);
typedef void (* GLFWscrollfun)(GLFWwindow*,double,double);


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

    void SetVsync(bool option) const;
    bool ShouldWindowClose() const;
    void onEvents() const;
    void onUpdate() const;
    void SetWindowDetails(unsigned int width, unsigned int height, const std::string& title);

    //GLFW Call Backs

    void SetFrameBufferSizeCallBack(GLFWframebuffersizefun fun) const; 
    void SetKeyCallBack(GLFWkeyfun fun) const; 
    void SetCursorPostionCallBack(GLFWcursorposfun fun) const;
    void SetScrollCallBack(GLFWscrollfun fun) const;

private:

    GLFWwindow* m_Window;
    unsigned int m_Width;
    unsigned int m_Height;
    std::string  m_Title;


};