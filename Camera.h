#ifndef __CAMERA__
#define __CAMERA__

#include "MatProjection.h"
#include "MatView.h"
#include "Vec3.h"

/**
 * @class Camera
 * @brief Representa uma classe de camera com suas matrizes projection e view.
 */
class Camera {
private:
    MatProjection* perspective;
    MatView* view;

    Vec3* camera_coordinates;
    Vec3* camera_target;
    Vec3* camera_view_up;
public:
    /**
     * Construtor da classe Camera. 
     * Inicializa a matriz perspective e view como matrizes identidade.
     * Inicialiaz coordenadas da câmera em (0, 0, 0), target para (0, 0, 0) e view up (0, 0, 0);
     */
    Camera();

    /**
     * Destrutor da classe Camera. Libera a memória alocada para as matrizes e vetores.
     */
    ~Camera();

    /**
     * Obtém a matriz Perspectiva resultante.
     *
     * @return Um ponteiro para a matriz Perspectiva.
     */
    GLfloat* getMatPerspective();

    /**
     * Obtém a matriz View resultante.
     *
     * @return Um ponteiro para a matriz View.
     */
    GLfloat* getMatView();

    /**
     * Obtém as coordenadas atuais da câmera.
     *
     * @return Um vetor tridimensional das coordenadas atuais da Câmera.
     */
    Vec3 getCameraCoordinates();

    /**
     * Obtém as coordenada X atual da câmera.
     * 
     * @return Valor atual da coordenada X da câmera.
     */
    float getCameraCoordinateX();

    /**
     * Obtém as coordenada Y atual da câmera.
     * 
     * @return Valor atual da coordenada Y da câmera.
     */
    float getCameraCoordinateY();

    /**
     * Obtém as coordenada Z atual da câmera.
     * 
     * @return Valor atual da coordenada Z da câmera.
     */
    float getCameraCoordinateZ();

    /**
     * Obtém as coordenadas target atuais da câmera.
     *
     * @return Um vetor tridimensional das coordenadas target atuais da Câmera.
     */
    Vec3 getCameraTarget();

    /**
     * Obtém as coordenada target X atual da câmera.
     * 
     * @return Valor atual da coordenada target X da câmera.
     */
    float getCameraTargetX();

    /**
     * Obtém as coordenada target Y atual da câmera.
     * 
     * @return Valor atual da coordenada target Y da câmera.
     */
    float getCameraTargetY();

    /**
     * Obtém as coordenada target Y atual da câmera.
     * 
     * @return Valor atual da coordenada target Y da câmera.
     */
    float getCameraTargetZ();

    /**
     * Define as coordenadas da câmera.
     *
     * @param x coordenada X da câmera.
     * @param y coordenada Y da câmera.
     * @param z coordenada Z da câmera.
     */
    void setCameraCoordinates(const float &x,const float &y, const float &z);

    /**
     * Define a coordenada X da câmera.
     *
     * @param x coordenada X da câmera.
     */
    void setCameraCoordinateX(const float &x);

    /**
     * Define a coordenada Y da câmera.
     *
     * @param y coordenada Y da câmera.
     */
    void setCameraCoordinateY(const float &y);

    /**
     * Define a coordenada Z da câmera.
     *
     * @param z coordenada Z da câmera.
     */
    void setCameraCoordinateZ(const float &z);

     /**
     * Define as coordenadas target da câmera.
     *
     * @param x coordenada target X da câmera.
     * @param y coordenada target Y da câmera.
     * @param z coordenada target Z da câmera.
     */
    void setCameraTarget(const float &x,const float &y, const float &z);

    /**
     * Define as coordenada target X da câmera.
     *
     * @param x coordenada target X da câmera.
     */
    void setCameraTargetX(const float &x);

    /**
     * Define as coordenada target Y da câmera.
     *
     * @param y coordenada target Y da câmera.
     */
    void setCameraTargetY(const float &y);

    /**
     * Define as coordenada target Z da câmera.
     *
     * @param z coordenada target Z da câmera.
     */
    void setCameraTargetZ(const float &z);
    
    /**
     * Define as coordenadas view up da câmera.
     *
     * @param x coordenada view up X da câmera.
     * @param y coordenada view up Y da câmera.
     * @param z coordenada view up Z da câmera.
     */
    void setCameraViewUp(const float &x,const float &y, const float &z);


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

    /**
     * Define o angulo do campo de visão em radianos.
     * 
     * @param fovy angulo do campo de visão em radianos.
     */
    void setFovy(const float &fovy);

    /**
     * Define o aspecto da janela de visualização. (Largura/Altura). 
     * 
     * @param window_aspect aspecto da janela de visualização. (Largura/Altura).
     */
    void setWindowAspect(const float &window_aspect);
};
#endif