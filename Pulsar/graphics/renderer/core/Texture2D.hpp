#pragma once

#include <string> //std::string

//Class represent texture 2D
class Texture2D{

public:
        
        //Constr. & destr.
        Texture2D() = delete;
        Texture2D(const std::string& filepath);
        ~Texture2D();

        //Utilities
        void Bind(unsigned int slot = 0) const;
        void UnBind() const;

        inline int GetWidth() const { return m_Width; }
        inline int GetHeight() const { return m_Height; }


private:
        unsigned int m_ID;
        std::string m_FilePath;
        unsigned char* m_CacheImageBuffer;
        int m_Width, m_Height, m_BytesPerPixel;

};//class Texture2D