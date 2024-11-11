#pragma once

#include <vector> //for std::vector<T>

#include "renderer/core/VertexArray.hpp"
#include "renderer/core/VertexBuffer.hpp"
#include "renderer/core/VertexBufferLayout.hpp"
#include "renderer/core/IndexBuffer.hpp"

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
    void UpdateData(const void* data, unsigned int size) const;
    inline unsigned int  GetVerticiesNumber() const { return m_VerticesNumber; }

private:
    VertexArray     *m_VAO;
    VertexBuffer    *m_VBO;
    IndexBuffer     *m_EBO;
    unsigned int m_VerticesNumber;



}; //class Mesh