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
#include "Render.h"
#include "Shader.h"
#include "Texture.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

int main(void){
    // Vetores para enviar dados para enviar a GPU
    std::vector<Vec3> vertices;
    std::vector<Vec3> normals;
    std::vector<Vec2> uvs;

    // Criando as objetos
    OBJ3D objetos[5] {
        OBJ3D("./objetos/RumikCube.obj", GL_QUADS),
        OBJ3D("./objetos/casa.obj", GL_TRIANGLES),
        OBJ3D("./objetos/espada.obj", GL_QUADS),
        OBJ3D("./objetos/torre.obj", GL_TRIANGLES),
        OBJ3D("./objetos/cranio.obj", GL_TRIANGLES),
    };

    // Criando as texturas
    Texture texturas[5] {
        Texture("./objetos/RumikCubeTexture.jpg"),
        Texture("./objetos/casa.png"),
        Texture("./objetos/espada.png"),
        Texture("./objetos/torre.jpg"),
        Texture("./objetos/cranio.jpg"),
    };

    // Criando escala iniciais dos objetos
    float scale_obj[5] = {0.05, 0.1, 0.02, 0.1, 0.03};
    // criando coordenadas iniciais dos objetos
    Vec3 coord_obj[5] = {Vec3(0), Vec3(0), Vec3(0), Vec3(0), Vec3(0)};
    // criando angulos iniciais dos objetos
    Vec3 angle_obj[5] = {Vec3(0), Vec3(0), Vec3(0), Vec3(0), Vec3(0)};

    // Criando matrizes de transformação
    MatT mt_obj[5];
    // Configurando as matrizes de transformação com os parâmetros iniciais
    for(int i = 0; i < 5; i++) {
        mt_obj[i].setScale(scale_obj[i]);
        mt_obj[i].setTranslation(coord_obj[i].getX(), coord_obj[i].getY(), coord_obj[i].getZ());
        mt_obj[i].setRotation(angle_obj[i].getX(), angle_obj[i].getY(), angle_obj[i].getZ());
    }
    // ID de programa de Shaders
    GLint program;

    // Cria e configura a janela
    GLFWwindow *window = glfwSetup(&program, 800, 800, "Trabalho 1");

    // Buffer de vertices e de vertices de textura
    GLuint buffer[2];

    // carrega todos os objetos e texturas e envia para GPU
    if(loadObjectAndTexture(objetos, texturas, &vertices, &normals, &uvs, &program, buffer) != 0) {
        exit(EXIT_FAILURE);
    }

    // Exibindo nossa janela
    glfwShowWindow(window);

    // Entra no LOOP de renderização e atualização dos objetos
    renderLoop(window, &program, objetos, texturas, mt_obj, scale_obj, coord_obj, angle_obj);

    // Destroi a janela e encerra o GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    exit(EXIT_SUCCESS);
}