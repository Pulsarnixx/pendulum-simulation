#include "Pulsar.hpp"

int main(){

    Log::Init();

    PX_CORE_WARN("Warning");

    pxGraphicsManager &gManager = pxGraphicsManager::getSystem();
    
    if( gManager.Init() == false ){
        gManager.Clean();
        return -1;
    } 
    
    Window *window = gManager.GetWindow();
    Renderer *renderer = gManager.GetRenderer();
    Gui *gui = gManager.GetGui();


    if (window == nullptr || renderer == nullptr || gui == nullptr) {
        gManager.Clean();
        return -1;
    }

    while (!window->ShouldClose())
    {
        // input / events


        //Imgui on begin
        gui->OnBegin();
  
        // render
        renderer->OnRender();

        // //Imgui on end
        gui->OnEnd();

        window->onUpdate();
    } 
    
   
    gManager.Clean();
    return 0;
}