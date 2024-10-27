#include "Pulsar.hpp"

#define EXAMPLE_SHADER "/home/marek/Dev/Projects/pulsarEngine/res/shaders/basic.shader"
#define EXAMPLE_TEXTURE  "/home/marek/Dev/Projects/pulsarEngine/res/images/cegla.jpg"

int main(){

    //Pulsar core
    Log::Init();
    GlobalTimer::Init();
    FPSTimer::Init();
    ScopedTimer::Init();

    //Pulsar graphics
    System::Init();

    const Window* window = System::GetWindow();
    const Renderer* renderer = System::GetRenderer();
    const Gui* gui = System::GetGui();

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


    /*
        TEXTURES
    */
    file_path = EXAMPLE_TEXTURE;
    Texture2D texture1(file_path);
    texture1.Bind(); //choose slot
    shaderProgram.SetUniform1i("u_texture", 0); // Tell GPU witch texture slot should be use. For Bind() is deafult = 0


    /*
        MATH
    */

    //For IMGUI entry
    float transArray[3] = {}; 
    float scaleArray[3] = {1.0f,1.0f,1.0f};
    float rotationArray[3] = {};

    GlobalTimer* timer = GlobalTimer::GetTimer().get();
    timer->Start();

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
        
        /* MODEL MATRIX */
        glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(transArray[0], transArray[1], transArray[2]));
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(scaleArray[0], scaleArray[1], scaleArray[2]));
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), (float)timer->GetElapsedTime() * glm::radians(rotationArray[0]), glm::vec3(1.0f,0.0f,0.0f));   //X-axis rotation
                  rotation = glm::rotate(rotation,(float)timer->GetElapsedTime() * glm::radians(rotationArray[1]), glm::vec3(0.0f,1.0f,0.0f));           //Y-axis rotation
                  rotation = glm::rotate(rotation,(float)timer->GetElapsedTime() * glm::radians(rotationArray[2]), glm::vec3(0.0f,0.0f,1.0f));           //Z-axis rotation

        //Read from right to left. First is scale, then rotation, then translation
        glm::mat4 model = trans * rotation * scale; 
        /* VIEW MATRIX */
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f)); 

        /* PROJECTION MATRIX */
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float) DEFAULT_WEIGHT / (float) DEFAULT_HEIGHT, 0.1f, 100.0f);
        
        glm::mat4 mvp = proj * view * model;

        shaderProgram.SetUniformMat4f("u_mvp", mvp);


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

            //Customizing gui...

            {
                ImGui::SetNextWindowPos(ImVec2(0.0f,0.0f));
                ImGui::Begin("Debug");

                    ImGui::Text("Window control");
                    ImGui::Text("Resolution: %d x %d",DEFAULT_WEIGHT, DEFAULT_HEIGHT);
                    ImGui::Separator();

                    ImGui::PushID(0);
                    ImGui::Text("Model Matrix");
                    ImGui::SliderFloat3("Translation",transArray,-1.0f,1.0f);
                    ImGui::SliderFloat3("Scale",scaleArray,0.0f,10.0f);
                    ImGui::SliderFloat3("Rotation",rotationArray,-360.0f,360.0f);
                   
                    if(ImGui::Button("Reset")) {
                        std::fill(std::begin(transArray), std::end(transArray), 0.0f);
                        std::fill(std::begin(scaleArray), std::end(scaleArray), 1.0f);
                        std::fill(std::begin(rotationArray), std::end(rotationArray), 0.0f);
                    }


                    ImGui::PopID();
                    ImGui::Separator();

                ImGui::End();
            }
        
        gui->OnEnd();
        
        window->onUpdate();

        /*
            STOP MEASURING APP FRAMERATE
        */

        FPSTimer::GetTimer()->UpdateFPS();
      
    }

    System::ShutDown();
    return 0;
}