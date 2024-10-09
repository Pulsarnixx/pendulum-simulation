#include "Pulsar.hpp"

#include "glad.h" //Temporary, when everything will be encapsulated - then delete.

int main(){

    PX_LOG::Init();
    PX_TIMER::Init();
    
    PX::Init();

    const Window* window = PX::GetWindow();
    const Renderer* renderer = PX::GetRenderer();
    const Gui* gui = PX::GetGui();


    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    //Buffers / containers
    VertexArray  vao;
    VertexBuffer vbo(vertices, 3 * 4 * sizeof(float) );
    IndexBuffer  ebo(indices,  3 * 2);

    //Vertex attributes
    VertexBufferLayout layout;
    layout.Push<float>(3);

    //Add everything to one container - vao
    vao.AddBuffer(vbo, layout);

    //Unbind everything (buffers are not needed, vao will be changed in loop)
    vao.UnBind();
    vbo.UnBind();
    //Unbind index buffer only when vao is unbind.
    ebo.UnBind();

    std::string file_path = "/home/marek/Dev/Projects/pulsarEngine/res/shader_prog.txt";
    Shader mainShader(file_path);
    mainShader.Bind();

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