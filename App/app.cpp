#include "Pulsar.hpp"

#include "glad.h" //Temporary, when everything will be encapsulated - then delete.
#include <iostream>

int main(){

    PX_LOG::Init();
    PX_TIMER::Init();
    
    PX::Init();

    const Window* window = PX::GetWindow();
    const Renderer* renderer = PX::GetRenderer();
    const Gui* gui = PX::GetGui();


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
    std::string file_path = "/home/marek/Dev/Projects/pulsarEngine/res/shaders/shader_prog.txt";
    Shader shaderProgram(file_path);
    shaderProgram.Bind();

    //Bind shaderProgram first
    shaderProgram.SetUniform4f("u_color", 1.0f, 0.984f, 0.0f, 1.0f );

    /*
        TEXTURES
    */
    file_path = "/home/marek/Dev/Projects/pulsarEngine/res/images/hagrid.jpg";
    Texture2D texture1(file_path);
    texture1.Bind();

   
    while (!window->ShouldWindowClose())
    {
        //Event handler - in the future

        // PX_CORE_TIMER_START();

        renderer->BeginRender();
        // PX_CORE_TIMER_STOP_MILI("Rendering");

        //Calculation...

        //Rendering staff...
        vao.Bind();
        ebo.Bind();

        renderer->Render();
        //GUI adjustment
        
        gui->OnBegin();
        /*
            Customizing gui...
        */
        gui->OnEnd();
        
        window->onUpdate();

    }

    PX::ShutDown();
    return 0;
}