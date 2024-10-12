#include "shader.hpp"

#include <fstream> //ifstream
#include <sstream> //stringstream
#include "glad.h"  //gl functions
//#include <glm> in the future

//ShaderSource definition
struct ShaderSource{
    std::string s_vertexSource;
    std::string s_fragmentSource;
};

//Constr, Destr.
Shader::Shader(const std::string& filepath)
    :m_ID(0),m_FilePath(filepath)
{
    ShaderSource source = ReadGLSLFromFile(filepath);
    m_ID = GenerateShaderProgram(source.s_vertexSource, source.s_fragmentSource);
}

Shader::~Shader(){
    glDeleteProgram(m_ID);
}

//Utilities
void Shader::Bind() const {
    glUseProgram(m_ID);
}

void Shader::UnBind() const {
    glUseProgram(0);
}

void Shader::SetUniform1i(const std::string& name, int v0){
    int location = GetUniformLocation(name);

    if(location != -1)
        glUniform1i(location, v0);
}
void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3 ){
    int location = GetUniformLocation(name);

    if(location != -1)
        glUniform4f(location, v0, v1, v2, v3);
}

// void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& m1){
//     int location = GetUniformLocation(name);

//     if(location != -1)
//         glUniformMatrix4fv(location,1,false,&m1[0][0]);

// }

//Private

unsigned int Shader::CompileShader(unsigned int type, const std::string& source){

    unsigned int shaderID = glCreateShader(type);
    const char* src = source.c_str();

    glShaderSource(shaderID,1,&src,nullptr);
    glCompileShader(shaderID);
   
    //Error handling -  TODO
    int result;
    glGetShaderiv(shaderID,GL_COMPILE_STATUS,&result);
    if(result == GL_FALSE){
        int length;
        glGetShaderiv(shaderID,GL_INFO_LOG_LENGTH,&length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(shaderID,length,&length,message);

        fprintf(stderr,"Failed to compile shader!\n");
        fprintf(stderr,"%s\n",message);
        
        glDeleteShader(shaderID);
        return 0;
    }

    return shaderID;
}

unsigned int Shader::GenerateShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int programID = glCreateProgram(); 

    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(programID, vs);
    glAttachShader(programID, fs);
    glLinkProgram(programID);
    glValidateProgram(programID);

    //Delete unnecessary objects
    glDeleteShader(vs);
    glDeleteShader(fs);

    return programID;
}

ShaderSource Shader::ReadGLSLFromFile(const std::string& filepath){
    
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

int Shader::GetUniformLocation(const std::string& name){

    //First check cache
    if(m_CachedUniformLocations.find(name) != m_CachedUniformLocations.end())
        return m_CachedUniformLocations[name];

    //Then check in shader code
    int location = glGetUniformLocation(m_ID, name.c_str());

    //Cache new uniform
    if(location >= 0)
        m_CachedUniformLocations[name] = location;

    return location;//location values will be check during setting values
}


