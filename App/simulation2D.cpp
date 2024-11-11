#include "simulation2D.hpp"

#include "Pulsar.hpp"

//Shader code paths
#define CIRCLE_SHADER "/home/marek/Dev/Projects/pulsarEngine/res/shaders/circle.shader"
#define LINE_SHADER "/home/marek/Dev/Projects/pulsarEngine/res/shaders/line.shader"

//Window resolution
static unsigned int Width = 1600;
static unsigned int Height = 900;

static void FrameBufferCallBack(GLFWwindow* window, int width, int height){
    
    glViewport(0, 0, width, height);
    Width = width;
    Height = height;  

}


void Simulation2D::initialize(){

        Log::Init();
        FPSTimer::Init();
        System::Init();

}

void Simulation2D::run(){

        const Window* window = System::GetWindow();
        const Renderer* renderer = System::GetRenderer();

        //Define GLFW callbacks for input
        window->SetFrameBufferSizeCallBack(FrameBufferCallBack);

        //Window option
        window->SetVsync(false);

        System::InitUI();
        const Gui* gui = System::GetGui();
        float x0 = float(Width) / 2;
        float y0 = float(Height) * 0.75;

        float l1 = 200.0f;
        float thetha1 = glm::radians(45.0f);

        float l2 = 200.0f;
        float thetha2 = glm::radians(30.0f);

        float x1 = x0 + ( l1 * sinf(thetha1));
        float y1 = y0 - ( l1 * cosf(thetha1));

        float x2 = x1 + ( l2 * sinf(thetha2));
        float y2 = y1 - ( l2 * cosf(thetha2));

        float radius1 = 25.0f;
        float radius2 = 25.0f;
        int segments = 100.0;


        float line1[] = { 
                x0, y0, 0.0f,
                x1, y1, 0.0f 
        };

        float line2[] = { 
                x1, y1, 0.0f,
                x2, y2, 0.0f 
        };

        VertexArray line1VAO;
        VertexBuffer line1VBO(line1, 6 * sizeof(float));
        VertexBufferLayout layout1;
        layout1.Push<float>(3);  //positions
        line1VAO.AddBuffer(line1VBO, layout1);
        line1VAO.UnBind();

        VertexArray line2VAO;
        VertexBuffer line2VBO(line2, 6 * sizeof(float));
        VertexBufferLayout layout2;
        layout2.Push<float>(3);  //positions
        line2VAO.AddBuffer(line2VBO, layout2);
        line2VAO.UnBind();

        Shader lineShader(LINE_SHADER);

        Circle circle1(x1, y1, radius1, segments);
        
        Circle circle2(x2, y2, radius2, segments);

        Mesh circleMesh1(circle1.getVerticesArrayData(), circle1.getVerticesArraySize());
        Mesh circleMesh2(circle2.getVerticesArrayData(), circle2.getVerticesArraySize());

        Shader circleShader(CIRCLE_SHADER);

        glm::mat4 modelCircle1;
        glm::mat4 modelCircle2;

        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::mat4(1.0f);
        glm::mat4 mvp;

        while (!window->ShouldWindowClose()){

        /*
            START MEASURING APP FRAMERATE
        */
        FPSTimer::GetTimer()->StartFrame();


        //Event handler - in the future
        window->onEvents();

        renderer->BeginRender();

       

            /* Calculations*/
            thetha1 += glm::radians(0.1f);
            thetha2 -= glm::radians(0.1f);
            x1 = x0 + ( l1 * sinf(thetha1));
            y1 = y0 - ( l1 * cosf(thetha1));

            x2 = x1 + ( l2 * sinf(thetha2));
            y2 = y1 - ( l2 * cosf(thetha2));

            float lineData[6] = { x0, y0, 0.0f, x1, y1, 0.0f };  
            float lineData2[6] = { x1, y1, 0.0f, x2, y2, 0.0f };  

            line1VBO.UpdateData(lineData, 6 * sizeof(float));
            line2VBO.UpdateData(lineData2, 6 * sizeof(float));

            circle1.generatePoints(x1, y1, radius1, segments);
            circle2.generatePoints(x2, y2, radius2, segments);
        

            circleMesh1.UpdateData(circle1.getVerticesArrayData(), circle1.getVerticesArraySize());
            circleMesh2.UpdateData(circle2.getVerticesArrayData(), circle2.getVerticesArraySize());


            /* MODEL MATRIX CIRCLE 1 */
            modelCircle1 = circle1.getModelMatrix();
        
            /* MODEL MATRIX CIRCLE 2 */
            modelCircle2 = circle2.getModelMatrix();

            /* VIEW MATRIX */
            view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,-0.5f));

            /* PROJECTION MATRIX */
            proj = glm::ortho(0.0f, (float)Width, 0.0f, (float)Height, -1.0f, 1.0f);


            circleShader.Bind();

            /* RENDER CIRCLE 1*/
            mvp = proj * view * modelCircle1;
            circleShader.SetUniformMat4f("u_mvp", mvp);
            renderer->RenderCircle(circleMesh1,circleShader);

            /* RENDER LINE 1 */
            line1VAO.Bind();
            lineShader.Bind();
            lineShader.SetUniformMat4f("u_mvp",mvp);
            glLineWidth(2.5f);
            glDrawArrays(GL_LINES, 0, 2);

            /* RENDER CIRCLE 2*/

            mvp = proj * view * modelCircle2;
            circleShader.SetUniformMat4f("u_mvp", mvp);
            renderer->RenderCircle(circleMesh2,circleShader);

            /* RENDER LINE 2 */

            line2VAO.Bind();
            lineShader.Bind();
            lineShader.SetUniformMat4f("u_mvp",mvp);
            glLineWidth(2.5f);
            glDrawArrays(GL_LINES, 0, 2);

       
        //Customizing gui...
        gui->OnBegin();


        

            ImGui::SetNextWindowPos(ImVec2(0.0f,0.0f));
            ImGui::Begin("Debug");

                    ImGui::Text("Window control");
                    ImGui::Text("Resolution: %d x %d",Width, Height);
                    ImGui::Separator();

                    ImGui::PushID(0);
                    ImGui::Text("Double pendulum parameters");
                    ImGui::SliderFloat("Length 1", &l1, 0.0f , 300.0f);
                    ImGui::SliderFloat("Length 2", &l2, 0.0f , 300.0f);
                    ImGui::SliderFloat("Thetha 1 (radians)", &thetha1, 0.0f , 2 * M_PI);
                    ImGui::SliderFloat("Thetha 2 (radians)", &thetha2, 0.0f , 2 * M_PI);
                   

                    ImGui::PopID();
            
            ImGui::End();

        

        
        gui->OnEnd();
        
        window->onUpdate();

        /*
            STOP MEASURING APP FRAMERATE
        */

        FPSTimer::GetTimer()->UpdateFPS();
      
    }


}  

void Simulation2D::shutdown(){

    System::ShutDown();

}