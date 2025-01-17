#include "Mesh.hpp"

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
    layout.Push<float>(3);  //positions
    layout.Push<float>(2);  //texture coorinates (uv)

    this->m_VAO->AddBuffer(*(this->m_VBO), layout);

    this->m_VAO->UnBind();
    this->m_VBO->UnBind();
    //Unbind index buffer only when vao is unbind.
    this->m_EBO->UnBind();

#ifdef DEBUG
    std::string message = "[MESH] constructor. VAO: " +
                          std::to_string(this->m_VAO->GetID()) + " VBO: " + std::to_string(this->m_VBO->GetID()) + 
                          " EBO: " + std::to_string(this->m_EBO->GetID());
    PX_CORE_TRACE(message);
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
    layout.Push<float>(3);  //positions

    this->m_VAO->AddBuffer(*(this->m_VBO), layout);

    this->m_VAO->UnBind();
    this->m_VBO->UnBind();

#ifdef DEBUG
    std::string message = "[MESH] constructor. VAO: " +
                        std::to_string(this->m_VAO->GetID()) + " VBO: " + std::to_string(this->m_VBO->GetID());
    PX_CORE_TRACE(message);
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
        std::string message = "[MESH] destructor ";
        PX_CORE_TRACE(message);
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

void Mesh::UpdateData(const void* data, unsigned int size) const{

    if(this->m_VAO != nullptr && this->m_VBO != nullptr){
        m_VBO->UpdateData(data,size);
    }
}
