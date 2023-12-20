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
#include "Render.h"
#include "Shader.h"
#include "Texture.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

#define WAVEFRONT_PATH "./OBJ/obj/caixa.obj"
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


//Funcao de callback para eventos de teclado
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    float cameraSpeed = 0.1;
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
    if(key == GLFW_KEY_Q && (action==1 || action==2)) //Se tecla Q apertada, entao diz que o programa deve ser fechado
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
    
    Texture txture(TEXTURE_PATH, GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);
    int r = txture.loadTexture();
    if(r == -1) {
        std::cout << "Textura " << TEXTURE_PATH << ": texture_path é nulo!!!" << std::endl;
        exit(EXIT_FAILURE);
    } else if(r == -2) {
        std::cout << "Textura " << TEXTURE_PATH << ": Não foi possível carregar imgaem!!!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Preparando dados para enviar a GPU
    std::vector<Vec3> vertices;
    std::vector<Vec3> normals;
    std::vector<Vec2> uvs;
    
    OBJ3D obj1(WAVEFRONT_PATH, GL_TRIANGLES);
    r = obj1.loadOBJ3D(&vertices, &uvs, &normals);
    if(r == -1) {
        std::cout << "File not found!" << std::endl;
        return r;
    } else if(r == -2) {
        std::cout << "Is not render with triangles" << std::endl;
        return r;
    }  else if(r == -3) {
        std::cout << "Is not render with quads" << std::endl;
        return r;
    }
    // define parametros de ilumincao do modelo
    obj1.setKa(0.2).setKd(0.5).setKs(0.9).setNs(32);

    GLuint buffer[2];
    glGenBuffers(2, buffer);


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

    // Exibindo nossa janela
    glfwShowWindow(window);

    glEnable(GL_DEPTH_TEST);// ### importante para 3D

    float angulo = 0.0, angulo_inc = 0.0001; 
    MatModel mt_obj1, mt_obj2, mt_obj3;

    //Inicializa o objeto de camera responsavel por criar as matrizes VIEW e PROJECTION do pipeline MVP
    camera Cam(program, glm::vec3(0, 1, -2), cameraFront, glm::vec3(0.0,1.0,0.0), 60, 1.0f, 0.1f, 10.0f, true);

    while (!glfwWindowShouldClose(window)) {
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
        glUniform3f(loc_light_pos, 5, 5, 0); // posicao da fonte de luz

        angulo += angulo_inc;

        mt_obj1.setScale(0.05);
        mt_obj1.setTranslation(0.5, 0, 0);

        mt_obj1.setRotationX(angulo);
        // mt_obj1.setRotationY(M_PI/2);
        // mt_obj1.setRotationZ(M_PI/2);

        // observador.setCameraCoordinates(coordinates.getX(), coordinates.getY(), coordinates.getZ());
        // observador.setCameraTarget(target.getX(), target.getY(), target.getZ());
        // observador.setCameraViewUp(view_up.getX(), view_up.getY(), view_up.getZ());

        // enviando a matriz de transformacao para a GPU
        GLuint loc_mat_model = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(loc_mat_model, 1, GL_TRUE, mt_obj1.getModelMatrix());

        GLuint loc_ka = glGetUniformLocation(program, "ka"); // recuperando localizacao da variavel ka na GPU
        glUniform1f(loc_ka, obj1.getKa()); // envia ka pra gpu

        GLuint loc_kd = glGetUniformLocation(program, "kd"); // recuperando localizacao da variavel kd na GPU
        glUniform1f(loc_kd, obj1.getKd()); // envia kd pra gpu    

        GLuint loc_ks = glGetUniformLocation(program, "ks"); // recuperando localizacao da variavel ks na GPU
        glUniform1f(loc_ks, obj1.getKs()); // envia ks pra gpu        

        GLuint loc_ns = glGetUniformLocation(program, "ns"); // recuperando localizacao da variavel ns na GPU
        glUniform1f(loc_ns, obj1.getNs()); // envia ns pra gpu 

        // atualizando a posicao da camera/observador na GPU para calculo da reflexao especular
        GLuint loc_view_pos = glGetUniformLocation(program, "viewPos"); // recuperando localizacao da variavel viewPos na GPU
        glUniform3f(loc_view_pos, Cam.getPos().x, Cam.getPos().y, Cam.getPos().z); // posicao da camera/observador (x,y,z)  

        // glActiveTexture(textureID);
        glBindTexture(GL_TEXTURE_2D, txture.getTextureID());
        glDrawArrays(obj1.getTypeRender(), obj1.getVertexStart(), obj1.getVertexEnd());

        mt_obj2.setScale(0.1);
        mt_obj2.setTranslation(-0.5, 0, 0);

        // mt_obj2.setRotationX(angulo);
        mt_obj2.setRotationY(angulo);
        // mt_obj2.setRotationZ(angulo);

        loc_mat_model = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(loc_mat_model, 1, GL_TRUE, mt_obj2.getModelMatrix());

        loc_ka = glGetUniformLocation(program, "ka"); // recuperando localizacao da variavel ka na GPU
        glUniform1f(loc_ka, obj1.getKa()); // envia ka pra gpu

        loc_kd = glGetUniformLocation(program, "kd"); // recuperando localizacao da variavel kd na GPU
        glUniform1f(loc_kd, obj1.getKd()); // envia kd pra gpu    

        loc_ks = glGetUniformLocation(program, "ks"); // recuperando localizacao da variavel ks na GPU
        glUniform1f(loc_ks, obj1.getKd()); // envia ks pra gpu        

        loc_ns = glGetUniformLocation(program, "ns"); // recuperando localizacao da variavel ns na GPU
        glUniform1f(loc_ns, obj1.getNs()); // envia ns pra gpu   

        // glActiveTexture(textureID);
        glBindTexture(GL_TEXTURE_2D, txture.getTextureID());
        glDrawArrays(obj1.getTypeRender(), obj1.getVertexStart(), obj1.getVertexEnd());


        mt_obj3.setScale(0.3);
        mt_obj3.setTranslation(0, 0, 0);

        // mat_transformation.setRotationX(angulo);
        // mat_transformation.setRotationY(angulo);
        mt_obj3.setRotationZ(angulo);

        loc_mat_model = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(loc_mat_model, 1, GL_TRUE, mt_obj3.getModelMatrix());

        loc_ka = glGetUniformLocation(program, "ka"); // recuperando localizacao da variavel ka na GPU
        glUniform1f(loc_ka, obj1.getKa()); // envia ka pra gpu

        loc_kd = glGetUniformLocation(program, "kd"); // recuperando localizacao da variavel kd na GPU
        glUniform1f(loc_kd, obj1.getKd()); // envia kd pra gpu    

        loc_ks = glGetUniformLocation(program, "ks"); // recuperando localizacao da variavel ks na GPU
        glUniform1f(loc_ks, obj1.getKd()); // envia ks pra gpu        

        loc_ns = glGetUniformLocation(program, "ns"); // recuperando localizacao da variavel ns na GPU
        glUniform1f(loc_ns, obj1.getNs()); // envia ns pra gpu  

        // glActiveTexture(textureID);
        glBindTexture(GL_TEXTURE_2D, txture.getTextureID());
        glDrawArrays(obj1.getTypeRender(), obj1.getVertexStart(), obj1.getVertexEnd());

        glfwSwapBuffers(window);   
    }
 
    glfwDestroyWindow(window);
 
    glfwTerminate();
    exit(EXIT_SUCCESS);
}