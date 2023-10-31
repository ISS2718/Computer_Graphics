#ifndef __TEXTURE__
#define __TEXTURE__

#include <iostream>
#include <string>
#include <GL/glew.h>  
#include <GLFW/glfw3.h>

#include "stb_image.h"

class Texture {
    private:
        std::string* texture_path;
        GLuint textureID;

        GLint mag_filter_type, min_filter_type;
        GLint wrap_s_type, wrap_t_type;

    public:
        Texture(std::string texture_path, GLint &mag_filter_type, GLint &min_filter_type, GLint &wrap_s_type, GLint &wrap_t_type);
        Texture(std::string texture_path);
        Texture();
        ~Texture();

        GLuint getTextureID();

        Texture& setTexturePath(std::string texture_path);
        Texture& setMagFilterType(GLint mag_filter_type);
        Texture& setMinFilterType(GLint min_filter_type);
        Texture& setWrapSType(GLint wrap_s_type);
        Texture& setWrapTType(GLint wrap_t_type);  

        int loadTexture();
        Texture& updateTextureParamters();
};

#endif