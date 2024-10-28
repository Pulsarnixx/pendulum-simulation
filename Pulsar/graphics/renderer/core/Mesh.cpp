#include "Mesh.hpp"

#include "renderer/core/VertexArray.hpp"
#include "renderer/core/VertexBuffer.hpp"
#include "renderer/core/VertexBufferLayout.hpp"
#include "renderer/core/IndexBuffer.hpp"
#include "renderer/core/Textures.hpp"

#define DEBUG

#ifdef DEBUG
    #include "../../../core/log/log.hpp"
#endif

//Constr. & destr.
Mesh::Mesh(const void* verticesData, unsigned int verticesSize, const unsigned int* indiciesData, unsigned int indiciesSize)
    :m_VerticesNumber(indiciesSize / sizeof(unsigned int))
{

    this->m_VAO = new VertexArray();
    this->m_VBO = new VertexBuffer(verticesData, verticesSize);
    this->m_EBO = new IndexBuffer(indiciesData, indiciesSize);

    //Vertex attributes
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);

    this->m_VAO->AddBuffer(*(this->m_VBO), layout);

    this->m_VAO->UnBind();
    this->m_VBO->UnBind();
    //Unbind index buffer only when vao is unbind.
    this->m_EBO->UnBind();

#ifdef DEBUG
    PX_CORE_TRACE("Mesh constructor");
#endif

}

Mesh::Mesh(const void* verticesData, unsigned int verticesSize)
    :m_VerticesNumber((verticesSize / 3) / sizeof(float))
{

    this->m_VAO = new VertexArray();
    this->m_VBO = new VertexBuffer(verticesData, verticesSize);
    this->m_EBO = nullptr;

    //Vertex attributes
    VertexBufferLayout layout;
    layout.Push<float>(3);

    this->m_VAO->AddBuffer(*(this->m_VBO), layout);

    this->m_VAO->UnBind();
    this->m_VBO->UnBind();

#ifdef DEBUG
    PX_CORE_TRACE("Mesh constructor");
#endif

}

Mesh::~Mesh(){

    if(this->m_EBO != nullptr){
        delete this->m_EBO;
        this->m_EBO = nullptr;
    }
    
    if(this->m_VBO != nullptr){
        delete this->m_VBO;
        this->m_VBO = nullptr;
    }
    
    if(this->m_VAO != nullptr){
        delete this->m_VAO;
        this->m_VAO = nullptr;
    }

    #ifdef DEBUG
    PX_CORE_TRACE("Mesh destructor");
    #endif
}

//Utilities

void Mesh::Bind(){

    if(this->m_VAO == nullptr && this->m_EBO == nullptr)
        return;

    if(this->m_VAO != nullptr)
        this->m_VAO->Bind();

    if(this->m_EBO != nullptr)
        this->m_EBO->Bind();

}

void Mesh::UnBind(){

    if(this->m_VAO == nullptr && this->m_EBO == nullptr)
        return;

    if(this->m_VAO != nullptr)
        this->m_VAO->UnBind();

    if(this->m_EBO != nullptr)
        this->m_EBO->UnBind();

}
