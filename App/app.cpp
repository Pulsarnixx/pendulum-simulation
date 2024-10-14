#include "Pulsar.hpp"

#define EXAMPLE_SHADER "/home/marek/Dev/Projects/pulsarEngine/res/shaders/shader_prog.txt"
#define EXAMPLE_TEXTURE  "/home/marek/Dev/Projects/pulsarEngine/res/images/hagrid.jpg"

int main(){

    //Pulsar core
    PX_LOG::Init();
    GlobalTimer::Init();
    FPSTimer::Init();
    ScopedTimer::Init();

    //Pulsar graphics
    PX::Init();

    const Window* window = PX::GetWindow();
    const Renderer* renderer = PX::GetRenderer();
    const Gui* gui = PX::GetGui();

    //Window option
    window->SetVsync(false);

    class Cube cube1;

    //Buffers / containers
    VertexArray  vao;
    VertexBuffer vbo(cube1.GetVerticesArrayData(), cube1.GetVerticesArraySize() );
    IndexBuffer  ebo(cube1.GetIndicatesArrayData(), cube1.GetIndicatesArraySize());

    //Vertex attributes
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);

    //Add everything to one container - vao
    vao.AddBuffer(vbo, layout);

    //Unbind everything (buffers are not needed, vao will be changed in loop)
    vao.UnBind();
    vbo.UnBind();
    //Unbind index buffer only when vao is unbind.
    ebo.UnBind();

    /*
        SHADERS
    */
    std::string file_path = EXAMPLE_SHADER;
    Shader shaderProgram(file_path);
    shaderProgram.Bind();

    //Bind shaderProgram first
    shaderProgram.SetUniform4f("u_color", 1.0f, 0.984f, 0.0f, 1.0f );

    /*
        TEXTURES
    */
    file_path = EXAMPLE_TEXTURE;
    Texture2D texture1(file_path);
    texture1.Bind(); //choose slot

    while (!window->ShouldWindowClose())
    {

        /*
            START MEASURING APP FRAMERATE
        */
        FPSTimer::GetTimer()->StartFrame();


        //Event handler - in the future
        window->onEvents();

        renderer->BeginRender();

        
        //Calculation...

        //Rendering staff...
        vao.Bind();
        ebo.Bind();

   

        /*
            START MEASURING RENDER FRAME TIME
        */       

        renderer->Render();
        /*
            STOP MEASURING RENDER FRAME TIME
        */  
     
        
        gui->OnBegin();
        /*
            Customizing gui...
        */
        gui->OnEnd();
        
        window->onUpdate();

        /*
            STOP MEASURING APP FRAMERATE
        */

        FPSTimer::GetTimer()->UpdateFPS();
      
    }

    PX::ShutDown();
    return 0;
}