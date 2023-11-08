#ifndef __OBJ3D__
#define __OBJ3D__

#include <iostream>
#include <ios>
#include <istream>
#include <fstream>
#include <limits>
#include <vector>
#include <string>
#include <GLFW/glfw3.h>

#include "Vec2.h"
#include "Vec3.h"

#define SIZE_LINE 256 /**< Tamanho máximo da linha a ser lida a partir de arquivos durante o processamento do formato .obj. */

/**
 * @class OBJ3D
 * @brief Classe para abrir, ler e salvar objetos 2D/3D de arquivos Wavefront (.obj).
 *
 * A classe OBJ3D permite abrir, ler e salvar objetos 2D/3D de arquivos Wavefront (.obj) e extrair informações como coordenadas de vértices, texturas e normais.
 */
class OBJ3D {
private:
    std::string* obj_path; /**< Caminho do arquivo .obj a ser carregado. */
    
    int vertex_start; /**< Índice de início dos vértices no vetor de saída. */
    int vertex_end; /**< Índice de término dos vértices no vetor de saída. */
    int vertex_size; /**< Tamanho do vetor de vértices. */
    
    int uvs_start; /**< Índice de início das coordenadas de textura (UVs) no vetor de saída. */
    int uvs_end;/**< Índice de término das coordenadas de textura (UVs) no vetor de saída. */
    int uvs_size; /**< Tamanho do vetor de coordenadas de textura (UVs). */
    
    int normals_start; /**< Índice de início das coordenadas normais no vetor de saída. */
    int normals_end; /**< Índice de término das coordenadas normais no vetor de saída. */
    int normals_size; /**< Tamanho do vetor de coordenadas normais. */

    int type_render; /**< Tipo de renderização, como GL_TRIANGLES, GL_QUADS, etc. */
    
    Vec3 max_vertex_coordinates; /**< Coordenadas máximas dos vértices. */
    
    Vec3 min_vertex_coordinates; /**< Coordenadas mínimas dos vértices. */

    /**
     * Lê as faces compostas por triângulos de uma linha no formato .obj e extrai os índices dos vértices, coordenadas de textura e normais, se disponíveis.
     * @param line A linha contendo informações sobre as faces.
     * @param vertexIndices Um vetor para armazenar os índices dos vértices.
     * @param uvsIndices Um vetor para armazenar os índices das coordenadas de textura (UVs).
     * @param normalsIndices Um vetor para armazenar os índices dos vetores normais, se disponíveis.
     * @param have_normal Um indicador booleano que indica se as faces têm vetores normais ou não.
     * @return 0 se a leitura for bem-sucedida, -1 se ocorrer um erro na leitura.
     */
    int loadOBJ3D_TRIANGLES(char* line, std::vector<unsigned int> *vertexIndices, std::vector<unsigned int> *uvsIndices, std::vector<unsigned int> *normalsIndices, bool *have_normal);

    /**
     * Lê as faces compostas por quadrados de uma linha no formato .obj e extrai os índices dos vértices, coordenadas de textura e normais, se disponíveis.
     * @param line A linha contendo informações sobre as faces.
     * @param vertexIndices Um vetor para armazenar os índices dos vértices.
     * @param uvsIndices Um vetor para armazenar os índices das coordenadas de textura (UVs).
     * @param normalsIndices Um vetor para armazenar os índices dos vetores normais, se disponíveis.
     * @param have_normal Um indicador booleano que indica se as faces têm vetores normais ou não.
     * @return 0 se a leitura for bem-sucedida, -1 se ocorrer um erro na leitura.
     */
    int loadOBJ3D_QUADS(char* line, std::vector<unsigned int> *vertexIndices, std::vector<unsigned int> *uvsIndices, std::vector<unsigned int> *normalsIndices, bool *have_normal);

    /**
     * Atualiza as coordenadas máximas e mínimas do objeto com base nos valores de x, y e z fornecidos.
     * @param x A coordenada x a ser verificada.
     * @param y A coordenada y a ser verificada.
     * @param z A coordenada z a ser verificada.
     */
    void updateMaxMinCoordinates(float x, float y, float z);

public:
    /**
     * Construtor padrão da classe OBJ3D.
     */
    OBJ3D();

