#include "VertexArray.hpp"

#include "glad.h" //gl functions

//Constr, Destr.
VertexArray::VertexArray(){
    glGenVertexArrays(1, &m_ID);
}

VertexArray::VertexArray(){
    glDeleteVertexArrays(1, &m_ID);
}

//Utilities
void VertexArray::Bind() const {
    glBindVertexArray(m_ID);
}

void VertexArray::UnBind() const {
    glBindVertexArray(0);
}
