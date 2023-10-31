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

#define ANGLE_INC 0.1
#define COORD_INC 0.1
#define INC_SCALE 0.01


int select_obj = 0;
bool mag_change = false, texture_view = true, 
    uping = false, righting = false, 
    downing = false, lefting = false,
    rotate_x_up = false, rotate_y_up = false, rotate_z_up = false,
    rotate_x_down = false, rotate_y_down = false, rotate_z_down = false,
    scale_update = false;
float scale = 0;

// funcao para processar eventos de teclado
static void key_event(GLFWwindow* window, int key, int scancode, int action, int mods){
    if((key == GLFW_KEY_1 || key == GLFW_KEY_KP_1) && action == GLFW_PRESS) {
        select_obj = 0;
    }

    if((key == GLFW_KEY_2 || key == GLFW_KEY_KP_2) && action == GLFW_PRESS) {
        select_obj = 1;
    }

    if((key == GLFW_KEY_3 || key == GLFW_KEY_KP_3) && action == GLFW_PRESS) {
        select_obj = 2;
    }

    if((key == GLFW_KEY_4 || key == GLFW_KEY_KP_4) && action == GLFW_PRESS) {
        select_obj = 3;
    }

    if((key == GLFW_KEY_5 || key == GLFW_KEY_KP_5) && action == GLFW_PRESS) {
        select_obj = 4;
    }

    if(key == GLFW_KEY_W) {
        uping = true;
    }

    if(key == GLFW_KEY_S) {
        downing = true;
    }

    if(key == GLFW_KEY_D) {
        righting = true;
    }

    if(key == GLFW_KEY_A) {
        lefting = true;
    }

    if(key == GLFW_KEY_UP) {
        rotate_x_up = true;
    }

    if(key == GLFW_KEY_DOWN) {
        rotate_x_down = true;
    }

    if(key == GLFW_KEY_RIGHT && !(mods == GLFW_MOD_SHIFT)) {
        rotate_y_up = true;
    }

    if(key == GLFW_KEY_LEFT && !(mods == GLFW_MOD_SHIFT)) {
        rotate_y_down = true;
    }

    if(key == GLFW_KEY_RIGHT && mods == GLFW_MOD_SHIFT) {
        rotate_z_up = true;
    }

    if(key == GLFW_KEY_LEFT && mods == GLFW_MOD_SHIFT) {
        rotate_z_down = true;
    }

    if(key == GLFW_KEY_P && action == GLFW_PRESS) {
        texture_view = !texture_view;
    }

    if(key == GLFW_KEY_V && action == GLFW_PRESS) {
        mag_change = !mag_change;
    }

    if(key == GLFW_KEY_Z && action == GLFW_PRESS) {
        scale = +INC_SCALE;
        scale_update = true;
    }

    if(key == GLFW_KEY_X && action == GLFW_PRESS) {
        scale = -INC_SCALE;
        scale_update = true;
    }
}

void verifyAndMakeMov(OBJ3D &obj, MatT *mt_obj, Vec3 *actual_coordiante, float scale) {
    if(uping) {
        if(actual_coordiante->getY() < 1) {
            actual_coordiante->setY(actual_coordiante->getY() + COORD_INC);
            mt_obj->setTranslationY(actual_coordiante->getY());
        } else {
            actual_coordiante->setY(-1);
        }
        uping = false;
    }
    
    if(downing) {
        if(actual_coordiante->getY() > -1) {
            actual_coordiante->setY(actual_coordiante->getY() - COORD_INC);
            mt_obj->setTranslationY(actual_coordiante->getY());
        } else {
            actual_coordiante->setY(1);
        }
        downing = false;
    }

    if(righting) {
        if(actual_coordiante->getX() < 1) {
            actual_coordiante->setX(actual_coordiante->getX() + COORD_INC);
            mt_obj->setTranslationX(actual_coordiante->getX());
        } else {
            actual_coordiante->setX(-1);
        }
        righting = false;
    } 

    if(lefting) {
        if(actual_coordiante->getX() > -1) {
            actual_coordiante->setX(actual_coordiante->getX() - COORD_INC);
            mt_obj->setTranslationX(actual_coordiante->getX());
        } else {
            actual_coordiante->setX(1);
        }
        lefting = false;
    }
}

void verifyAndMakeScale(OBJ3D &obj, MatT *mt_obj, float *actual_scale, float scale) {
    if(scale_update) {
        Vec3 max = obj.getMaxVertexCoordinates();
        max *= scale;
        Vec3 min = obj.getMinVertexCoordinates();
        min *= scale;

        if(((max.getX() > -1) && (max.getX() < 1)) && ((min.getX() < 1) && (min.getX() > -1))) {
            if(((max.getX() > -1) && (max.getX() < 1)) && ((min.getX() < 1) && (min.getX() > -1))) {
                *actual_scale = scale;
                mt_obj->setScale(*actual_scale);
            }  
        }    
        scale_update = false;
    }
}

