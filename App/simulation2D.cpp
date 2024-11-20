#include "simulation2D.hpp"
#include "pendulum.hpp"

#include "Pulsar.hpp"
#include "iostream"

//Shader code paths
#define CIRCLE_SHADER "/home/marek/Dev/Projects/pulsarEngine/res/shaders/circle.shader"
#define LINE_SHADER "/home/marek/Dev/Projects/pulsarEngine/res/shaders/line.shader"
#define TRAIL_SHADER "/home/marek/Dev/Projects/pulsarEngine/res/shaders/trail.shader"

//Window resolution
static unsigned int Width = 1600;
static unsigned int Height = 900;

static void FrameBufferCallBack(GLFWwindow* window, int width, int height){
    
    glViewport(0, 0, width, height);
    Width = width;
    Height = height;  

}

//Starting point
static double x_0 = double(Width) / 2;
static double y_0 = double(Height) * 0.75;


void updateTrailData(float x, float y, float* trailPosition, int trailElements){
    
    for (int i = 0; i < trailElements - 1; ++i) {
        trailPosition[(trailElements - 1 - i) * 2]     = trailPosition[(trailElements - 2 - i) * 2];     // x
        trailPosition[(trailElements - 1 - i) * 2 + 1] = trailPosition[(trailElements - 2 - i) * 2 + 1]; // y
    }

    trailPosition[0] = x;
    trailPosition[1] = y;
}


void Simulation2D::initialize(){

        Log::Init();
        FPSTimer::Init();
        System::Init();

}

