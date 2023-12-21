#include <GL/glew.h>  

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <time.h>

#include <glm/matrix.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "stb_image.h"

#include "MatModel.h"
#include "Camera.h"
#include "OBJ3D.h"
#include "Shader.h"
#include "Texture.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

#define QUANTIDADE_OBJS 7
#define TEXTURE_PATH "./OBJ/obj/textures/caixa.jpg"


int altura = 1000;
int largura = 1000;

float deltaTime = 0.0f;	//Tempo entre o ultimo frame e o atual. Usado para obter uma movimentacao mais "suave" da camera pelo cenario
float lastFrame = 0.0f; //Tempo do ultimo frame 

glm::vec3 cameraFront(0, 0, 1); //Variavel global para matriz View


//Variaveis globais de controle de tecla
bool stop = false;          //Caso a tecla para fechar o programa seja apertada
bool polygonMode = false;   //Caso a tecla para modo poligono seja apertada
bool W = false;             //Caso a tecla W seja apertada
bool A = false;             //Caso a tecla A seja apertada
bool S = false;             //Caso a tecla S seja apertada
bool D = false;             //Caso a tecla D seja apertada

int select_light = 0; // seleciona a luz a ser utilizada

//Funcao de callback para eventos de teclado
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if((key == GLFW_KEY_1 || key == GLFW_KEY_KP_1) && action == GLFW_PRESS) {
        select_light = 0;
    }

    if((key == GLFW_KEY_2 || key == GLFW_KEY_KP_2) && action == GLFW_PRESS) {
        select_light = 1;
    }

    if((key == GLFW_KEY_3 || key == GLFW_KEY_KP_3) && action == GLFW_PRESS) {
        select_light = 2;
    }

    if((key == GLFW_KEY_4 || key == GLFW_KEY_KP_4) && action == GLFW_PRESS) {
        select_light = 3;
    }

    if((key == GLFW_KEY_5 || key == GLFW_KEY_KP_5) && action == GLFW_PRESS) {
        select_light = 4;
    }
    if(key == 87 && (action==1 || action==2)){ //Se tecla W apertada
        W = true;
    }
    if(key == 83 && (action==1 || action==2)){ //Se tecla S apertada
        S = true;
    }
    if(key == 65 && (action==1 || action==2)){ //Se tecla A apertada
        A = true;    
    }
    if(key == 68 && (action==1 || action==2)){ //Se tecla D apertada
        D = true;
    }
    if(key == GLFW_KEY_ESCAPE) //Se tecla Q apertada, entao diz que o programa deve ser fechado
        stop = true;
    if(key == GLFW_KEY_P && (action==1 || action==2)){ //Se tecla P apertada, entao ativara/desativara o modo poligono
        polygonMode = !polygonMode;
    }
}

//Variaveis globais para controle do uso do mouse
float yaw =  -90.0;         
float pitch = 0.0;
float lastX = largura/2;
float lastY = altura/2;

