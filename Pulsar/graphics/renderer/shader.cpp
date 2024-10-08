#include "shader.hpp"

#include <fstream> //ifstream
#include <sstream> //stringstream

ShaderSource ReadGLSLFromFile(const std::string& filepath){
    
    std::ifstream file(filepath);
    std::string line;

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0 ,FRAGMENT = 1
    };

    ShaderType type = ShaderType::NONE;
    std::stringstream ss[2];

    while(std::getline(file,line))
    {
        if(line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
        
            else if(line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT; 
        }
        else
        {
            ss[(int)type] << line << "\n";
        }
        
    }

    return {ss[0].str(),ss[1].str()};
}


