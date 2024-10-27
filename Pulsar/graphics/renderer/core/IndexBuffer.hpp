#pragma once

/*
    Class represents element buffer object / index buffer object
*/
class IndexBuffer{

public:

        //Constr, Destr.
        IndexBuffer() = delete;
        IndexBuffer(const unsigned int* data, unsigned int size);
        ~IndexBuffer();

        //Utilities
        void Bind() const ;
        void UnBind() const ;
        inline unsigned int GetCount() const { return m_Count; }

private:
        unsigned int m_ID;
        unsigned int m_Count;

};