void Simulation2D::run(){

    /*
    ==============================================================    
                    SYSTEM CONFIGURATION 
    ==============================================================    
    */

        const Window* window = System::GetWindow();
        const Renderer* renderer = System::GetRenderer();

        //Define GLFW callbacks for input
        window->SetFrameBufferSizeCallBack(FrameBufferCallBack);

        //Window option
        window->SetVsync(true);

        System::InitUI();
        const Gui* gui = System::GetGui();

        //Imgui combo 1
        const char* pendulumTypes[] = { "Single Pendulum", "Double Pendulum"};
        int pendulumTypesIndex = 0;

        const char* pendulumNumericEq[] = { "Aprox", "Euler", "RK2", "RK4"};
        int pendulumNumericEqIndex = 0;

        bool isSimulationRunning = false;

    /*
    ==============================================================    
                    DATA CONFIGURATION 
    ==============================================================    
    */
        int segments = 100;

        float scaleX = Width / 16.0; 
        float scaleY = Height / 9.0;

        //Physics origin
        float x0 = 0.0f, y0 = 0.0f;

        //Graphics origin
        float xg = (x0 * scaleX) + (Width/2);
        float yg = (Height * 0.75) - (y0 * scaleY);

        //Physical object
        SinglePendulum single(x0, y0, 0.1, 5.0, 45.0, 0.0);

        //Graphicals object
        Line singleLine(xg, yg, 0.0f, xg + (single.x * scaleX), yg + (single.y * scaleY), 0.0f);
        Circle singleCircle(xg + (single.x * scaleX), yg + (single.y * scaleY), 25.0f, segments);
        
        //Physical object
        DoublePendulum pendulum(x0, y0, 0.1, 0.2, 3.0, 3.0, 180.0, 180.0, 0.0, 0.0);

        //Graphicals objects      
        Line doubleLine1(xg, yg, 0.0f, xg + (pendulum.x1 * scaleX), yg + (pendulum.y1 * scaleY), 0.0f);
        Line doubleLine2(xg + (pendulum.x1 * scaleX), yg + (pendulum.y1 * scaleY), 0.0f, xg + (pendulum.x2 * scaleX), yg + (pendulum.y2 * scaleY), 0.0f);
        Circle circle1(xg + (pendulum.x1 * scaleX), yg + (pendulum.y1 * scaleY), 25.0f, segments);
        Circle circle2(xg + (pendulum.x2 * scaleX), yg + (pendulum.y2 * scaleY), 25.0f, segments);
        
    /*
    ==============================================================    
                OPENGL DATA CONFIGURATION 
    ==============================================================    
    */

        
        //Rod for single pendulum
        Mesh singleLineMesh(singleLine.getVerticesArrayData(), singleLine.getVerticesArraySize());

        //Rods for double pendulum
        Mesh doubleLine1Mesh(doubleLine1.getVerticesArrayData(), doubleLine1.getVerticesArraySize());
        Mesh doubleLine2Mesh(doubleLine2.getVerticesArrayData(), doubleLine2.getVerticesArraySize());
  
        //Universal shader for lines
        Shader lineShader(LINE_SHADER);

        //Circle for single pendulum
        Mesh singleCircleMesh(singleCircle.getVerticesArrayData(), singleCircle.getVerticesArraySize());

        //Circles for double pendulum
        Mesh circleMesh1(circle1.getVerticesArrayData(), circle1.getVerticesArraySize());
        Mesh circleMesh2(circle2.getVerticesArrayData(), circle2.getVerticesArraySize());

        //Universal shader for circles
        Shader circleShader(CIRCLE_SHADER);

        //Trail for single pendulum
        float trailPositions[10000 * 2] = {0.0f}; 
        VertexArray trailVAO;
        VertexBuffer trailPositionsVBO(trailPositions, 10000 * 2 * sizeof(float));
        VertexBufferLayout trailPositionsLayout;
        trailPositionsLayout.Push<float>(2);
        trailVAO.AddBuffer(trailPositionsVBO, trailPositionsLayout);

        float doubleTrailPostions[10000 * 2] = {0.0f}; 
        VertexArray doubleTrailPostionsVAO;
        VertexBuffer doubleTrailPostionsVBO(trailPositions, 10000 * 2 * sizeof(float));
        VertexBufferLayout doubleTrailPostionsLayout;
        doubleTrailPostionsLayout.Push<float>(2);
        doubleTrailPostionsVAO.AddBuffer(doubleTrailPostionsVBO, doubleTrailPostionsLayout);


        float doubleTrailPostions2[10000 * 2] = {0.0f}; 
        VertexArray doubleTrailPostionsVAO2;
        VertexBuffer doubleTrailPostionsVBO2(trailPositions, 10000 * 2 * sizeof(float));
        VertexBufferLayout doubleTrailPostionsLayout2;
        doubleTrailPostionsLayout2.Push<float>(2);
        doubleTrailPostionsVAO2.AddBuffer(doubleTrailPostionsVBO2, doubleTrailPostionsLayout2);

        Shader trailShader(TRAIL_SHADER);

        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,-0.5f));
        glm::mat4 proj = glm::ortho(0.0f, (float)Width, 0.0f, (float)Height, -1.0f, 1.0f);
        glm::mat4 mvp = proj * view * glm::mat4(1.0f);

        //Set uniforms for lines once
        lineShader.Bind();
        lineShader.SetUniformMat4f("u_mvp",mvp);

        trailShader.Bind();
        trailShader.SetUniformMat4f("u_mvp",mvp);
        trailShader.SetUniform4f("u_color", 1.0f, 0.784f, 0.341f, 1.0f);

        circleShader.Bind();
        circleShader.SetUniformMat4f("u_mvp",mvp);
        circleShader.UnBind();
        

    /*
    ==============================================================    
                        MAIN LOOP
    ==============================================================    
    */

    while (!window->ShouldWindowClose()){
        
        FPSTimer::GetTimer()->StartFrame();



        //Event handler - in the future
        window->onEvents();

        /*
            ==============================================================    
                        PHYSICS CALCULATION 
            ==============================================================    
        */

        if(isSimulationRunning == true){


            //Single Pendulum
            if(pendulumTypesIndex == 0){

                switch (pendulumNumericEqIndex)
                {
                    case 0: printf("Simulation - Approx\n"); SimulatePendulumApprox(single); break;
                    case 1: printf("Simulation - Euler\n"); SimulatePendulumEuler(single); break;
                    case 2: printf("Simulation - RK2\n"); SimulatePendulumRK2(single); break;
                    case 3: printf("Simulation - RK4\n"); SimulatePendulumRK4(single); break;
                    default: printf("Simulation - None\n"); break;
                }
               

                /*
                ==============================================================    
                                GRAPHICS ADJUSTMENTS
                ==============================================================    
                */
                singleLine.setPositions( xg, yg, 0.0f, xg + (single.x * scaleX), yg + (single.y * scaleY), 0.0f);
                singleLineMesh.UpdateData(singleLine.getVerticesArrayData(), singleLine.getVerticesArraySize());

                singleCircle.generatePoints(xg + (single.x * scaleX), yg + (single.y * scaleY), 25.0f, segments);
                singleCircleMesh.UpdateData(singleCircle.getVerticesArrayData(), singleCircle.getVerticesArraySize());


                updateTrailData(xg + (single.x * scaleX), yg + (single.y * scaleY), trailPositions, 10000);
                trailPositionsVBO.UpdateData(trailPositions, 10000 * 2 * sizeof(float));
            }

            //Double Pendulum
            if(pendulumTypesIndex == 1){
                
                SimulatePendulumEuler(pendulum);

                /*
                ==============================================================    
                                GRAPHICS ADJUSTMENTS
                ==============================================================    
                */


                doubleLine1.setPositions(xg, yg, 0.0f, xg + (pendulum.x1 * scaleX), yg + (pendulum.y1 * scaleY), 0.0f);
                doubleLine1Mesh.UpdateData(doubleLine1.getVerticesArrayData(), doubleLine1.getVerticesArraySize());


                doubleLine2.setPositions(xg + (pendulum.x1 * scaleX), yg + (pendulum.y1 * scaleY), 0.0f, xg + (pendulum.x2 * scaleX), yg + (pendulum.y2 * scaleY), 0.0f);
                doubleLine2Mesh.UpdateData(doubleLine2.getVerticesArrayData(), doubleLine2.getVerticesArraySize());

                circle1.generatePoints(xg + (pendulum.x1 * scaleX), yg + (pendulum.y1 * scaleY), 25.0f, segments);
                circle2.generatePoints(xg + (pendulum.x2 * scaleX), yg + (pendulum.y2 * scaleY), 25.0f, segments);
            

                circleMesh1.UpdateData(circle1.getVerticesArrayData(), circle1.getVerticesArraySize());
                circleMesh2.UpdateData(circle2.getVerticesArrayData(), circle2.getVerticesArraySize());

                updateTrailData(xg + (pendulum.x1 * scaleX), yg + (pendulum.y1 * scaleY), doubleTrailPostions, 10000);
                doubleTrailPostionsVBO.UpdateData(doubleTrailPostions, 10000 * 2 * sizeof(float));

                updateTrailData(xg + (pendulum.x2 * scaleX), yg + (pendulum.y2 * scaleY), doubleTrailPostions2, 10000);
                doubleTrailPostionsVBO2.UpdateData(doubleTrailPostions2, 10000 * 2 * sizeof(float));

            }

        }


        /*
        ==============================================================    
                            RENDERING
        ==============================================================    
        */

        renderer->BeginRender();

        //Single Pendulum
        if(pendulumTypesIndex == 0){

            /* RENDER TRAILS*/
            trailVAO.Bind();
            trailShader.Bind();
            glDrawArrays(GL_POINTS, 0, 10000);


            /* RENDER LINE*/
            renderer->RenderLine(singleLineMesh, lineShader);
            

            /* RENDER CIRCLE */
            renderer->RenderCircle(singleCircleMesh,circleShader);

        }
        
        //Double Pendulum
        if(pendulumTypesIndex == 1){

            /* RENDER TRAILS*/
            trailShader.Bind();
            doubleTrailPostionsVAO.Bind();
            trailShader.SetUniform4f("u_color", 1.0f, 0.784f, 0.341f, 1.0f);
            glDrawArrays(GL_POINTS, 0, 10000);
            doubleTrailPostionsVAO2.Bind();
            trailShader.SetUniform4f("u_color", 1.0f, 0.902f, 0.502f, 1.0f);
            glDrawArrays(GL_POINTS, 0, 10000);

            /* RENDER LINES */
            renderer->RenderLine(doubleLine1Mesh, lineShader);
            renderer->RenderLine(doubleLine2Mesh, lineShader);

            /* RENDER CIRCLES*/
            renderer->RenderCircle(circleMesh1,circleShader);
            renderer->RenderCircle(circleMesh2,circleShader);

        }


        /*
        ==============================================================    
                            USER UI 
        ==============================================================    
        */
            
        gui->OnBegin();
            ImGui::SetNextWindowPos(ImVec2(0.0f,0.0f));
            ImGui::Begin("Panel");

            if (ImGui::Combo("Choose pendulum", &pendulumTypesIndex, pendulumTypes, IM_ARRAYSIZE(pendulumTypes))) {
                printf("Selected: %s\n", pendulumTypes[pendulumTypesIndex]);
            }

            //Single pendulum
            if(pendulumTypesIndex == 0){

                if (ImGui::Combo("Numerical method", &pendulumNumericEqIndex, pendulumNumericEq, IM_ARRAYSIZE(pendulumNumericEq))) {
                    printf("Selected: %s\n", pendulumNumericEq[pendulumNumericEqIndex]);
                }

                ImGui::PushID(0);
                // ImGui::SliderFloat("Rod length", &single.l, 0.0f , 300.0f);
                // ImGui::SliderFloat("Thetha (radians)", &single.theta, 0.0f , 2 * M_PI);

                ImGui::Text("Actual data");
                ImGui::BulletText("Rod length: %f", single.l);
                ImGui::BulletText("Thetha (radians): %f", single.theta);
                ImGui::BulletText("Position (x,y): %f, %f", single.x , single.y);
                ImGui::BulletText("Angular velocity: %f", single.thetadot);

                ImGui::PopID();
            }

            //Double Pendulum
            if(pendulumTypesIndex == 1){
                ImGui::PushID(0);

                ImGui::Text("Change parameters");
                double minl1 = 0.0;
                double maxl1 = 5.0;
                ImGui::SliderScalar("l1", ImGuiDataType_Double, &pendulum.l1, &minl1, &maxl1, "%.2f");
                // ImGui::SliderFloat("Rod 1 length", &pendulum.l1, 0.0f , 300.0f);
                // ImGui::SliderFloat("Rod 2 length", &pendulum.l2, 0.0f , 300.0f);
                // ImGui::SliderFloat("Thetha 1 (radians)", &pendulum.theta1, 0.0f , 2 * M_PI);
                // ImGui::SliderFloat("Thetha 2 (radians)", &pendulum.theta2, 0.0f , 2 * M_PI);


                ImGui::Text("Actual data");
                ImGui::BulletText("Rod length 1: %f", pendulum.l1);
                ImGui::BulletText("Rod length 2: %f", pendulum.l2);
                ImGui::BulletText("Thetha 1 (radians): %f", pendulum.theta1);
                ImGui::BulletText("Thetha 2 (radians): %f", pendulum.theta2);
                ImGui::BulletText("Position 1 (x,y): %f, %f", pendulum.x1 , pendulum.y1);
                ImGui::BulletText("Position 2 (x,y): %f, %f", pendulum.x2  , pendulum.y2);
                ImGui::BulletText("Angular velocity 1 : %f", pendulum.thetadot1);
                ImGui::BulletText("Angular velocity 2 : %f", pendulum.thetadot2);

               

                ImGui::PopID();
            }

            if (ImGui::Button("Start")){ isSimulationRunning = true; }
            ImGui::SameLine();
            if (ImGui::Button("Stop")){ isSimulationRunning = false; }
            ImGui::SameLine();
            if (ImGui::Button("Reset")){

                if(pendulumTypesIndex == 0)
                    ResetPendulum(single);
                if(pendulumTypesIndex == 1)
                    ResetPendulum(pendulum);
            }

            ImGui::End();
        gui->OnEnd();
        
        window->onUpdate();
        FPSTimer::GetTimer()->UpdateFPS();
      
    }


}  

void Simulation2D::shutdown(){

    System::ShutDown();

}