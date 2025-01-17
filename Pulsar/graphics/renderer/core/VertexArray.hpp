#pragma once

//Forward dec.
class VertexBuffer;
class VertexBufferLayout;

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
        void AddBuffer(const VertexBuffer& buffer, const VertexBufferLayout& layout);
        unsigned int GetID() const { return m_ID; }

private:
        unsigned int m_ID;
};