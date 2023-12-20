#ifndef __SHADER__
#define __SHADER__

#include <GL/glew.h>  
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

#define INFO_LENGTH 512 /**< Tamanho máximo esperado para informações e mensagens de erro. */

/**
 * @class Shader
 * @brief Classe que lida com shaders em OpenGL, incluindo a compilação e carregamento de shaders de vértice e fragmento.
 */
class Shader {
private:
    std::string vertex_shader_path;     /**< Caminho para o arquivo do shader de vértice. */
    std::string fragment_shader_path;   /**< Caminho para o arquivo do shader de fragmento. */

    std::string s_vertex_shader;        /**< Conteúdo do shader de vértice. */
    std::string s_fragment_shader;      /**< Conteúdo do shader de fragmento. */

    GLint vertex_shader_ID;             /**< ID do shader de vértice após compilação. */
    GLint fragment_shader_ID;           /**< ID do shader de fragmento após compilação.*/

    char *info;             /**< Armazena informações de log da compilação dos shaders. */

    /**
     * @brief Carrega o conteúdo de um arquivo de shader.
     * @param path Caminho para o arquivo do shader.
     * @param shader Ponteiro para a string que conterá o conteúdo do shader.
     * @return 0 em caso de sucesso ou um código de erro.
     */
    int loadShader(const std::string &path, std::string *shader);

public:
    /**
     * @brief Construtor padrão da classe Shader.
     */
    Shader();

    /**
     * @brief Construtor da classe Shader que permite especificar os caminhos para os shaders de vértice e fragmento.
     * @param vertex_path Caminho para o arquivo do shader de vértice.
     * @param fragment_path Caminho para o arquivo do shader de fragmento.
     */
    Shader(std::string vertex_path, std::string fragment_path);

    /**
     * @brief Destrutor da classe Shader. Libera recursos associados aos shaders.
     */
    ~Shader();

    /**
     * @brief Define o caminho para o arquivo do shader de vértice.
     * @param vertex_shader_path Caminho para o arquivo do shader de vértice.
     * @return Uma referência à instância da classe Shader para suportar chamadas encadeadas.
     */
    Shader& setVertexShader(std::string vertex_shader_path);

    /**
     * @brief Define o caminho para o arquivo do shader de fragmento.
     * @param fragment_shader_path Caminho para o arquivo do shader de fragmento.
     * @return Uma referência à instância da classe Shader para suportar chamadas encadeadas.
     */
    Shader& setFragmentShader(std::string fragment_shader_path);

    /**
     * @brief Compila o shader de vértice e retorna um log de informações.
     * @return Ponteiro para o log de informações da compilação.
     */
    char* compileVertexShader();

    /**
     * @brief Compila o shader de fragmento e retorna um log de informações.
     * @return Ponteiro para o log de informações da compilação.
     */
    char* compileFragmentShader();

    /**
     * @brief Carrega o shader de vértice a partir de um arquivo.
     * @return 0 em caso de sucesso ou um código de erro.
     */
    int loadVertexShader();

    /**
     * @brief Carrega o shader de fragmento a partir de um arquivo.
     * @return 0 em caso de sucesso ou um código de erro.
     */
    int loadFragmentShader();

    /**
     * @brief Obtém o ID do shader de vértice.
     * @return ID do shader de vértice após compilação.
     */
    GLint getVertexShaderID();

    /**
     * @brief Obtém o ID do shader de fragmento.
     * @return ID do shader de fragmento após compilação.
     */
    GLint getFragmentShaderID();

    /**
     * @brief Obtém o conteúdo do shader de vértice como um array de GLchar.
     * @return Ponteiro para o conteúdo do shader de vértice.
     */
    const GLchar* getVertexShaderSource();

    /**
     * @brief Obtém o conteúdo do shader de fragmento como um array de GLchar.
     * @return Ponteiro para o conteúdo do shader de fragmento.
     */
    const GLchar* getFragmentShaderSource();
};

#endif
