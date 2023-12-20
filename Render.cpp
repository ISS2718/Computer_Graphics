#include "Render.h"

int select_obj = 0; /**< Variável Global para seleção de objetos*/

bool mag_change = false; /**< Variável Global para troca de filtro de magnificação de texturas*/
bool mag_change_update = false; /**< /**< Variável Global identificação de troca de estado da variável mag_change*/

bool texture_view = true; /**< Variável Global para habilitar ou desabilitar as texturas*/

bool uping = false; /**< Variável Global para movimentar objeto para cima*/
bool righting = false; /**< Variável Global para movimentar objeto para baixo*/
bool downing = false; /**< Variável Global para movimentar objeto para direita*/
bool lefting = false; /**< Variável Global para movimentar objeto para esquerda*/

bool rotate_x_up = false; /**< Variável Global para rotacionar objeto no eixo X positivamente*/
bool rotate_y_up = false; /**< Variável Global para rotacionar objeto no eixo Y positivamente*/
bool rotate_z_up = false; /**< Variável Global para rotacionar objeto no eixo Z positivamente*/
bool rotate_x_down = false; /**< Variável Global para rotacionar objeto no eixo X negativamente*/
bool rotate_y_down = false; /**< Variável Global para rotacionar objeto no eixo Y negativamente*/
bool rotate_z_down = false; /**< Variável Global para rotacionar objeto no eixo Z negativamente*/

bool scale_up = false; /**< Variável Global para aumentar a escala do objeto*/
bool scale_down = false; /**< Variável Global para diminuir a escala do objeto*/

/**
 * Função para processar eventos de teclado.
 *
 * @param window Janela GLFW
 * @param key Código da tecla pressionada
 * @param scancode Código da tecla scancode
 * @param action Ação do teclado (GLFW_PRESS, GLFW_RELEASE)
 * @param mods Modificadores (como Shift)
 */
static void key_event(GLFWwindow* window, int key, int scancode, int action, int mods) {
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
        scale_up = true;
    }

    if(key == GLFW_KEY_X && action == GLFW_PRESS) {
        scale_down = true;
    }
}

