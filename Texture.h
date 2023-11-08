#ifndef __TEXTURE__
#define __TEXTURE__

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"

/** @class Texture
 *  @brief Classe para lidar com texturas em OpenGL.
 *
 *  A classe Texture é usada para carregar e configurar texturas que serão usadas em aplicações OpenGL.
 */
class Texture {
    private:
        std::string* texture_path;  /**< Caminho para o arquivo da textura */
        GLuint textureID;  /**< ID da textura gerado pelo OpenGL */

        GLint mag_filter_type;  /**< Tipo de filtro de magnificação */
        GLint min_filter_type;  /**< Tipo de filtro de minificação */
        GLint wrap_s_type;  /**< Tipo de envolvimento da textura no eixo S */
        GLint wrap_t_type;  /**< Tipo de envolvimento da textura no eixo T */

    public:
        /** Construtor da classe Texture que permite especificar configurações de filtragem e envolvimento.
         * @param texture_path Caminho para o arquivo da textura.
         * @param mag_filter_type Tipo de filtro de magnificação.
         * @param min_filter_type Tipo de filtro de minificação.
         * @param wrap_s_type Tipo de envolvimento da textura no eixo S.
         * @param wrap_t_type Tipo de envolvimento da textura no eixo T.
         */
        Texture(std::string texture_path, GLint &mag_filter_type, GLint &min_filter_type, GLint &wrap_s_type, GLint &wrap_t_type);

        /** 
         * Construtor da classe Texture que permite especificar apenas o caminho da textura.
         * @param texture_path Caminho para o arquivo da textura.
         */
        Texture(std::string texture_path);

        /**
         * Construtor da classe Texture sem parâmetros.
         * Permite iniciar a textura sem um caminho de arquivo definido.
         */
        Texture();

        /**  
         * Destrutor da classe Texture. 
         */
        ~Texture();  

        /** Obtém o ID da textura gerado pelo OpenGL.
         * @return ID da textura.
         */
        GLuint getTextureID();

        /** Define o caminho do arquivo da textura.
         * @param texture_path Caminho para o arquivo da textura.
         * @return Referência para a instância de Texture atualizada.
         */
        Texture& setTexturePath(std::string texture_path);

        /** Define o tipo de filtro de magnificação.
         * @param mag_filter_type Tipo de filtro de magnificação.
         * @return Referência para a instância de Texture atualizada.
         */
        Texture& setMagFilterType(GLint mag_filter_type);

        /** Define o tipo de filtro de minificação.
         * @param min_filter_type Tipo de filtro de minificação.
         * @return Referência para a instância de Texture atualizada.
         */
        Texture& setMinFilterType(GLint min_filter_type);

        /** Define o tipo de envolvimento da textura no eixo S.
         * @param wrap_s_type Tipo de envolvimento da textura no eixo S.
         * @return Referência para a instância de Texture atualizada.
         */
        Texture& setWrapSType(GLint wrap_s_type);

        /** Define o tipo de envolvimento da textura no eixo T.
         * @param wrap_t_type Tipo de envolvimento da textura no eixo T.
         * @return Referência para a instância de Texture atualizada.
         */
        Texture& setWrapTType(GLint wrap_t_type);

        /** Carrega a textura da imagem do caminho especificado.
         * @return 0 se a textura for carregada com sucesso, -1 se houver um erro no caminho do arquivo e -2 se houver um erro ao carregar a imagem.
         */
        int loadTexture();

        /** Atualiza os parâmetros da textura após a configuração.
         * @return Referência para a instância de Texture atualizada.
         */
        Texture& updateTextureParamters();
};

#endif
