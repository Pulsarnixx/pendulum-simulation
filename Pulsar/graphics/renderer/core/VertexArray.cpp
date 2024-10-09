#include "VertexArray.hpp"

#include "glad.h"                   //gl functions
#include "VertexBuffer.hpp"         //class VertexBuffer
#include "VertexBufferLayout.hpp"   //class VertexBufferLayout

//Constr, Destr.
VertexArray::VertexArray(){
    glGenVertexArrays(1, &m_ID);
}

VertexArray::~VertexArray(){
    glDeleteVertexArrays(1, &m_ID);
}

//Utilities
void VertexArray::Bind() const {
    glBindVertexArray(m_ID);
}

void VertexArray::UnBind() const {
    glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer& buffer, const VertexBufferLayout& layout){
    this->Bind(); //Bind vao first   
    buffer.Bind(); //Bind buffer

    //Bind all Vertex Attributes coresponding to current buffer (vbo)
    int offset = 0;
    const auto elements = layout.GetElements();
    for(unsigned int i = 0 ; i < elements.size(); i++)
    {
        const auto element = elements[i];
        glVertexAttribPointer(  i, element.count, element.type, element.normalized, 
                                layout.GetStride(), (const void*)offset);
        glEnableVertexAttribArray(i);
        
        offset += element.count * VertexBufferElements::GetTypeSize(element.type); 
    }
}
