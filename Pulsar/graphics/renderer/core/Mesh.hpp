#pragma once

#include <vector> //for std::vector<T>

//Forward dec. - perhaps temp. solution, cause this causes initialization to heap memory. Maybe better is to use opengl function without OOP?
class VertexArray;
class VertexBuffer;
class IndexBuffer;

/*
    Mesh class that's just container for VertexArray, VertexBuffer and IndexBuffer objects
*/
class Mesh{


public:

    //Constr. & destr.
    Mesh() = delete;
    //VBO & EBO
    Mesh(const void* verticesData, unsigned int verticesSize, const unsigned int* indiciesData, unsigned int indiciesSize);
    //VBO
    Mesh(const void* verticesData, unsigned int verticesSize);
    ~Mesh();

    //Utilities
    void Bind();
    void UnBind();
    inline unsigned int  GetVerticiesNumber() const { return m_VerticesNumber; }

private:
    VertexArray     *m_VAO;
    VertexBuffer    *m_VBO;
    IndexBuffer     *m_EBO;
    unsigned int m_VerticesNumber;



}; //class Mesh