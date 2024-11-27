#include "simulation2D.hpp"
#include "pendulum.hpp"

#include "Pulsar.hpp"
#include "iostream"

//Window resolution
static unsigned int Width = 1600;
static unsigned int Height = 900;

static void FrameBufferCallBack(GLFWwindow* window, int width, int height){
    
    glViewport(0, 0, width, height);
    Width = width;
    Height = height;  

}

void updateTrailData(float x, float y, float* trailPosition, int trailElements){
    
    for (int i = 0; i < trailElements - 1; ++i) {
        trailPosition[(trailElements - 1 - i) * 2]     = trailPosition[(trailElements - 2 - i) * 2];     // x
        trailPosition[(trailElements - 1 - i) * 2 + 1] = trailPosition[(trailElements - 2 - i) * 2 + 1]; // y
    }

    trailPosition[0] = x;
    trailPosition[1] = y;
}

void updatePlotData(double newData, double* dataArray, size_t dataSize){

    for (size_t i = 0; i < dataSize - 1; ++i) {
        dataArray[i] = dataArray[i+1];
    }

    dataArray[dataSize - 1] = newData;

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

        //ImGui parameters for UI
        const char* pendulumTypes[] = { "Single Pendulum", "Double Pendulum"};
        int pendulumTypesIndex = 0;

        const char* pendulumNumericEq[] = { "Approximation", "Euler Method", "Heun's method (Modified Euler Method)", "Runge-Kutta Method (RK4)"};
        int pendulumNumericEqIndex = 0;

        const char* pendulumNumericEq2[] = { "Euler Method", "Heun's method (Modified Euler Method)", "Runge-Kutta Method (RK4)"};
        int pendulumNumericEqIndex2 = 0;

        double degrees = 0.0, degrees2 = 0.0, degrees3 = 0.0;

        bool isSimulationRunning = false;


        //ImPlot parameters for plots

        //Single Pendulum data
        double t_data[1000] = {0.0};

        double theta_data[1000] = {0.0};
        double thetadot_data[1000] = {0.0};
        
        double Ep_data[1000] = {0.0};
        double Ek_data[1000] = {0.0};
        double Ec_data[1000] = {0.0};
        
        //Double Pendulum data
        double t2_data[1000] = {0.0};

        double theta1_data[1000] = {0.0};
        double thetadot1_data[1000] = {0.0};
        double theta2_data[1000] = {0.0};
        double thetadot2_data[1000] = {0.0};

        double Ep2_data[1000] = {0.0};
        double Ek2_data[1000] = {0.0};
        double Ec2_data[1000] = {0.0};

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
        DoublePendulum pendulum(x0, y0, 0.1, 0.2, 3.0, 3.0, 90.0, 90.0, 0.0, 0.0);

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
    double dt = 0.016;

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
                    case 0: SimulatePendulumApprox(single); break;
                    case 1: SimulatePendulumEuler(single); break;
                    case 2: SimulatePendulumHeun(single); break;
                    case 3: SimulatePendulumRK4(single); break;
                    default: break;
                }

                                
                updatePlotData(t_data[999] + dt, t_data, 1000);
                updatePlotData(single.theta, theta_data, 1000);
                updatePlotData(single.thetadot, thetadot_data, 1000);

                double pot = single.getPotencialEnergy();
                double kin = single.getKinematicEnergy();
                
                updatePlotData(pot, Ep_data, 1000);
                updatePlotData(kin, Ek_data, 1000);
                updatePlotData(kin + pot, Ec_data, 1000);


                //Trails data
                updateTrailData(xg + (single.x * scaleX), yg + (single.y * scaleY), trailPositions, 10000);
                trailPositionsVBO.UpdateData(trailPositions, 10000 * 2 * sizeof(float));
               
            }

            //Double Pendulum
            if(pendulumTypesIndex == 1){

                switch (pendulumNumericEqIndex2)
                {
                    case 0: SimulatePendulumEuler(pendulum);; break;
                    case 1: SimulatePendulumHeun(pendulum); break;
                    case 2: SimulatePendulumRK4(pendulum); break;
                    default: break;
                }

                updatePlotData(t2_data[999] + dt, t2_data, 1000);
                updatePlotData(pendulum.theta1, theta1_data, 1000);
                updatePlotData(pendulum.thetadot1, thetadot1_data, 1000);
                updatePlotData(pendulum.theta2, theta2_data, 1000);
                updatePlotData(pendulum.thetadot2, thetadot2_data, 1000);

                double pot = pendulum.getPotencialEnergy();
                double kin = pendulum.getKinematicEnergy();
                
                updatePlotData(pot, Ep2_data, 1000);
                updatePlotData(kin, Ek2_data, 1000);
                updatePlotData(kin + pot, Ec2_data, 1000);

                //Trails data
                updateTrailData(xg + (pendulum.x1 * scaleX), yg + (pendulum.y1 * scaleY), doubleTrailPostions, 10000);
                doubleTrailPostionsVBO.UpdateData(doubleTrailPostions, 10000 * 2 * sizeof(float));

                updateTrailData(xg + (pendulum.x2 * scaleX), yg + (pendulum.y2 * scaleY), doubleTrailPostions2, 10000);
                doubleTrailPostionsVBO2.UpdateData(doubleTrailPostions2, 10000 * 2 * sizeof(float));

     
            }

        }

        /*
        ==============================================================    
                        GRAPHICS ADJUSTMENTS
        ==============================================================    
        */

        if(pendulumTypesIndex == 0){

                singleLine.setPositions( xg, yg, 0.0f, xg + (single.x * scaleX), yg + (single.y * scaleY), 0.0f);
                singleLineMesh.UpdateData(singleLine.getVerticesArrayData(), singleLine.getVerticesArraySize());

                singleCircle.generatePoints(xg + (single.x * scaleX), yg + (single.y * scaleY), 25.0f, segments);
                singleCircleMesh.UpdateData(singleCircle.getVerticesArrayData(), singleCircle.getVerticesArraySize());



        }

        if(pendulumTypesIndex == 1){

                doubleLine1.setPositions(xg, yg, 0.0f, xg + (pendulum.x1 * scaleX), yg + (pendulum.y1 * scaleY), 0.0f);
                doubleLine1Mesh.UpdateData(doubleLine1.getVerticesArrayData(), doubleLine1.getVerticesArraySize());


                doubleLine2.setPositions(xg + (pendulum.x1 * scaleX), yg + (pendulum.y1 * scaleY), 0.0f, xg + (pendulum.x2 * scaleX), yg + (pendulum.y2 * scaleY), 0.0f);
                doubleLine2Mesh.UpdateData(doubleLine2.getVerticesArrayData(), doubleLine2.getVerticesArraySize());

                circle1.generatePoints(xg + (pendulum.x1 * scaleX), yg + (pendulum.y1 * scaleY), 25.0f, segments);
                circle2.generatePoints(xg + (pendulum.x2 * scaleX), yg + (pendulum.y2 * scaleY), 25.0f, segments);
            

                circleMesh1.UpdateData(circle1.getVerticesArrayData(), circle1.getVerticesArraySize());
                circleMesh2.UpdateData(circle2.getVerticesArrayData(), circle2.getVerticesArraySize());
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
            glPointSize(2.5f);
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
            glPointSize(2.5f);
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

            if (ImGui::Button("Start")){ isSimulationRunning = true; }
            ImGui::SameLine();
            if (ImGui::Button("Stop")){ isSimulationRunning = false; }
            ImGui::SameLine();
            if (ImGui::Button("Reset")){

                if(pendulumTypesIndex == 0){
                    single.ResetValues();
                    single.UpdateCartesianCoordinates();
                    std::fill(&trailPositions[0], &trailPositions[(10000 * 2) - 1], 0.0f);
                }
                else{
                    pendulum.ResetValues();
                    pendulum.UpdateCartesianCoordinates();
                    std::fill(&doubleTrailPostions[0], &doubleTrailPostions[(10000 * 2) - 1], 0.0f);
                    std::fill(&doubleTrailPostions2[0], &doubleTrailPostions2[(10000 * 2) - 1], 0.0f);
                }

                isSimulationRunning = false;
            }

            if (ImGui::Combo("Choose pendulum", &pendulumTypesIndex, pendulumTypes, IM_ARRAYSIZE(pendulumTypes))) {
                printf("Selected: %s\n", pendulumTypes[pendulumTypesIndex]);
                
            }

            //Single pendulum
            if(pendulumTypesIndex == 0){

                if (ImGui::Combo("Numerical method", &pendulumNumericEqIndex, pendulumNumericEq, IM_ARRAYSIZE(pendulumNumericEq))) {
                    printf("Selected: %s\n", pendulumNumericEq[pendulumNumericEqIndex]);
                }

                ImGui::PushID(0);

                ImGui::Text("Change parameters");
                ImGui::InputDouble("Mass", &single.m, 0.01, 3.0, "%.2f");

                if(ImGui::InputDouble("Rod length", &single.l, 0.01, 3.0, "%.2f"))
                    single.UpdateCartesianCoordinates();
                if (ImGui::InputDouble("Theta (degrees)", &degrees, 0.0, 360.0, "%.2f")) {
                    single.theta = glm::radians(degrees);
                    single.UpdateCartesianCoordinates();
                }

       

                ImGui::Text("Actual data");
                ImGui::BulletText("Mass: %f", single.m);
                ImGui::BulletText("Rod length: %f", single.l);
                ImGui::BulletText("Thetha (radians): %f", single.theta);
                ImGui::BulletText("Angular velocity: %f", single.thetadot);

                ImGui::PopID();
                
                if (ImPlot::BeginPlot("Position and velocity")) {
                    ImPlot::PlotLine("Theta", t_data, theta_data, 1000);
                    ImPlot::PlotLine("ThetaDot", t_data, thetadot_data, 1000);
                    ImPlot::EndPlot();
                }

                if (ImPlot::BeginPlot("Energy")) {
                    ImPlot::PlotLine("Ep", t_data, Ep_data, 1000);
                    ImPlot::PlotLine("Ek ", t_data, Ek_data, 1000);
                    ImPlot::PlotLine("Ec ", t_data, Ec_data, 1000);
                    ImPlot::EndPlot();
                }

            }

            //Double Pendulum
            if(pendulumTypesIndex == 1){

                if (ImGui::Combo("Numerical method", &pendulumNumericEqIndex2, pendulumNumericEq2, IM_ARRAYSIZE(pendulumNumericEq2))) {
                    printf("Selected: %s\n", pendulumNumericEq2[pendulumNumericEqIndex2]);
                }
`
                ImGui::PushID(0);

                ImGui::Text("Change parameters");
                if(ImGui::InputDouble("Rod length 1", &pendulum.l1, 0.01, 3.0, "%.2f") || ImGui::InputDouble("Rod length 2", &pendulum.l2, 0.01, 5.0, "%.2f")){
                      pendulum.UpdateCartesianCoordinates();
                }
            
                if (ImGui::InputDouble("Theta 1 (degrees)", &degrees2, 0.0, 360.0, "%.2f")) {
                    pendulum.theta1 = glm::radians(degrees2);
                    pendulum.UpdateCartesianCoordinates();
                }
                if (ImGui::InputDouble("Theta 2 (degrees)", &degrees3, 0.0, 360.0, "%.2f")) {
                    pendulum.theta2 = glm::radians(degrees3);
                    pendulum.UpdateCartesianCoordinates();
                }


                ImGui::Text("Actual data");
                ImGui::BulletText("Mass 1: %f", pendulum.m1); ImGui::SameLine();
                ImGui::BulletText("Mass 2: %f", pendulum.m2);
                ImGui::BulletText("Rod length 1: %f", pendulum.l1); ImGui::SameLine();
                ImGui::BulletText("Rod length 2: %f", pendulum.l2);
                ImGui::BulletText("Thetha 1 (radians): %f", pendulum.theta1); ImGui::SameLine();
                ImGui::BulletText("Thetha 2 (radians): %f", pendulum.theta2);
                ImGui::BulletText("Angular velocity 1 : %f", pendulum.thetadot1);ImGui::SameLine();
                ImGui::BulletText("Angular velocity 2 : %f", pendulum.thetadot2);

                ImGui::PopID();

                 
                if (ImPlot::BeginPlot("Positions and velocities")) {
                    ImPlot::PlotLine("Theta 1", t2_data, theta1_data, 1000);
                    ImPlot::PlotLine("Theta 2", t2_data, theta2_data, 1000);
                    ImPlot::PlotLine("ThetaDot 1 ", t2_data, thetadot1_data, 1000);
                    ImPlot::PlotLine("ThetaDot 2 ", t2_data, thetadot2_data, 1000);
                    ImPlot::EndPlot();
                }

                if (ImPlot::BeginPlot("Energy")) {
                    ImPlot::PlotLine("Ep", t2_data, Ep2_data, 1000);
                    ImPlot::PlotLine("Ek ", t2_data, Ek2_data, 1000);
                    ImPlot::PlotLine("Ec ", t2_data, Ec2_data, 1000);
                    ImPlot::EndPlot();
                }
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