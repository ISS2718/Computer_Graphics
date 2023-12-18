#ifndef __MAT_MODEL__
#define __MAT_MODEL__

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include "Mat4.h"

/**
 * @class MatModel
 * @brief Representa uma classe de matrizes de transformações para objetos 2D/3D.
 */
class MatModel {
private:
    Mat4* transformation; /**< Matriz de transformação final (multiplicação de todas). */
    Mat4* translation; /**< Matriz de translação. */
    Mat4* rotationX; /**< Matriz de rotação no eixo X. */
    Mat4* rotationY; /**< Matriz de rotação no eixo Y. */
    Mat4* rotationZ; /**< Matriz de rotação no eixo Z. */
    Mat4* scale; /**< Matriz de escala. */

    bool update; /**< Flag de update nas matrizes para recalcular a matriz "transformation". */

    /**
     * Atualiza a matriz de transformação combinando todas as transformações individuais.
     */
    void updateTransformationMatrix();

public:
    /**
     * Construtor da classe MatModel. Inicializa as matrizes de transformação como matrizes identidade.
     */
    MatModel();

    /**
     * Destrutor da classe MatModel. Libera a memória alocada para as matrizes de transformação.
     */
    ~MatModel();

    /**
     * Obtém a matriz de transformação resultante.
     *
     * @return Um ponteiro para a matriz de transformação.
     */
    GLfloat* getTransformationMatrix();

    /**
     * Define uma rotação nos eixos x, y e z, aplicando as rotações em sequência.
     *
     * @param rx Ângulo de rotação no eixo x.
     * @param ry Ângulo de rotação no eixo y.
     * @param rz Ângulo de rotação no eixo z.
     */
    void setRotation(const float &rx, const float &ry, const float &rz);

    /**
     * Define uma rotação no eixo x.
     *
     * @param r Ângulo de rotação no eixo x.
     */
    void setRotationX(const float &r);

    /**
     * Define uma rotação no eixo y.
     *
     * @param r Ângulo de rotação no eixo y.
     */
    void setRotationY(const float &r);

    /**
     * Define uma rotação no eixo z.
     *
     * @param r Ângulo de rotação no eixo z.
     */
    void setRotationZ(const float &r);

    /**
     * Define uma translação nos eixos x, y e z.
     *
     * @param x Valor de translação no eixo x.
     * @param y Valor de translação no eixo y.
     * @param z Valor de translação no eixo z.
     */
    void setTranslation(const float &x, const float &y, const float &z);

    /**
     * Define uma translação no eixo x.
     *
     * @param x Valor de translação no eixo x.
     */
    void setTranslationX(const float &x);

    /**
     * Define uma translação no eixo y.
     *
     * @param y Valor de translação no eixo y.
     */
    void setTranslationY(const float &y);

    /**
     * Define uma translação no eixo z.
     *
     * @param z Valor de translação no eixo z.
     */
    void setTranslationZ(const float &z);

    /**
     * Define uma escala uniforme nos eixos x, y e z.
     *
     * @param s Valor de escala.
     */
    void setScale(const float &s);

    /**
     * Define uma escala nos eixos x, y e z.
     *
     * @param sx Valor de escala no eixo x.
     * @param sy Valor de escala no eixo y.
     * @param sz Valor de escala no eixo z.
     */
    void setScale(const float &sx, const float &sy, const float &sz);
};

#endif
