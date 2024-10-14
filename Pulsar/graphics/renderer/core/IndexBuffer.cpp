#include "IndexBuffer.hpp"

#include "glad.h" //gl functions


//Constr, Destr.
IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    :m_Count(count)
{

    //TODO assert
    // sizeof(unsigned int) == sizeof(GLuint);

    glGenBuffers(1,&m_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer(){
    glDeleteBuffers(1,&m_ID);
}

//Utilities
void IndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}
void IndexBuffer::UnBind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}