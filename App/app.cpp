#include "Pulsar.hpp"


#define EXAMPLE_SHADER "/home/marek/Dev/Projects/pulsarEngine/res/shaders/basic.shader"
#define EXAMPLE_SHADER2 "/home/marek/Dev/Projects/pulsarEngine/res/shaders/sphere.shader"
#define GRID_SHADER "/home/marek/Dev/Projects/pulsarEngine/res/shaders/grid.shader"
#define LINE_SHADER "/home/marek/Dev/Projects/pulsarEngine/res/shaders/line.shader"
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

    Camera camera;

    //Window option
    window->SetVsync(false);


    /*
        Cube primitive with dependecies
    */
        //Data
        Cube cube1;
        
        Mesh cubeMesh(  cube1.GetVerticesArrayData(), cube1.GetVerticesArraySize(),
                        cube1.GetIndicatesArrayData(), cube1.GetIndicatesArraySize()
                    );

        //Shader for cube
        std::string file_path = EXAMPLE_SHADER;
        Shader shaderCube(file_path);

        // //Cube texture
        file_path = EXAMPLE_TEXTURE;
        Texture2D texture1(file_path);
        texture1.Bind(); //choose slot
        shaderCube.SetUniform1i("u_texture", 0); // Tell GPU witch texture slot should be use. For Bind() is deafult = 0

    /*
        Sphere primitive with dependecies
    */
        //Data
        Sphere sphere({0.0f, 1.0f, 0.0f}, 1.0f, 36, 18);
        
        Mesh sphereMesh(sphere.GetVerticesArrayData(), sphere.GetVerticesArraySize(),
                        sphere.GetIndicatesArrayData(), sphere.GetIndicatesArraySize()
                    );

        //Shader for cube
        file_path = EXAMPLE_SHADER2;
        Shader shaderSphere(file_path);


        //Line for sphere 
        Vector3f sphereCenter = sphere.getCenter();
        float sphereRadius = sphere.getRadius();
        float lineLenght = 10.0f;

        float lineVerticies[] = { 
            sphereCenter.x, sphereCenter.y, sphereCenter.z, 
            sphereCenter.x, sphereCenter.y + sphereRadius + lineLenght, sphereCenter.z 
        };

        VertexArray lineVAO;
        VertexBuffer lineVBO(lineVerticies, 6 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(3);  //positions


        lineVAO.AddBuffer(lineVBO, layout);

        lineVAO.UnBind();

        file_path = LINE_SHADER;
        Shader lineShader(file_path);

        // Square grid;
        file_path = GRID_SHADER;
        Shader gridShader(file_path);

   
    //For IMGUI entry
    float transArray[3] = {}; 
    float scaleArray[3] = {1.0f,1.0f,1.0f};
    float rotationArray[3] = {};

    float cameraPosition[3] = {0.0f, 6.0f, 5.0f}; 
    float cameraFront[3] = {0.0f, -1.0f, -1.0f};
    float cameraUp[3] = {0.0f, 1.0f, 0.0f};

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
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f),  glm::radians(rotationArray[0]), glm::vec3(1.0f,0.0f,0.0f));   //X-axis rotation
                  rotation = glm::rotate(rotation,  glm::radians(rotationArray[1]), glm::vec3(0.0f,1.0f,0.0f));           //Y-axis rotation
                  rotation = glm::rotate(rotation, glm::radians(rotationArray[2]), glm::vec3(0.0f,0.0f,1.0f));           //Z-axis rotation

        //Read from right to left. First is scale, then rotation, then translation
        glm::mat4 model = trans * rotation * scale; 

        /* VIEW MATRIX */

        // glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, -5.0f)); 

        //Camera setting
        camera.s_position = glm::vec3(cameraPosition[0], cameraPosition[1], cameraPosition[2]);  
        camera.s_front = glm::vec3(cameraFront[0], cameraFront[1], cameraFront[2]);    
        camera.s_up = glm::vec3(cameraUp[0], cameraUp[1], cameraUp[2]);        
        glm::mat4 view = glm::lookAt(camera.s_position,               //position
                            camera.s_position +  camera.s_front,      //target
                            camera.s_up                               //up
                            );

        /* PROJECTION MATRIX */
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float) DEFAULT_WEIGHT / (float) DEFAULT_HEIGHT, 0.1f, 1000.0f);
        
        glm::mat4 mvp = proj * view * model;


        //Rendering staff...
        gridShader.Bind();
        gridShader.SetUniformMat4f("u_view", view);
        gridShader.SetUniformMat4f("u_proj", proj);
        renderer->RenderGrid(gridShader);

        // shaderCube.Bind();
        // shaderCube.SetUniformMat4f("u_mvp",mvp);
        // renderer->RenderMesh(cubeMesh,shaderCube);

        shaderSphere.Bind();
        shaderSphere.SetUniformMat4f("u_mvp",mvp);
        renderer->RenderMesh(sphereMesh,shaderSphere);

        lineVAO.Bind();
        lineShader.Bind();
        lineShader.SetUniformMat4f("u_mvp",mvp);
        glLineWidth(1.5f); // 5 pikseli
        glDrawArrays(GL_LINES, 0, 2);



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

                    ImGui::PushID(1);
                    ImGui::Text("Camera");
                    ImGui::SliderFloat3("Position",cameraPosition,-10.0f,10.0f);
                    ImGui::SliderFloat3("Front",cameraFront,-10.0f,10.0f);
                    ImGui::SliderFloat3("Up",cameraUp,-10.0f,10.0f);

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