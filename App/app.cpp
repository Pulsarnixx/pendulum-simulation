#include "Pulsar.hpp"


//Shader code paths
#define GRID_SHADER "/home/marek/Dev/Projects/pulsarEngine/res/shaders/grid.shader"
#define PLATFORM_SHADER "/home/marek/Dev/Projects/pulsarEngine/res/shaders/platform.shader"
#define SPHERE_SHADER "/home/marek/Dev/Projects/pulsarEngine/res/shaders/sphere.shader"
#define LINE_SHADER "/home/marek/Dev/Projects/pulsarEngine/res/shaders/line.shader"


//Texture paths
#define PLATFORM_TEXTURE  "/home/marek/Dev/Projects/pulsarEngine/res/images/concrete.jpg"
#define SPHERE_TEXTURE "/home/marek/Dev/Projects/pulsarEngine/res/images/ball_texture.jpg"

static Camera camera;
static unsigned int Width = 1600;
static unsigned int Height = 900;
bool firstMouse = true;
static float lastX = static_cast<float>(Width) / 2;
static float lastY = static_cast<float>(Height) / 2;

/*
    GLFW CALL BACKS FUNTTIONS
*/
void FrameBufferCallBack(GLFWwindow* window, int width, int height){
    
    #ifdef DEBUG
        std::string s = "[FrameBuffer] resolution: " + std::to_string(width) + " x " + std::to_string(height);
        PX_CORE_TRACE(s);
    #endif
 
    glViewport(0, 0, width, height);
    Width = width;
    Height = height;  
}

void KeyInputCallBack(GLFWwindow* window, int key, int scancode, int action, int mods){

    float cameraStep = 2.5f * (1.0f / 60.0f);

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){

        #ifdef DEBUG
            PX_CORE_TRACE("[Keyboard] pressed: ESCAPE");
        #endif
        
        glfwSetWindowShouldClose(window,GLFW_TRUE);
    }

    if (key == GLFW_KEY_W && action == GLFW_REPEAT){
        #ifdef DEBUG
             PX_CORE_TRACE("[Keyboard] pressed: W");
        #endif
        camera.s_position += cameraStep * camera.s_front;
    }
    if (key == GLFW_KEY_S && action == GLFW_REPEAT){
        #ifdef DEBUG
             PX_CORE_TRACE("[Keyboard] pressed: S");
        #endif
        camera.s_position -= cameraStep * camera.s_front;
    }
    if (key == GLFW_KEY_D && action == GLFW_REPEAT){
         #ifdef DEBUG
             PX_CORE_TRACE("[Keyboard] pressed: D");
        #endif
        camera.s_position += cameraStep * glm::normalize(glm::cross(camera.s_front,camera.s_up));
    }
    if (key == GLFW_KEY_A && action == GLFW_REPEAT){
        #ifdef DEBUG
             PX_CORE_TRACE("[Keyboard] pressed: A");
        #endif
        camera.s_position -= cameraStep * glm::normalize(glm::cross(camera.s_front,camera.s_up));
    }

      
 
}

