#include "Pulsar.hpp"

int main(){

    PX_LOG::Init();
    Timer::Init();


    PX::Init();

    const Window* window = PX::GetWindow();
    const Renderer* renderer = PX::GetRenderer();
    const Gui* gui = PX::GetGui();


    while (!window->ShouldWindowClose())
    {
        //Event handler - in the future

        PX_CORE_TIMER_START();

        renderer->BeginRender();
        PX_CORE_TIMER_STOP_MILI("Rendering");


        /*
            Calculation...

            Rendering staff...
        */
        //GUI - in the future
        
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