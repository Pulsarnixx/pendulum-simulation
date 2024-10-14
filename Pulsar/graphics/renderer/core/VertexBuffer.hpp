#pragma once

/*
    Class represents vertex buffer object
*/
class VertexBuffer
{
public:
        
        //Constr, Destr.
        // VertexBuffer() = delete;
        //VertexBuffer::VertexBuffer(const void* data, unsigned int size, unsigned int type, unsigned int usage){}
        VertexBuffer(const void* data, unsigned int size);
        ~VertexBuffer();

        //Utilities
        void Bind() const ;
        void UnBind() const ;

private:
        unsigned int m_ID;
        
};