void MouseCallBack(GLFWwindow* window, double xposIn, double yposIn){

    #ifdef DEBUG
        std::string s = "[Mouse] position: " + std::to_string(xposIn) + " " + std::to_string(yposIn);
        PX_CORE_TRACE(s);
    #endif

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera.yaw += xoffset;
    camera.pitch += yoffset;

    camera.yaw   += xoffset;
    camera.pitch += yoffset;

    if(camera.pitch > 89.0f)
        camera.pitch = 89.0f;
    if(camera.pitch < -89.0f)
        camera.pitch = -89.0f;


    glm::vec3 direction;
    direction.x = cos(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
    direction.y = sin(glm::radians(camera.pitch));
    direction.z = sin(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
    camera.s_front = glm::normalize(direction);
}  

void ScrollCallBack(GLFWwindow* window, double xpos2, double ypos2){

    #ifdef DEBUG
        std::string s = "[Mouse Scroll] values: " + std::to_string(xpos2) + " " + std::to_string(ypos2);
        PX_CORE_TRACE(s);
    #endif

    camera.fov -= (float)ypos2;
    if (camera.fov < 1.0f)
        camera.fov = 1.0f;
    if (camera.fov > 90.0f)
        camera.fov = 90.0f; 

}  


int main(){


    /*
    =================================================
                        SYSTEM 
    =================================================        
    */

    //Pulsar core
    Log::Init();
    GlobalTimer::Init();
    FPSTimer::Init();
    ScopedTimer::Init();

    //Pulsar graphics
    System::Init();

    const Window* window = System::GetWindow();
    const Renderer* renderer = System::GetRenderer();

    //Define GLFW callbacks for input
    window->SetFrameBufferSizeCallBack(FrameBufferCallBack);
    window->SetKeyCallBack(KeyInputCallBack);
    // window->SetCursorPostionCallBack(MouseCallBack);
    window->SetScrollCallBack(ScrollCallBack);

    //Window option
    window->SetVsync(false);

    System::InitUI();
    const Gui* gui = System::GetGui();

    //Camera initial values
    camera.s_position = glm::vec3(0.0f, 3.0f, 8.0f);
    camera.fov = 45.0f;
    camera.pitch = -20.0f;
    camera.yaw = 90.0f;
    /*
    =================================================
                PHYSICAL INITIAL VALUES
    =================================================        
    */
    float L1 =  2.0f;
    float L2 =  2.0f;
    
    float radius1 = 0.25f;
    float radius2 = 0.25f;
    // float theta1 = glm::radians(45.0f);  
    // float theta2 = glm::radians(30.0f);   
    // float omega1 = 0.0f;   
    // float omega2 = 0.0f;   
    // float gravity = 9.8f;  

    /*
    =================================================
                GRAPHICS SHAPE - GRID 
    =================================================        
    */
        Shader gridShader(GRID_SHADER);
    /*
    =================================================
              GRAPHICS SHAPE - PLATFORM 
    =================================================        
    */

        Cube platform;
        
        Mesh platformMesh( platform.getVerticesArrayData(), platform.getVerticesArraySize(),
                           platform.getIndicatesArrayData(), platform.getIndicatesArraySize()
                    );

        Shader platformShader(PLATFORM_SHADER);

        platformShader.Bind();
        platformShader.SetUniform4f("u_color", 0.47f, 0.47f, 0.47f, 1.0f);

        platform.setPosition(0.0f, 6.0f, 0.0f);
        platform.setScale(6.0f, 0.3f, 1.0f);
   
    /*
    =================================================
            GRAPHICS SHAPE - SPHERES 
    =================================================        
    */
        Sphere sphere(radius1, 36, 18);
        Sphere sphere2(radius2, 36, 18);
        
        //Both spheres are identical, so only one Mesh is needed.
        Mesh sphereMesh( sphere.getVerticesArrayData(), sphere.getVerticesArraySize(),
                         sphere.getIndicatesArrayData(), sphere.getIndicatesArraySize()
                    );

        Shader shaderSphere(SPHERE_SHADER);

        Texture2D sphereTexture(SPHERE_TEXTURE);
        sphereTexture.Bind(); //choose slot. For Bind() default is  '0'

        shaderSphere.SetUniform1i("u_texture", 0); // Tell GPU witch texture slot should be use. 


    /*
    =================================================
            GRAPHICS SHAPE - LINES  
    =================================================        
    */
        glm::vec3 platformPoint = platform.getPosition();
        glm::vec3 sphere1Point = sphere.getPosition();
        glm::vec3 sphere2Point = sphere2.getPosition();

        float lineVerticies1[] = { 
            platformPoint.x, platformPoint.y, platformPoint.z, 
            sphere1Point.x, sphere1Point.y, sphere1Point.z
        };

        float lineVerticies2[] = { 
            sphere1Point.x, sphere1Point.y, sphere1Point.z, 
            sphere2Point.x, sphere2Point.y, sphere2Point.z
        };

        // VertexArray lineVAO;
        // VertexBuffer lineVBO(lineVerticies, 6 * sizeof(float));
        // VertexBufferLayout layout;
        // layout.Push<float>(3);  //positions
        // lineVAO.AddBuffer(lineVBO, layout);
        // lineVAO.UnBind();
        // Shader lineShader(LINE_SHADER);

    /* MVP Matrix buffers */
    glm::mat4 modelSphere1;
    glm::mat4 modelSphere2;
    glm::mat4 modelPlatform = platform.getModelMatrix();
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);
    glm::mat4 mvp  = glm::mat4(1.0f);

    /* ImGUI entry values for changing sphere parameters */
    float transBuffer[3] = { 0.0f, 4.0f, 0.0f }; 
    float transBuffer2[3] = { 0.0f, 2.0f, 0.0f};

    float scaleBuffer = 1.0f;
    float scaleBuffer2 = 1.0f;

    float rotBuffer[3] = {};
    float rotBuffer2[3] = {};


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
        
       
        /* MODEL MATRIX SPHERE 1 */
        
        sphere.setPosition(transBuffer[0], transBuffer[1], transBuffer[2]);
        sphere.setScale(scaleBuffer);
        sphere.setRotation(rotBuffer[0], rotBuffer[1], rotBuffer[2]);

        modelSphere1 = sphere.getModelMatrix();

        /* MODEL MATRIX SPHERE 2 */

        sphere2.setPosition(transBuffer2[0], transBuffer2[1], transBuffer2[2]);
        sphere2.setScale(scaleBuffer2);
        sphere2.setRotation(rotBuffer2[0], rotBuffer2[1], rotBuffer2[2]);
        
        modelSphere2 = sphere2.getModelMatrix();


        /* VIEW MATRIX */
        view = glm::lookAt(camera.s_position,               //position
                                    camera.s_position +  camera.s_front,//target
                                    camera.s_up                //up
                                    );

        /* PROJECTION MATRIX */
        proj = glm::perspective(glm::radians(camera.fov), (float)Width / (float)Height, 0.1f, 1000.0f);
        
        /*
            GRID RENDERING
        */
        gridShader.Bind();

            gridShader.SetUniformMat4f("u_view", view);
            gridShader.SetUniformMat4f("u_proj", proj);
            renderer->RenderGrid(gridShader);

        /*
            PLATFORM RENDERING
        */
        platformShader.Bind();

            mvp = proj * view * modelPlatform;
            shaderSphere.SetUniformMat4f("u_mvp",mvp);
            renderer->RenderMesh(platformMesh, platformShader);

        /*
            SPHERES RENDERING
        */


        shaderSphere.Bind();
        sphereTexture.Bind();

            //Sphere 1
            mvp = proj * view * modelSphere1;
            shaderSphere.SetUniformMat4f("u_mvp",mvp);
            renderer->RenderMesh(sphereMesh,shaderSphere);

            //Sphere 2 
            mvp = proj * view * modelSphere2;
            shaderSphere.SetUniformMat4f("u_mvp",mvp);
            renderer->RenderMesh(sphereMesh, shaderSphere);

        /*
            LINES RENDERING
        */
        // lineVAO.Bind();
        // lineShader.Bind();
        // lineShader.SetUniformMat4f("u_mvp",mvp);
        // glLineWidth(1.5f);
        // glDrawArrays(GL_LINES, 0, 2);
        // glLineWidth(1.0f);


        gui->OnBegin();

            //Customizing gui...

            {
                ImGui::SetNextWindowPos(ImVec2(0.0f,0.0f));
                ImGui::Begin("Debug");

                    ImGui::Text("Window control");
                    ImGui::Text("Resolution: %d x %d",window->GetWidth(), window->GetHeight());
                    ImGui::Separator();

                    ImGui::PushID(0);
                    ImGui::Text("Sphere 1");
                    ImGui::SliderFloat3("Translation",transBuffer,-10.0f,10.0f);
                    ImGui::SliderFloat("Scale",&scaleBuffer,0.0f,10.0f);
                    ImGui::SliderFloat3("Rotation",rotBuffer,-360.0f,360.0f);

                    ImGui::Text("Actual Position: X: %f, Y: %f, Z: %f",transBuffer[0] ,transBuffer[1] ,transBuffer[2] );
                   
                    if(ImGui::Button("Reset")) {
                        std::fill(std::begin(transBuffer), std::end(transBuffer), 0.0f);
                        scaleBuffer = 1.0f;
                        std::fill(std::begin(rotBuffer), std::end(rotBuffer), 0.0f);
                    }

                    ImGui::PopID();
                    ImGui::Separator();

                    ImGui::PushID(1);
                    ImGui::Text("Sphere 2");
                    ImGui::SliderFloat3("Translation",transBuffer2,-10.0f,10.0f);
                    ImGui::SliderFloat("Scale",&scaleBuffer2,0.0f,10.0f);
                    ImGui::SliderFloat3("Rotation",rotBuffer2,-360.0f,360.0f);

                    ImGui::Text("Actual Position: X: %f, Y: %f, Z: %f",transBuffer2[0] ,transBuffer2[1] ,transBuffer2[2] );

                    if(ImGui::Button("Reset")) {
                        std::fill(std::begin(transBuffer2), std::end(transBuffer2), 0.0f);
                        scaleBuffer2 = 1.0f;
                        std::fill(std::begin(rotBuffer2), std::end(rotBuffer2), 0.0f);
                    }

                    ImGui::PopID();

                    ImGui::PushID(2);
                    ImGui::Text("Camera");
                    ImGui::Text("Position:  X: %f, Y: %f, Z: %f",camera.s_position.x ,camera.s_position.y ,camera.s_position.z );
                    ImGui::Text("Angle: Pitch: %f, Yaw: %f , Fov: %f",camera.pitch,camera.yaw,camera.fov);
                    ImGui::Separator();
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