void verifyAndMakeRotate(OBJ3D &obj, MatT *mt_obj, Vec3 *actual_angle) {
    if(rotate_x_up) {
        actual_angle->setX(actual_angle->getX() + ANGLE_INC);
        mt_obj->setRotationX(actual_angle->getX());
        rotate_x_up = false;
    }

    if(rotate_x_down) {
        actual_angle->setX(actual_angle->getX() - ANGLE_INC);
        mt_obj->setRotationX(actual_angle->getX());
        rotate_x_down = false;
    }

    if(rotate_y_up) {
        actual_angle->setY(actual_angle->getY() - ANGLE_INC);
        mt_obj->setRotationY(actual_angle->getY());
         rotate_y_up = false;
    }

    if(rotate_y_down) {
        actual_angle->setY(actual_angle->getY() + ANGLE_INC);
        mt_obj->setRotationY(actual_angle->getY());
        rotate_y_down = false;
    }

    if(rotate_z_up) {
        actual_angle->setZ(actual_angle->getZ() - ANGLE_INC);
        mt_obj->setRotationZ(actual_angle->getZ());
        rotate_z_up = false;
    }

    if(rotate_z_down) {
        actual_angle->setZ(actual_angle->getZ() + ANGLE_INC);
        mt_obj->setRotationZ(actual_angle->getZ());
        rotate_z_down = false;
    }
}

