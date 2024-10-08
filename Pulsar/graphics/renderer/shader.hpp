#pragma once

#include <string>

//Forward dec.
struct ShaderSource;

/*
    Class represents shader program
*/
class Shader{

public:
        //Constr, Destr.
        Shader(const std::string& filepath);
        ~Shader();

        //Utilities
        void Bind() const;
        void UnBind() const;

private:
    ShaderSource ReadGLSLFromFile(const std::string& filepath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int GenerateShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
    //PrintSourceFile()
    //GetId()
    
private:
    unsigned int m_ID;
    std::string m_FilePath; //Debugging purpose




};