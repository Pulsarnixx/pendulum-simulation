#pragma once

#include <string>

struct ShaderSource{
    std::string s_vertexSource;
    std::string s_fragmentSource;
};

ShaderSource ReadGLSLFromFile(const std::string& filepath);