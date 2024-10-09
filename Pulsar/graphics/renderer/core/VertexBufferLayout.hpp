#pragma once

#include <vector> //vector
#include "glad.h" //gl functions

struct VertexBufferElements{

    unsigned int type;
    unsigned int count;
    int normalized; 

    static unsigned int GetTypeSize(unsigned int type)
    {
        switch(type)
        {
            case GL_FLOAT:          return 4;
            case GL_UNSIGNED_INT:   return 4;
            case GL_UNSIGNED_BYTE:  return 1;
        }

        return 0;
    }
};

class VertexBufferLayout{

public:
        VertexBufferLayout()
            :m_Stride(0){};

        template<typename T>
        void Push(unsigned int count);
        
        inline const std::vector<VertexBufferElements>& GetElements() const { return m_Elements; }
        inline unsigned int GetStride() const { return m_Stride; }


private:
        std::vector<VertexBufferElements> m_Elements;
        unsigned int m_Stride;
};

template<>
inline void VertexBufferLayout::Push<float>(unsigned int count){   
            m_Elements.push_back({GL_FLOAT,count,GL_FALSE});
            m_Stride += count * VertexBufferElements::GetTypeSize(GL_FLOAT);
}

template<>
inline void VertexBufferLayout::Push<unsigned int>(unsigned int count){   
            m_Elements.push_back({GL_UNSIGNED_INT,count,GL_FALSE});
            m_Stride += count * VertexBufferElements::GetTypeSize(GL_UNSIGNED_INT);
}

template<>
inline void VertexBufferLayout::Push<unsigned char>(unsigned int count){   
            m_Elements.push_back({GL_UNSIGNED_BYTE,count,GL_TRUE});
            m_Stride += count * VertexBufferElements::GetTypeSize(GL_UNSIGNED_BYTE);
}