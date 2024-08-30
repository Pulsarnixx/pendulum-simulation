#include "Pulsar.hpp"

int main(){

    PX_LOG::Init();

    PX::Init();

    const Window* window = PX::GetWindow();
    const Renderer* renderer = PX::GetRenderer();
    const Gui* gui = PX::GetGui();


    while (!window->ShouldWindowClose())
    {
        //Event handler - in the future

        renderer->BeginRender();
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