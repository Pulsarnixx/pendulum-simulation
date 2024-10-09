#pragma once


/*
    Class represents vertex array object
*/
class VertexArray{

public:
        //Constr, Destr.
        VertexArray();
        ~VertexArray();

        //Utilities
        void Bind() const;
        void UnBind() const;
        // void AddBuffer(const VertexBuffer& buffer, const VertexBufferLayout& layout);

private:
        unsigned int m_ID;
};