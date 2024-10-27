#include "VertexBuffer.hpp"

#include "glad.h" //gl functions

//Constr, Destr.

VertexBuffer::VertexBuffer(const void* data, unsigned int size){
    glGenBuffers(1,&m_ID);
    glBindBuffer(GL_ARRAY_BUFFER,m_ID);
    glBufferData(GL_ARRAY_BUFFER, size , data , GL_STATIC_DRAW);   //usage can be changed for GL_DRAW_DYNAMIC
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