    /**
     * Cria uma instância de OBJ3D com um caminho de arquivo .obj e um tipo de renderização específico.
     * @param obj_path Caminho do arquivo .obj.
     * @param type_render Tipo de renderização, como GL_TRIANGLES, GL_QUADS, etc.
     */
    OBJ3D(std::string obj_path, int type_render);

    /**
     * Cria uma instância de OBJ3D com um caminho de arquivo .obj e um tipo de renderização específico.
     * @param obj_path Caminho do arquivo .obj.
     * @param type_render Tipo de renderização, como GL_TRIANGLES, GL_QUADS, etc.
     */
    OBJ3D(const char* obj_path, int type_render);

    /**
     * Destrutor da classe OBJ3D.
     */
    ~OBJ3D();

    /**
     * Obtém o tipo de renderização.
     * @return Tipo de renderização, como GL_TRIANGLES, GL_QUADS, etc.
     */
    int getTypeRender();

    /**
     * Obtém o índice de início dos vértices no vetor de saída.
     * @return O índice de início dos vértices no vetor de saída.
     */
    int getVertexStart();

    /**
     * Obtém o índice de término dos vértices no vetor de saída.
     * @return O índice de término dos vértices no vetor de saída.
     */
    int getVertexEnd();

    /**
     * Obtém o tamanho do vetor de vértices.
     * @return O tamanho do vetor de vértices.
     */
    int getVertexSize();

    /**
     * Obtém o índice de início das coordenadas de textura (UVs) no vetor de saída.
     * @return O índice de início das coordenadas de textura (UVs) no vetor de saída.
     */
    int getUVSStart();

    /**
     * Obtém o índice de término das coordenadas de textura (UVs) no vetor de saída.
     * @return O índice de término das coordenadas de textura (UVs) no vetor de saída.
     */
    int getUVSEnd();

    /**
     * Obtém o tamanho do vetor de coordenadas de textura (UVs).
     * @return O tamanho do vetor de coordenadas de textura (UVs).
     */
    int getUVSSize();

    /**
     * Obtém o índice de início das coordenadas normais no vetor de saída.
     * @return O índice de início das coordenadas normais no vetor de saída.
     */
    int getNormalsStart();

    /**
     * Obtém o índice de término das coordenadas normais no vetor de saída.
     * @return O índice de término das coordenadas normais no vetor de saída.
     */
    int getNormalsEnd();

    /**
     * Obtém o tamanho do vetor de coordenadas normais.
     * @return O tamanho do vetor de coordenadas normais.
     */
    int getNormalsSize();

    /**
     * Obtém as coordenadas máximas dos vértices.
     * @return As coordenadas máximas dos vértices.
     */
    Vec3 getMaxVertexCoordinates();

    /**
     * Obtém as coordenadas mínimas dos vértices.
     * @return As coordenadas mínimas dos vértices.
     */
    Vec3 getMinVertexCoordinates();

    /**
     * Define o tipo de renderização.
     * @param type_render Tipo de renderização, como GL_TRIANGLES, GL_QUADS, etc.
     * @return Referência para a instância de OBJ3D atualizada.
     */
    OBJ3D& setTypeRender(int type_render);

    /**
     * Define o caminho do arquivo .obj a ser carregado.
     * @param obj_path Caminho do arquivo .obj.
     * @return Referência para a instância de OBJ3D atualizada.
     */
    OBJ3D& setTypeObjPath(std::string obj_path);

    /**
     * Carrega um arquivo .obj e extrai informações de vértices, coordenadas de textura e coordenadas normais.
     * @param out_vertex Vetor de saída para as coordenadas de vértices.
     * @param out_uvs Vetor de saída para as coordenadas de textura (UVs).
     * @param out_normals Vetor de saída para as coordenadas normais.
     * @return 0 se a operação for bem-sucedida, um valor negativo em caso de erro.
     */
    int loadOBJ3D(std::vector<Vec3> *out_vertex, std::vector<Vec2> *out_uvs, std::vector<Vec3> *out_normals);

    /**
     * Sobrecarga do operador de atribuição para copiar os valores de outra instância de OBJ3D.
     * @param v A instância de OBJ3D a ser copiada.
     * @return Uma referência para a instância de OBJ3D atualizada.
     */
    OBJ3D& operator=(const OBJ3D& v);
};

#endif