int main(void){
 
    // inicicializando o sistema de\ janelas
    glfwInit();

    // deixando a janela invisivel, por enquanto
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

 
    // criando uma janela
    GLFWwindow* window = glfwCreateWindow(800, 800, "Wavefront", NULL, NULL);

    
    // tornando a janela como principal 
    glfwMakeContextCurrent(window);

    // inicializando Glew (para lidar com funcoes OpenGL)
    GLint GlewInitResult = glewInit();
    printf("GlewStatus: %s\n", glewGetErrorString(GlewInitResult));

    // Requisitando slot para a GPU para nossos programas Vertex e Fragment Shaders
    GLuint program = glCreateProgram();
    
    Shader s("./texture.vert", "./texture.frag");

    // Carregando Vertex Shadder
    if(s.loadVertexShader() != 0) {
        std::cout << "Vertex Shader não encontrado" << std::endl;
        return -1;
    }

    // Compilando o Vertex Shader e verificando erros
    char *info = s.compileVertexShader();
    if(info != nullptr) {
        std::cout << "Erro de compilacao no Vertex Shader." << std::endl;
        std::cout<< "\t--> " << info << std::endl;
    }

    // Carregando Fragment Shadder
    if(s.loadFragmentShader() != 0) {
        std::cout << "Vertex Shader não encontrado" << std::endl;
        return -1;
    }

    // Compilando o Fragment Shader e verificando erros
    info = s.compileFragmentShader();
    if(info != nullptr) {
        std::cout << "Erro de compilacao no Fragment Shader." << std::endl;
        std::cout<< "\t--> " << info << std::endl;
    }

    // Associando os programas compilado ao programa principal
    glAttachShader(program, s.getVertexShaderID());
    glAttachShader(program, s.getFragmentShaderID());

    // Linkagem do programa e definindo como default
    glLinkProgram(program);
    glUseProgram(program);

    // Criando as texturas;
    OBJ3D objetos[5] {
        OBJ3D("./objetos/RumikCube.obj", GL_QUADS),
        OBJ3D("./objetos/cabana.obj", GL_TRIANGLES),
        OBJ3D("./objetos/monstro.obj", GL_TRIANGLES),
        OBJ3D("./objetos/torre.obj", GL_TRIANGLES),
        OBJ3D("./objetos/cranio.obj", GL_TRIANGLES),
    };

    // Criando as texturas;
    Texture texturas[5] {
        Texture("./objetos/RumikCubeTexture.jpg"),
        Texture("./objetos/cabana.jpg"),
        Texture("./objetos/monstro.jpg"),
        Texture("./objetos/torre.jpg"),
        Texture("./objetos/cranio.jpg"),
    };

    // Carregando texturas
    for(int i = 0; i < 5; i++) {
        texturas[i].setMagFilterType(GL_LINEAR);
        texturas[i].setMinFilterType(GL_LINEAR);
        texturas[i].setWrapSType(GL_REPEAT);
        texturas[i].setWrapTType(GL_REPEAT);

        int r = texturas[i].loadTexture();
        if(r == -1) {
            std::cout << "Textura " << i << ": texture_path é nulo!!!" << std::endl;
        } else if(r == -2) {
            std::cout << "Textura " << i << ": Não foi possível carregar imgaem!!!" << std::endl;
        }
    }

    // Preparando dados para enviar a GPU
    std::vector<Vec3> vertices;
    std::vector<Vec3> normals;
    std::vector<Vec2> uvs;

    // Carregando objetos
    for(int i = 0; i < 5; i++) {
        int r = objetos[i].loadOBJ3D(&vertices, &uvs, &normals);
        if(r == -1) {
            std::cout << "Objeto " << i << ": Arquivo não encontrado!" << std::endl;
            return r;
        } else if(r == -2) {
            std::cout << "Objeto " << i << ": Não é composto por triangulos" << std::endl;
            return r;
        }  else if(r == -3) {
            std::cout << "Objeto " << i << ": Não é composto por quadrados" << std::endl;
            return r;
        }
    }

    GLuint buffer[2];
    glGenBuffers(2, buffer);

    // Abaixo, nós enviamos todo o conteúdo da variável vertices.
    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vec3), &vertices[0], GL_STATIC_DRAW);

    // Associando variáveis do programa GLSL (Vertex Shaders) com nossos dados
    GLint loc_positon = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(loc_positon);
    glVertexAttribPointer(loc_positon, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), (void*) 0); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml
    

    // Abaixo, nós enviamos todo o conteúdo da variável uvs.
    glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(Vec2), &uvs[0], GL_STATIC_DRAW);

    // Associando variáveis do programa GLSL (Vertex Shaders) com nossos dados
    GLint loc_texture_coord = glGetAttribLocation(program, "texture_coord");
    glEnableVertexAttribArray(loc_texture_coord);
    glVertexAttribPointer(loc_texture_coord, 2, GL_FLOAT, GL_FALSE, sizeof(Vec2), (void*) 0); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml

    // Associando nossa janela com eventos de teclado
    glfwSetKeyCallback(window, key_event); // teclado

    // Exibindo nossa janela
    glfwShowWindow(window);

    glEnable(GL_DEPTH_TEST);// ### importante para 3D

    MatT mt_obj[5];
    bool mag_change_update = false;
    float scale_obj[5] = {0.05, 0.01, 0.1, 0.1, 0.03};
    Vec3 coord_obj[5] = {Vec3(0), Vec3(0), Vec3(0), Vec3(0), Vec3(0)};
    Vec3 angle_obj[5] = {Vec3(0), Vec3(0), Vec3(0), Vec3(0), Vec3(0)};

    for(int i = 0; i < 5; i++) {
        mt_obj[i].setScale(scale_obj[i]);
        mt_obj[i].setTranslation(coord_obj[i].getX(), coord_obj[i].getY(), coord_obj[i].getZ());
        mt_obj[i].setRotation(angle_obj[i].getX(), angle_obj[i].getY(), angle_obj[i].getZ());
    }

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0, 1.0, 1.0, 1.0);

      
        verifyAndMakeScale(objetos[select_obj], &mt_obj[select_obj], &scale_obj[select_obj], (scale_obj[select_obj] + scale));

        verifyAndMakeMov(objetos[select_obj], &mt_obj[select_obj], &coord_obj[select_obj], scale_obj[select_obj]);
        verifyAndMakeRotate(objetos[select_obj], &mt_obj[select_obj], &angle_obj[select_obj]);

        // enviando a matriz de transformacao para a GPU
        GLuint loc_mat_transformation = glGetUniformLocation(program, "mat_transformation");
        glUniformMatrix4fv(loc_mat_transformation, 1, GL_TRUE, mt_obj[select_obj].getTransformationMatrix());
        
        if(mag_change && mag_change != mag_change_update) {
            texturas[select_obj].setMagFilterType(GL_NEAREST).updateTextureParamters();
            mag_change_update = mag_change;
        } else if(!mag_change && mag_change != mag_change_update) {
            texturas[select_obj].setMagFilterType(GL_LINEAR).updateTextureParamters();
            mag_change_update = mag_change;
        }

        if(texture_view) {
            glBindTexture(GL_TEXTURE_2D, texturas[select_obj].getTextureID());
        } else {
            glBindTexture(GL_TEXTURE_2D, 0);
        }
            
        glDrawArrays(objetos[select_obj].getTypeRender(), objetos[select_obj].getVertexStart(), objetos[select_obj].getVertexSize());

        glfwSwapBuffers(window);   
    }
 
    glfwDestroyWindow(window);
 
    glfwTerminate();
    exit(EXIT_SUCCESS);
}