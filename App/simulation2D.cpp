#include "simulation2D.hpp"
#include "pendulum.hpp"

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

//Physics const.
static const double g = 9.81;
static const double dt = 0.025;

//Starting point
static double x_0 = double(Width) / 2;
static double y_0 = double(Height) * 0.75;


void SimulatePendulumEuler(SinglePendulum& pendulum){

    //Calculate properties in polar coordinates
    float thethaddot = -(g / pendulum.l) * sin(pendulum.thetha);
    pendulum.thethadot += (thethaddot * dt);    
    pendulum.thetha += (pendulum.thethadot * dt);

    //Update cartesian coordinates based on polar coordinates values
    pendulum.x = x_0 + ( pendulum.l * sinf(pendulum.thetha));
    pendulum.y = y_0 - ( pendulum.l * cosf(pendulum.thetha));
}

void SimulatePendulumApprox(SinglePendulum& pendulum){

    //Calculate properties in polar coordinates
    float thethaddot = -(g / pendulum.l) * pendulum.thetha;
    pendulum.thethadot += (thethaddot * dt);    
    pendulum.thetha += (pendulum.thethadot * dt);

    //Update cartesian coordinates based on polar coordinates values
    pendulum.x = x_0 + ( pendulum.l * sinf(pendulum.thetha));
    pendulum.y = y_0 - ( pendulum.l * cosf(pendulum.thetha));

}