//Funcao que realiza a leitura dos valores do mouse e obtem para onde a camera deve ser apontada
void cursor_position_update(GLFWwindow* window){
    double xpos, ypos;
    glfwGetCursorPos(window,&xpos,&ypos);       //Pega a posicao atual do cursor na tela
    glfwSetCursorPos(window, 500.0, 500.0);     //Muda a posicao do cursor para o centro da tela para a proxima chamada da funcao
    
    float xoffset = xpos - 500;     //Calcula quanto o mouse foi mexido em X desde a ultima chamada da funcao
    float yoffset = 500 - ypos;     //Calcula quanto o mouse foi mexido em Y desde a ultima chamada da funcao, invertido

    float sensitivity = 2.5f;              //Sensibilidade da camera
    xoffset *= sensitivity * deltaTime;    //Calcula o quanto o angulo da camera em X foi alterado 
    yoffset *= sensitivity * deltaTime;    //Calcula o quanto o angulo da camera em Y foi alterado

    yaw += xoffset;     //Calcula o angulo atual da camera em X
    pitch += yoffset;   //Calcula o angulo atual da camera em Y

    
    if (pitch >= 89.9) pitch = 89.9;    //Define limites para o angulo da camera em Y
    if (pitch <= -89.9) pitch = -89.9;

    //Com base nos angulos da camera em X e Y calcula o ponto para o qual a camera esta olhando
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

int main(void){
 
    // inicicializando o sistema de\ janelas
    glfwInit();

    // deixando a janela invisivel, por enquanto
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

 
    // criando uma janela
    GLFWwindow* window = glfwCreateWindow(largura, altura, "Wavefront", NULL, NULL);

    
    // tornando a janela como principal 
    glfwMakeContextCurrent(window);

    // inicializando Glew (para lidar com funcoes OpenGL)
    GLint GlewInitResult = glewInit();
    printf("GlewStatus: %s\n", glewGetErrorString(GlewInitResult));

    glfwSetKeyCallback(window, key_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);    //Ativa o modo sem cursor do mouse

    // Requisitando slot para a GPU para nossos programas Vertex e Fragment Shaders
    GLuint program = glCreateProgram();
    
    Shader s("./ilumination.vert", "./ilumination.frag");

    // Carregando Vertex Shadder
    if(s.loadVertexShader() != 0) {
        std::cout << "Vertex Shader não encontrado" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Compilando o Vertex Shader e verificando erros
    char *info = s.compileVertexShader();
    if(info != nullptr) {
        std::cout << "Erro de compilacao no Vertex Shader." << std::endl;
        std::cout<< "\t--> " << info << std::endl;
        exit(EXIT_FAILURE);
    }

    // Carregando Fragment Shadder
    if(s.loadFragmentShader() != 0) {
        std::cout << "Vertex Shader não encontrado" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Compilando o Fragment Shader e verificando erros
    info = s.compileFragmentShader();
    if(info != nullptr) {
        std::cout << "Erro de compilacao no Fragment Shader." << std::endl;
        std::cout<< "\t--> " << info << std::endl;
        exit(EXIT_FAILURE);
    }

    // Associando os programas compilado ao programa principal
    glAttachShader(program, s.getVertexShaderID());
    glAttachShader(program, s.getFragmentShaderID());

    // Linkagem do programa e definindo como default
    glLinkProgram(program);
    glUseProgram(program);


// Vetores para enviar dados para enviar a GPU
    std::vector<Vec3> vertices;
    std::vector<Vec3> normals;
    std::vector<Vec2> uvs;

    // Criando as objetos
    OBJ3D objetos[QUANTIDADE_OBJS + 1] {
        OBJ3D("./objetos/RumikCube.obj", GL_QUADS),
        OBJ3D("./objetos/casa.obj", GL_TRIANGLES),
        OBJ3D("./objetos/espada.obj", GL_QUADS),
        OBJ3D("./objetos/torre.obj", GL_TRIANGLES),
        OBJ3D("./objetos/cranio.obj", GL_TRIANGLES),
        OBJ3D("./objetos/terreno.obj", GL_TRIANGLES),
        OBJ3D("./objetos/luz.obj", GL_TRIANGLES),
        OBJ3D("./objetos/skybox.obj", GL_TRIANGLES)
    };

    objetos[0].setKa(0.2).setKd(0.5).setKs(0.8).setNs(50); // define parametros de ilumincao do cubo mágico.
    objetos[1].setKa(0.4).setKd(0.9).setKs(0.2).setNs(26); // define parametros de ilumincao da casa.
    objetos[2].setKa(0.1).setKd(1).setKs(0.9).setNs(502); // define parametros de ilumincao da espada.
    objetos[3].setKa(0.3).setKd(0.4).setKs(0.3).setNs(32); // define parametros de ilumincao da torre.
    objetos[4].setKa(0.2).setKd(0.4).setKs(0.4).setNs(15); // define parametros de ilumincao do cranio.
    objetos[5].setKa(0.1).setKd(0.1).setKs(0.9).setNs(40); // define parametros de ilumincao do terreno.
    objetos[6].setKa(1).setKd(1).setKs(1).setNs(1000); // define parametros de ilumincao da luz.
    objetos[6].setKa(1000).setKd(0).setKs(0).setNs(1); // define parametros de ilumincao da skybox.
    

    // Criando as texturas
    Texture texturas[QUANTIDADE_OBJS + 1] {
        Texture("./objetos/RumikCubeTexture.jpg"),
        Texture("./objetos/casa.png"),
        Texture("./objetos/espada.png"),
        Texture("./objetos/torre.jpg"),
        Texture("./objetos/cranio.jpg"),
        Texture("./objetos/pedras.jpg"),
        Texture("./objetos/luz.png"),
        Texture("./objetos/skybox.png")
    };

    // criando posições de luzes
    Vec3 luzes[5] {Vec3(5, 3.7, 2), Vec3(0, 2, 3.5), Vec3(-4.9, 4.2, -2), Vec3(10, 6, 0), Vec3(-8, 0.38, 5)};

    // Criando escala iniciais dos objetos
    float scale_obj[QUANTIDADE_OBJS + 1] = {0.1, 0.1, 0.02, 0.1, 0.01, 15, 0.1, 1};
    // criando coordenadas iniciais dos objetos
    Vec3 coord_obj[QUANTIDADE_OBJS + 1] = {Vec3(5, 1, 2), Vec3(0), Vec3(-2, 1, -2), Vec3(6,0.38,-3), Vec3(-6, 0.38, 5), Vec3(0), luzes[0], Vec3(0)};
    // criando angulos iniciais dos objetos
    Vec3 angle_obj[QUANTIDADE_OBJS + 1] = {Vec3(0), Vec3(0), Vec3(0), Vec3(0), Vec3(0), Vec3(0), Vec3(0), Vec3(0)};

    // Criando matrizes de transformação
    MatModel mt_obj[QUANTIDADE_OBJS + 1];
    // Configurando as matrizes de transformação com os parâmetros iniciais
    for(int i = 0; i < QUANTIDADE_OBJS + 1; i++) {
        mt_obj[i].setScale(scale_obj[i]);
        mt_obj[i].setTranslation(coord_obj[i].getX(), coord_obj[i].getY(), coord_obj[i].getZ());
        mt_obj[i].setRotation(angle_obj[i].getX(), angle_obj[i].getY(), angle_obj[i].getZ());
    };
    
   // Carregando texturas
    for(int i = 0; i < QUANTIDADE_OBJS + 1; i++) {
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
    for(int i = 0; i < QUANTIDADE_OBJS + 1; i++) {
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

    GLuint buffer[3];
    glGenBuffers(3, buffer);


    // Abaixo, nós enviamos todo o conteúdo da variável vertices.
    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vec3), &vertices[0], GL_STATIC_DRAW);

    // Associando variáveis do programa GLSL (Vertex Shaders) com nossos dados
    GLint loc_positon = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(loc_positon);
    glVertexAttribPointer(loc_positon, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*) 0); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml
    

    // Abaixo, nós enviamos todo o conteúdo da variável uvs.
    glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(Vec2), &uvs[0], GL_STATIC_DRAW);

    // Associando variáveis do programa GLSL (Vertex Shaders) com nossos dados
    GLint loc_texture_coord = glGetAttribLocation(program, "texture_coord");
    glEnableVertexAttribArray(loc_texture_coord);
    glVertexAttribPointer(loc_texture_coord, 2, GL_FLOAT, GL_FALSE, sizeof(uvs[0]), (void*) 0); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml

    // Abaixo, nós enviamos todo o conteúdo da variável normals.
    glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(Vec3), &normals[0], GL_STATIC_DRAW);

    // Associando variáveis do programa GLSL (Vertex Shaders) com nossos dados
    GLint loc_normals = glGetAttribLocation(program, "normals");
    glEnableVertexAttribArray(loc_normals);
    glVertexAttribPointer(loc_normals, 3, GL_FLOAT, GL_FALSE, sizeof(normals[0]), (void*) 0); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml

    // Exibindo nossa janela
    glfwShowWindow(window);

    glEnable(GL_DEPTH_TEST);// ### importante para 3D

    //Inicializa o objeto de camera responsavel por criar as matrizes VIEW e PROJECTION do pipeline MVP
    camera Cam(program, glm::vec3(0, 1, -2), cameraFront, glm::vec3(0.0,1.0,0.0), 60, 1.0f, 0.1f, 100.0f, true);

    float angle = 0;            //Angulo responsavel pela movimentacao em circulos do modelo do cachorro
    float angle_inc = 0.001;      

    while (!glfwWindowShouldClose(window) && !stop) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1, 0.1, 0.1, 1.0);

        //Calcula quanto tempo se passou entre o ultimo frame e o atual
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;  

        cursor_position_update(window); //Chama a funcao que le as coordenadas do mouse e obtem para onde a camera deve olhar 

        //Movimenta a camera pelo cenario
        if(W){  //Para frente
            Cam.moveFront(deltaTime);
            W = false;
        }
        if(S){  //Para tras
            Cam.moveBack(deltaTime);
            S = false;
        }
        if(A){  //Para a esquerda
            Cam.moveLeft(deltaTime);
            A = false;
        }
        if(D){  //Para a direita
            Cam.moveRight(deltaTime);
            D = false;
        }


        Cam.setFront(cameraFront);  //set para onde a camera deve olhar, calculado pela funcao de leitura do mouse
        Cam.update();               //atualiza e manda os valores das matrizes calculadas pelo objeto de camera para a GPU (VIEW e PROJECTION)

        GLuint loc_light_pos = glGetUniformLocation(program, "lightPos"); // recuperando localizacao da variavel lightPos na GPU
        glUniform3f(loc_light_pos, luzes[select_light].getX(), luzes[select_light].getY(), luzes[select_light].getZ()); // posicao da fonte de luz
        mt_obj[6].setTranslation(luzes[select_light].getX(), luzes[select_light].getY(), luzes[select_light].getZ());


        GLuint loc_mat_model = glGetUniformLocation(program, "model");
        GLuint loc_ka = glGetUniformLocation(program, "ka"); // recuperando localizacao da variavel ka na GPU
        GLuint loc_kd = glGetUniformLocation(program, "kd"); // recuperando localizacao da variavel kd na GPU
        GLuint loc_ks = glGetUniformLocation(program, "ks"); // recuperando localizacao da variavel ks na GPU
        GLuint loc_ns = glGetUniformLocation(program, "ns"); // recuperando localizacao da variavel ns na GPU
        GLuint its_skybox = glGetUniformLocation(program, "its_skybox"); // recuperando localizacao da variavel its_kybox na GPU  

        angle += angle_inc;
        mt_obj[0].setRotation(-angle, angle, -angle);
        mt_obj[2].setRotation(angle, -angle, angle);
        

        for(int i = 0; i < QUANTIDADE_OBJS + 1; i++) {
            glUniformMatrix4fv(loc_mat_model, 1, GL_TRUE, mt_obj[i].getModelMatrix());
            glUniform1f(loc_ka, objetos[i].getKa()); // envia ka pra gpu
            glUniform1f(loc_kd, objetos[i].getKd()); // envia kd pra gpu    
            glUniform1f(loc_ks, objetos[i].getKs()); // envia ks pra gpu
            glUniform1f(loc_ns, objetos[i].getNs()); // envia ns pra gpu
            if(i == 7) {
                glUniform1f(its_skybox, 1.0); // envia que é uma skybox pra gpu
            } else {
                glUniform1f(its_skybox, 0.0);
            }

            // glActiveTexture(textureID);
            if(!polygonMode) {
                glBindTexture(GL_TEXTURE_2D, texturas[i].getTextureID());
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            } else {
                glBindTexture(GL_TEXTURE_2D, 0);
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }
            glDrawArrays(objetos[i].getTypeRender(), objetos[i].getVertexStart(), objetos[i].getVertexSize());
        }

        // atualizando a posicao da camera/observador na GPU para calculo da reflexao especular
        GLuint loc_view_pos = glGetUniformLocation(program, "viewPos"); // recuperando localizacao da variavel viewPos na GPU
        glUniform3f(loc_view_pos, Cam.getPos().x, Cam.getPos().y, Cam.getPos().z); // posicao da camera/observador (x,y,z) 

        glfwSwapBuffers(window);   
    }
 
    glfwDestroyWindow(window);
 
    glfwTerminate();
    exit(EXIT_SUCCESS);
}