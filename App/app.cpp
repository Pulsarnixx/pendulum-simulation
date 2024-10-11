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
    texture1.Bind(); //choose slot


    unsigned int frames = 0;
    std::chrono::time_point<std::chrono::steady_clock> startTime;
    std::chrono::time_point<std::chrono::steady_clock> endTime;
    std::chrono::duration<double> elapsedTime(0);


    while (!window->ShouldWindowClose())
    {

        /*
            START MEASURING APP FRAMERATE
        */
        startTime = std::chrono::steady_clock::now();
        frames++;

     


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

        //Force GPU to end rendering task from SwapBuffer before measuring performance
       

        // PX_CORE_TIMER_GL_MILI("Render()", renderer->Render(););
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

        endTime = std::chrono::steady_clock::now();
        elapsedTime += endTime - startTime;
        
        if(elapsedTime.count() >= 1.0){

            double elapsedMili = elapsedTime.count() * 1000;
            std::string s = "FPS: " + std::to_string(frames) + " | Frame time (avg): " + std::to_string( (elapsedMili / frames)) + " ms";
            PX_CORE_TRACE(s);


            frames = 0;
            elapsedTime = std::chrono::duration<double>(0);
        }
    }

    PX::ShutDown();
    return 0;
}