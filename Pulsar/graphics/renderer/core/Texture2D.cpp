#include "Texture2D.hpp"

#include "glad.h"      //gl functions
#include "stb_image.h" //stb_image functions

//Constr. & destr.
Texture2D::Texture2D(const std::string& filepath)
    :m_ID(0),m_FilePath(filepath), m_CacheImageBuffer(nullptr), 
    m_Width(0), m_Height(0),m_BytesPerPixel(0)
{
    //Optional - depands on image format
    stbi_set_flip_vertically_on_load(1);
    m_CacheImageBuffer = stbi_load(filepath.c_str(),&m_Width,&m_Height,&m_BytesPerPixel,4);

    //Prepare OpenGL texture object
    glGenTextures(1,&m_ID);
    glBindTexture(GL_TEXTURE_2D,m_ID);

    //Texture Filtering
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    //Texture Wrapping
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);  //x
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);  //y
  
    //Copy data to OpenGL texture object
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,m_Width,m_Height,0,GL_RGBA,GL_UNSIGNED_BYTE,m_CacheImageBuffer);

    glBindTexture(GL_TEXTURE_2D,0);

    //Optional
    if(m_CacheImageBuffer)
        stbi_image_free(m_CacheImageBuffer);

}

Texture2D::~Texture2D(){
    glDeleteTextures(1,&m_ID);
}

//Utilities
void Texture2D::Bind(unsigned int slot) const{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D,m_ID);
}

void Texture2D::UnBind() const{
    glBindTexture(GL_TEXTURE_2D,0); 
}
