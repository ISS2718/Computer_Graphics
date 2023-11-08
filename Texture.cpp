#include "Texture.h"

Texture::Texture(std::string texture_path, GLint mag_filter_type, GLint min_filter_type, GLint wrap_s_type, GLint wrap_t_type) {
    this->texture_path = new std::string(texture_path);
    this->textureID = -1;

    this->mag_filter_type = mag_filter_type;
    this->min_filter_type = min_filter_type;
    
    this->wrap_s_type = wrap_s_type;
    this->wrap_t_type = wrap_t_type;
}

Texture::Texture(std::string texture_path) {
    this->texture_path = new std::string(texture_path);
    this->textureID = -1;

    this->mag_filter_type = -1;
    this->min_filter_type = -1;
    
    this->wrap_s_type = -1;
    this->wrap_t_type = -1;
}

Texture::Texture() {
    this->texture_path = nullptr;
    this->textureID = -1;

    this->mag_filter_type = -1;
    this->min_filter_type = -1;

    this->wrap_s_type = -1;
    this->wrap_t_type = -1;
}

Texture::~Texture() {
    delete texture_path;
}

GLuint Texture::getTextureID() {
    return textureID;
}

Texture& Texture::setTexturePath(std::string texture_path) {
    if(this->texture_path != nullptr) {
        delete this->texture_path;
    }
    this->texture_path = new std::string(texture_path);
    return *this;
}

Texture& Texture::setMagFilterType(GLint mag_filter_type) {
    this->mag_filter_type = mag_filter_type;
    return *this;
}

Texture& Texture::setMinFilterType(GLint min_filter_type) {
    this->min_filter_type = min_filter_type;
    return *this;
}

Texture& Texture::setWrapSType(GLint wrap_s_type) {
    this->wrap_s_type = wrap_s_type;
    return *this;
}

Texture& Texture::setWrapTType(GLint wrap_t_type) {
    this->wrap_t_type = wrap_t_type;
    return *this;
}

int Texture::loadTexture() {
    if(texture_path == nullptr) {
        return -1;
    }

    // Solicitando um slot de textura
    glGenTextures(1, &textureID);
    
    // "Vinculando" a textura recém-criada com todas as configurações de modificação de textura.
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter_type);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter_type);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s_type);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t_type);

    // Parâmetros da imagem
    GLint width = 0, height = 0, nrChannels = 0;

    // Para carregar a textura no sentido original da imagem
    stbi_set_flip_vertically_on_load(true);

    // Carrega a imgaem;
    GLubyte *data = stbi_load(texture_path->c_str(), &width, &height, &nrChannels, 0);

    if(data == nullptr) {
        return -2;
    } else {
        // Enviando a imagem para o OpenGL
        if(nrChannels == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        } else if(nrChannels == 3) {
             glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        stbi_image_free(data);
    }

    return 0;
}

Texture& Texture::updateTextureParamters() {
    // "Vinculando" a textura recém-criada com todas as configurações de modificação de textura.
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter_type);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter_type);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s_type);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t_type);

    return *this;
}