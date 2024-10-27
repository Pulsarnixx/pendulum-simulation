#pragma once

#include <string> //std::string
#include <unordered_map> //std::unordered_map for cache
#include <glm/glm.hpp> //math for glm::mat4


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

        inline unsigned int GetID() const { return m_ID; } //Not safe, to do later  
        inline const std::string GetSourcePath() const { return m_FilePath; }

        //Uniform manipulation
        void SetUniform1i(const std::string& name, int v0);
        void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3 );
        void SetUniformMat4f(const std::string& name, const glm::mat4& m1); 

private:
    ShaderSource ReadGLSLFromFile(const std::string& filepath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int GenerateShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
    int GetUniformLocation(const std::string& name);
    
private:
    unsigned int m_ID;
    std::string m_FilePath; //Debugging purpose
    std::unordered_map<std::string, int> m_CachedUniformLocations;
    
};