void SimulateRungeKutta(DoublePendulum& pendulum){

    //Calculate properties in polar coordinates for mass 1
    float thethaddot = -(g / pendulum.l1) * sin(pendulum.thetha1);
    pendulum.thethadot1 += (thethaddot * dt);    
    pendulum.thetha1 += (pendulum.thethadot1 * dt);

    //Update cartesian coordinates based on polar coordinates values for mass 1 and 2
    pendulum.x1 = x_0 + ( pendulum.l1 * sinf(pendulum.thetha1));
    pendulum.y1 = y_0 - ( pendulum.l1 * cosf(pendulum.thetha1));

    pendulum.x2 = pendulum.x1 + ( pendulum.l2 * sinf(pendulum.thetha2));
    pendulum.y2 = pendulum.y1 - ( pendulum.l2 * cosf(pendulum.thetha2));
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
        window->SetVsync(false);

        System::InitUI();
        const Gui* gui = System::GetGui();

        bool isSimulationRunning = false;
        bool isSinglePendulum = true;

    /*
    ==============================================================    
                    DATA CONFIGURATION 
    ==============================================================    
    */
    

        DoublePendulum pendulum;

        InitDoublePendulum(x_0,y_0,pendulum);
        

        SinglePendulum single;

        InitPendulum(x_0,y_0,single);

        Line singleLine(x_0, y_0, 0.0f, single.x, single.y, 0.0f);
        Line doubleLine1(x_0, y_0, 0.0f, pendulum.x1, pendulum.y1, 0.0f);
        Line doubleLine2(pendulum.x1, pendulum.y1, 0.0f, pendulum.x2, pendulum.y2, 0.0f);

        int segments = 100;
        
        Circle singleCircle(single.x, single.y, single.r, segments);
        Circle circle1(pendulum.x1, pendulum.y1, pendulum.r1, segments);
        Circle circle2(pendulum.x2, pendulum.y2, pendulum.r2, segments);
        
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

        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,-0.5f));
        glm::mat4 proj = glm::ortho(0.0f, (float)Width, 0.0f, (float)Height, -1.0f, 1.0f);
        glm::mat4 mvpLines = proj * view * glm::mat4(1.0f);
        glm::mat4 mvpCircles = proj * view * glm::mat4(1.0f);

        //Set uniforms for lines once
        lineShader.Bind();
        lineShader.SetUniformMat4f("u_mvp",mvpLines);
        lineShader.UnBind();

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

            if(isSinglePendulum == true){
                SimulatePendulumEuler(single);

                /*
                ==============================================================    
                                GRAPHICS ADJUSTMENTS
                ==============================================================    
                */
                singleLine.setPositions( x_0, y_0, 0.0f, single.x, single.y, 0.0f);
                singleLineMesh.UpdateData(singleLine.getVerticesArrayData(), singleLine.getVerticesArraySize());

                singleCircle.generatePoints(single.x, single.y, single.r, segments);
                singleCircleMesh.UpdateData(singleCircle.getVerticesArrayData(), singleCircle.getVerticesArraySize());
            }

            else{
                
                SimulateRungeKutta(pendulum);

                /*
                ==============================================================    
                                GRAPHICS ADJUSTMENTS
                ==============================================================    
                */

                doubleLine1.setPositions(x_0, y_0, 0.0f, pendulum.x1, pendulum.y1, 0.0f );
                doubleLine1Mesh.UpdateData(doubleLine1.getVerticesArrayData(), doubleLine1.getVerticesArraySize());


                doubleLine2.setPositions( pendulum.x1, pendulum.y1, 0.0f, pendulum.x2, pendulum.y2, 0.0f);
                doubleLine2Mesh.UpdateData(doubleLine2.getVerticesArrayData(), doubleLine2.getVerticesArraySize());

                circle1.generatePoints(pendulum.x1, pendulum.y1, pendulum.r1, segments);
                circle2.generatePoints(pendulum.x2, pendulum.y2, pendulum.r2, segments);
            

                circleMesh1.UpdateData(circle1.getVerticesArrayData(), circle1.getVerticesArraySize());
                circleMesh2.UpdateData(circle2.getVerticesArrayData(), circle2.getVerticesArraySize());

            }

        }


        /*
        ==============================================================    
                            RENDERING
        ==============================================================    
        */

        renderer->BeginRender();

        if(isSinglePendulum == true){

            /* RENDER LINE*/
            renderer->RenderLine(singleLineMesh, lineShader);
            

            /* RENDER CIRCLE */
            circleShader.Bind();
            circleShader.SetUniformMat4f("u_mvp", mvpCircles);

            renderer->RenderCircle(singleCircleMesh,circleShader);

        }
        else{

            /* RENDER LINES */
            renderer->RenderLine(doubleLine1Mesh, lineShader);
            renderer->RenderLine(doubleLine2Mesh, lineShader);

            /* RENDER CIRCLES*/
            circleShader.Bind();
            circleShader.SetUniformMat4f("u_mvp", mvpCircles);

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

            if (ImGui::Button("Single Pendulum")){ isSinglePendulum = true; }
            ImGui::SameLine();
            if (ImGui::Button("Double Pendulum")){ isSinglePendulum = false; }
                
            if(isSinglePendulum == true){
                ImGui::PushID(0);
                ImGui::Text("Single pendulum parameters");
                ImGui::SliderFloat("Rod length", &single.l, 0.0f , 300.0f);
                ImGui::SliderFloat("Thetha (radians)", &single.thetha, 0.0f , 2 * M_PI);

                ImGui::Text("Single pendulum data");
                ImGui::BulletText("Rod length: %f", single.l);
                ImGui::BulletText("Thetha (radians): %f", single.thetha);
                ImGui::BulletText("Position (x,y): %f, %f", single.x , single.y);
                ImGui::BulletText("Angular velocity: %f", single.thethadot);

                ImGui::PopID();
            }

            if(isSinglePendulum == false){
                ImGui::PushID(0);
                ImGui::Text("Double pendulum parameters");
                ImGui::SliderFloat("Rod 1 length", &pendulum.l1, 0.0f , 300.0f);
                ImGui::SliderFloat("Rod 2 length", &pendulum.l2, 0.0f , 300.0f);
                ImGui::SliderFloat("Thetha 1 (radians)", &pendulum.thetha1, 0.0f , 2 * M_PI);
                ImGui::SliderFloat("Thetha 2 (radians)", &pendulum.thetha2, 0.0f , 2 * M_PI);


                ImGui::Text("Double pendulum data");
                ImGui::BulletText("Rod length 1: %f", pendulum.l1);
                ImGui::BulletText("Rod length 2: %f", pendulum.l2);
                ImGui::BulletText("Thetha 1 (radians): %f", pendulum.thetha1);
                ImGui::BulletText("Thetha 2 (radians): %f", pendulum.thetha2);
                ImGui::BulletText("Position 1 (x,y): %f, %f", pendulum.x1 , pendulum.y1);
                ImGui::BulletText("Position 2 (x,y): %f, %f", pendulum.x2  , pendulum.y2);
                ImGui::BulletText("Angular velocity 1 : %f", pendulum.thethadot1);
                ImGui::BulletText("Angular velocity 2 : %f", pendulum.thethadot2);

               

                ImGui::PopID();
            }

            if (ImGui::Button("Start")){ isSimulationRunning = true; }
            ImGui::SameLine();
            if (ImGui::Button("Stop")){ isSimulationRunning = false; }
            ImGui::SameLine();
            if (ImGui::Button("Reset")){

                if(isSinglePendulum == true)
                    InitPendulum(x_0,y_0,single);
                else
                    InitDoublePendulum(x_0,y_0,pendulum);
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