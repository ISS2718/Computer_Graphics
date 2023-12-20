#ifndef __MAT_PROJECTION__
#define __MAT_PROJECTION__

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>

#include "Mat4.h"
#include "Vec3.h"

/**
 * @class MatProjection
 * @brief Representa uma classe da matriz Projection perspectiva.
 */
class MatProjection {
private:
    Mat4* perspective; /**< Matriz de projeção perspectiva. */

    float aspect; /**< Aspecto da janela de visualização. (Largura/Altura) */
    float fovy; /**< Angulo do campo de visão em radianos. */
    float z_near; /**< Ponto no eixo Z que plano recorte perto intercepta. */
    float z_far; /**< Ponto no eixo Z que plano recorte longe intercepta. */

    bool update; /**< Flag de update nas matrizes para recalcular a matriz "perspective". */

    /**
     * Atualiza a matriz perspective calculando a partir dos novos parâmetros.
     */
    void updatePerspectiveMatrix();

public:
    /**
     * Construtor da classe MatProjection. Inicializa a matriz perspective como matriz identidade.
     */
    MatProjection();

    /**
     * Construtor da classe MatProjection. Inicializa os parâmetros da perspectiva 
     * e ativa o update da matriz perspective.
     *
     * @param aspect aspecto da janela de visualização. (Largura/Altura).
     * @param fovy angulo do campo de visão em radianos.
     * @param z_near ponto no eixo Z que plano recorte perto intercepta.
     * @param z_far ponto no eixo Z que plano recorte longe intercepta.
     */
    MatProjection(const float &aspect, const float &fovy, const float &z_near, const float &z_far);
    
    /**
     * Destrutor da classe MatProjection. Libera a memória alocada para a matriz prespective.
     */
    ~MatProjection();

    /**
     * Obtém a matriz Projection resultante.
     *
     * @return Um ponteiro para a matriz perscpective.
     */
    GLfloat* getProjectionMatrix();

    /**
     * Define os parâmetros da perspectiva e ativa o update da matriz perspective.
     *
     * @param aspect aspecto da janela de visualização. (Largura/Altura).
     * @param fovy angulo do campo de visão em radianos.
     * @param z_near ponto no eixo Z que plano recorte perto intercepta.
     * @param z_far ponto no eixo Z que plano recorte longe intercepta.
     */
    void setPerspectiveParameters(const float &aspect, const float &fovy, const float &z_near, const float &z_far);

    /**
     * Define o aspecto da janela de visualização. (Largura/Altura).
     *
     * @param aspect aspecto da janela de visualização. (Largura/Altura).
     */
    void setAspect(const float &aspect);

    /**
     * Define o angulo do campo de visão em radianos.
     *
     * @param fovy angulo do campo de visão em radianos.
     */
    void setFovy(const float &fovy);

    /**
     * Define o ponto no eixo Z que plano recorte perto intercepta.
     *
     * @param z_near ponto no eixo Z que plano recorte perto intercepta.
     */
    void setZNear(const float &z_near);

    /**
     * Define o ponto no eixo Z que plano recorte longe intercepta.
     *
     * @param z_far ponto no eixo Z que plano recorte longe intercepta.
     */
    void setZFar(const float &z_far);
};

#endif