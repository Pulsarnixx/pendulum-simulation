#include "VertexBuffer.hpp"

#include "glad.h" //gl functions

//Constr, Destr.

VertexBuffer::VertexBuffer(const void* data, unsigned int size){
    glGenBuffers(1,&m_ID);
    glBindBuffer(GL_ARRAY_BUFFER,m_ID);
    glBufferData(GL_ARRAY_BUFFER, size , data , GL_DYNAMIC_DRAW);   //usage can be changed for GL_DYNAMIC_DRAW
}

VertexBuffer::~VertexBuffer(){
    glDeleteBuffers(1,&m_ID);
}

//Utilities

void VertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}
void VertexBuffer::UnBind() const {
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void VertexBuffer::UpdateData(const void* data, unsigned int size) const {
    glBindBuffer(GL_ARRAY_BUFFER,m_ID);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);  // Aktualizacja danych linii 1
}