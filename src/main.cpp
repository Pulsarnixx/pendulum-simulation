#include "core/systemhandler.hpp"

int main(){

    SystemHandler &system = SystemHandler::getSystem();
    
    if( system.Init() == true ) system.Run();
    
    system.Clean();

    return 0;
}