void verifyAndMakeMov(OBJ3D &obj, MatModel *mt_obj, Vec3 *actual_coordiante) {
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

void verifyAndMakeScale(OBJ3D &obj, MatModel *mt_obj, float *actual_scale) {
    Vec3 max = obj.getMaxVertexCoordinates();
    Vec3 min = obj.getMinVertexCoordinates();
    if(scale_up) {
        max *= (*actual_scale + INC_SCALE);
        min *= (*actual_scale + INC_SCALE);

        if(((max.getX() >= -1) && (max.getX() <= 1)) && ((min.getX() <= 1) && (min.getX() >= -1))) {
            if(((max.getY() >= -1) && (max.getY() <= 1)) && ((min.getY() <= 1) && (min.getY() >= -1))) {
                *actual_scale += INC_SCALE;
                mt_obj->setScale(*actual_scale);
            }  
        }    
        scale_up = false;
    }

    if(scale_down) {
        float scale = (*actual_scale - INC_SCALE);
        if(scale <= 0) {
            scale = 0;
        }
        max *= scale;
        min *= scale;

        if(((max.getX() >= -1) && (max.getX() <= 1)) && ((min.getX() <= 1) && (min.getX() >= -1))) {
            if(((max.getY() >= -1) && (max.getY() <= 1)) && ((min.getY() <= 1) && (min.getY() >= -1))) {
                *actual_scale = scale;
                mt_obj->setScale(scale);
            }  
        }    
        scale_down = false;
    }
}

void verifyAndMakeRotate(OBJ3D &obj, MatModel *mt_obj, Vec3 *actual_angle) {
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

void verifyAndModifyTexture(Texture *texture) {
        if(mag_change && mag_change != mag_change_update) {
            texture->setMagFilterType(GL_NEAREST).updateTextureParamters();
            mag_change_update = mag_change;
        } else if(!mag_change && mag_change != mag_change_update) {
            texture->setMagFilterType(GL_LINEAR).updateTextureParamters();
            mag_change_update = mag_change;
        }

        if(texture_view) {
            glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        } else {
            glBindTexture(GL_TEXTURE_2D, 0);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
}

GLFWwindow* glfwSetup(GLint *program, GLuint width, GLuint heigth, const char* title) {
    // inicicializando o sistema de\ janelas
    glfwInit();

    // deixando a janela invisivel, por enquanto
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

 
    // criando uma janela
    GLFWwindow *window = glfwCreateWindow(width, heigth, title, NULL, NULL);

    
    // tornando a janela como principal 
    glfwMakeContextCurrent(window);

    // inicializando Glew (para lidar com funcoes OpenGL)
    GLint GlewInitResult = glewInit();
    printf("GlewStatus: %s\n", glewGetErrorString(GlewInitResult));

    // Requisitando slot para a GPU para nossos programas Vertex e Fragment Shaders
    *program = glCreateProgram();
    
    Shader s("./texture.vert", "./texture.frag");

    // Carregando Vertex Shadder
    if(s.loadVertexShader() != 0) {
        std::cout << "Vertex Shader não encontrado" << std::endl;
        return nullptr;
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
        return  nullptr;
    }

    // Compilando o Fragment Shader e verificando erros
    info = s.compileFragmentShader();
    if(info != nullptr) {
        std::cout << "Erro de compilacao no Fragment Shader." << std::endl;
        std::cout<< "\t--> " << info << std::endl;
    }

    // Associando os programas compilado ao programa principal
    glAttachShader(*program, s.getVertexShaderID());
    glAttachShader(*program, s.getFragmentShaderID());

    // Linkagem do programa e definindo como default
    glLinkProgram(*program);
    glUseProgram(*program);

    // Associando nossa janela com eventos de teclado
    glfwSetKeyCallback(window, key_event); // teclado

    glEnable(GL_DEPTH_TEST);// ### importante para 3D

    return window;
}

int loadObjectAndTexture(OBJ3D *objetos, Texture *texturas, std::vector<Vec3> *vertices, std::vector<Vec3> *normals, std::vector<Vec2> *uvs, GLint *program, GLuint *buffer) {
    // Carregando texturas
    for(int i = 0; i < 5; i++) {
        texturas[i].setMagFilterType(GL_LINEAR);
        texturas[i].setMinFilterType(GL_LINEAR);
        texturas[i].setWrapSType(GL_REPEAT);
        texturas[i].setWrapTType(GL_REPEAT);

        int r = texturas[i].loadTexture();
        if(r == -1) {
            std::cout << "Textura " << i << ": texture_path é nulo!!!" << std::endl;
            return r;
        } else if(r == -2) {
            std::cout << "Textura " << i << ": Não foi possível carregar imgaem!!!" << std::endl;
            return r;
        }
    }

    // Carregando objetos
    for(int i = 0; i < 5; i++) {
        int r = objetos[i].loadOBJ3D(vertices, uvs, normals);
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

    glGenBuffers(2, buffer);

    // Abaixo, nós enviamos todo o conteúdo da variável vertices.
    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(Vec3), &((*vertices)[0]), GL_STATIC_DRAW);

    // Associando variáveis do programa GLSL (Vertex Shaders) com nossos dados
    GLint loc_positon = glGetAttribLocation(*program, "position");
    glEnableVertexAttribArray(loc_positon);
    glVertexAttribPointer(loc_positon, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), (void*) 0);
    

    // Abaixo, nós enviamos todo o conteúdo da variável uvs.
    glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
    glBufferData(GL_ARRAY_BUFFER, uvs->size() * sizeof(Vec2), &((*uvs)[0]), GL_STATIC_DRAW);

    // Associando variáveis do programa GLSL (Vertex Shaders) com nossos dados
    GLint loc_texture_coord = glGetAttribLocation(*program, "texture_coord");
    glEnableVertexAttribArray(loc_texture_coord);
    glVertexAttribPointer(loc_texture_coord, 2, GL_FLOAT, GL_FALSE, sizeof(Vec2), (void*) 0);
    
    return 0;
}

void renderLoop(GLFWwindow *window, GLint *program, OBJ3D *objetos, Texture *texturas, MatModel *mt_obj, float *scale_obj, Vec3 *coord_obj, Vec3 *angle_obj) {
    while (!glfwWindowShouldClose(window)) {
        // Verifique o tempo no início do quadro
        double frameStart = glfwGetTime();

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0, 1.0, 1.0, 1.0);

      
        verifyAndMakeScale(objetos[select_obj], &mt_obj[select_obj], &scale_obj[select_obj]);

        verifyAndMakeMov(objetos[select_obj], &mt_obj[select_obj], &coord_obj[select_obj]);
        verifyAndMakeRotate(objetos[select_obj], &mt_obj[select_obj], &angle_obj[select_obj]);

        // enviando a matriz de transformacao para a GPU
        GLuint loc_mat_transformation = glGetUniformLocation(*program, "mat_transformation");
        glUniformMatrix4fv(loc_mat_transformation, 1, GL_TRUE, mt_obj[select_obj].getModelMatrix());
        
        verifyAndModifyTexture(&(texturas[select_obj]));
            
        glDrawArrays(objetos[select_obj].getTypeRender(), objetos[select_obj].getVertexStart(), objetos[select_obj].getVertexSize());

        glfwSwapBuffers(window);

        // Verifique o tempo no final do quadro
        double frameEnd = glfwGetTime();

        // Calcule o tempo gasto no quadro atual
        double frameTime = frameEnd - frameStart;

        // Se o tempo gasto for menor que 1/144 segundos (aproximadamente 6.94 ms),
        // espere o tempo restante para atingir 1/144 segundos.
        double targetFrameTime = 1.0 / FRAME_RATE;
        if (frameTime < targetFrameTime) {
            double sleepTime = targetFrameTime - frameTime;
            glfwSetTime(0.0);  // Redefina o tempo para medir a espera
            while (glfwGetTime() < sleepTime) {
                // Aguarde até atingir o tempo alvo
            }
        }   
    }
}
