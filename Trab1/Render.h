#ifndef __RENDER__
#define __RENDER__

#include <GL/glew.h>  

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <time.h>

#include "stb_image.h"

#include "MatT.h"
#include "OBJ3D.h"
#include "Shader.h"
#include "Texture.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

#define ANGLE_INC 0.1 /**< Macro de definição do incremnto/decremento da rotação*/
#define COORD_INC 0.1 /**< Macro de definição do incremnto/decremento de deslocamento*/
#define INC_SCALE 0.01 /**< Macro de definição do incremnto/decremento da escala*/

#define FRAME_RATE 150.0 /**< Marcro para definição do frame rate máx*/

/**
 * Verifica se pode/deve realizar translações em um objeto 3D.
 * Caso possa realiza essa translação, realiza.
 *
 * @param obj Objeto 3D a ser movido.
 * @param mt_obj Matriz de transformação do objeto.
 * @param actual_coordiante Coordenadas atuais do objeto.
 */
void verifyAndMakeMov(OBJ3D &obj, MatT *mt_obj, Vec3 *actual_coordiante);

/**
 * Verifica se pode/deve ser realizada modificações na escalas em um objeto 3D.
 * Se puder/dever realiza essas modificações.
 *
 * @param obj Objeto 3D a ser escalado.
 * @param mt_obj Matriz de transformação do objeto.
 * @param actual_scale Escala atual do objeto.
 */
void verifyAndMakeScale(OBJ3D &obj, MatT *mt_obj, float *actual_scale);

/**
 * Verifica se pode/deve ser realizada rotações em um objeto 3D.
 *  Se puder/dever realiza essas rotações.
 * 
 * @param obj Objeto 3D a ser rotacionado.
 * @param mt_obj Matriz de transformação do objeto.
 * @param actual_angle Ângulos atuais do objeto.
 */
void verifyAndMakeRotate(OBJ3D &obj, MatT *mt_obj, Vec3 *actual_angle);

/**
 * Verifica se deve modificar a textura.
 * Caso sim, modifica.
 * 
 * @param texture Textura a ser modificada.
 */
void verifyAndModifyTexture(Texture *texture);

/**
 * Configuração inicial do GLFW e criação de janela.
 *
 * @param program Ponteiro para o programa GLSL.
 * @param width Largura da janela.
 * @param heigth Altura da janela.
 * @param title Título da janela.
 * @return Ponteiro para a janela GLFW criada.
 */
GLFWwindow* glfwSetup(GLint *program, GLuint width, GLuint heigth, const char* title);

/**
 * Carrega objetos 3D e suas texturas na memoria principal e na da GPU.
 *
 * @param objetos Array de objetos 3D.
 * @param texturas Array de texturas.
 * @param vertices Vetor de coordenadas de vértices.
 * @param normals Vetor de normais dos vértices.
 * @param uvs Vetor de coordenadas de textura (UV).
 * @param program Programa GLSL.
 * @param buffer Buffer.
 * @return 0 se o carregamento for bem-sucedido, código de erro caso contrário.
 */
int loadObjectAndTexture(OBJ3D *objetos, Texture *texturas, std::vector<Vec3> *vertices, std::vector<Vec3> *normals, std::vector<Vec2> *uvs, GLint *program, GLuint *buffer);

/**
 * Loop principal para renderização e atualização dos objetos.
 *
 * @param window Janela GLFW.
 * @param program Programa GLSL.
 * @param objetos Array de objetos 3D.
 * @param texturas Array de texturas.
 * @param mt_obj Matriz de transformação dos objetos.
 * @param scale_obj Array de escalas dos objetos.
 * @param coord_obj Array de coordenadas dos objetos.
 * @param angle_obj Array de ângulos dos objetos.
 */
void renderLoop(GLFWwindow *window, GLint *program, OBJ3D *objetos, Texture *texturas, MatT *mt_obj, float *scale_obj, Vec3 *coord_obj, Vec3 *angle_obj);

#endif