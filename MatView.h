#ifndef __MAT_VIEW__
#define __MAT_VIEW__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Mat4.h"
#include "Vec3.h"

/**
 * @class MatView
 * @brief Representa uma classe da matriz View.
 */
class MatView {
private:
    Mat4* view; /**< Matriz de view. */

    Mat4* rotation; /**< Matriz de rotação. */
    Mat4* translation; /**< Matriz de translação. */

    Vec3 *n; /**< Vetor 'n' ou vetor normal: Representa a direção para a qual a câmera está apontando. */
    Vec3 *u; /**< Vetor 'u': Representa a direção "direita" do plano da câmera. */
    Vec3 *v; /**< Vetor 'v': Representa a direção "acima" do plano da câmera. */

    bool update; /**< Flag de update nas matrizes para recalcular a matriz "view". */

    /**
     * Atualiza a matriz view multiplicando a matriz de rotação e translação.
     */
    void updateViewMatrix();

public:
    /**
     * Construtor da classe MatView. Inicializa as matrizes como matrizes identidade.
     */
    MatView();

    /**
     * Construtor da classe MatView. Inicializa a matriz view, calcula as matrizes de rotação e translação, 
     * e ativa o update da matriz View.
     *
     * @param eye_position coordenadas da posição do olho/câmera.
     * @param target coordenadas da direção observada pelo olho/câmera.
     * @param view_up coordenadas da orientação (qual lado tá pra cima) do olho/câmera.
     */
    MatView(Vec3 &eye_position, Vec3 &target, Vec3 &view_up);

    /**
     * Destrutor da classe MatView. Libera a memória alocada para as matrizes e vetores.
     */
    ~MatView();

    /**
     * Obtém a matriz View resultante.
     *
     * @return Um ponteiro para a matriz view.
     */
    GLfloat* getViewMatrix();

    /**
     * Calcula as matrizes de translação e rotação da matriz View.
     */
    void setViewCoordinates(Vec3 &eye_position, Vec3 &target, Vec3 &view_up);
};

#endif