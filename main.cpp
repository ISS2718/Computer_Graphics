#include <GL/glew.h>  

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <time.h>

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


Vec3 coordinates(0, 0, 1), target(0.1, 0.1, 0.1), view_up(0, 1, 0), speed(3.5);

static void key_event(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_W) {
        coordinates += speed * target;
    }

    if(key == GLFW_KEY_S) {
        coordinates -= speed * target;
    }

    if(key == GLFW_KEY_D) {
        Vec3 r = target.cross(view_up);
        r.normalized();
        coordinates -= speed * r;
    }

    if(key == GLFW_KEY_A) {
        Vec3 r = target.cross(view_up);
        r.normalized();
        coordinates -= speed * r;
    }
}

//Variaveis globais para controle do uso do mouse
float yaw =  -90.0;         
float pitch = 0.0;
float lastX = 800/2;
float lastY = 800/2;

static void mouse_event(GLFWwindow* window, double xpos, double ypos) {
    float xoffset = xpos - 400;     //Calcula quanto o mouse foi mexido em X desde a ultima chamada da funcao
    float yoffset = 400 - ypos;     //Calcula quanto o mouse foi mexido em Y desde a ultima chamada da funcao, invertido

    float sensitivity = 2.5f;              //Sensibilidade da camera
    xoffset *= sensitivity;    //Calcula o quanto o angulo da camera em X foi alterado 
    yoffset *= sensitivity;   //Calcula o quanto o angulo da camera em Y foi alterado

    yaw += xoffset;     //Calcula o angulo atual da camera em X
    pitch += yoffset;   //Calcula o angulo atual da camera em Y

    
    if (pitch >= 89.9) pitch = 89.9;    //Define limites para o angulo da camera em Y
    if (pitch <= -89.9) pitch = -89.9;

    double yaw_rad = (M_PI/180) * yaw;
    double pitch_rad = (M_PI/180) * pitch;
    //Com base nos angulos da camera em X e Y calcula o ponto para o qual a camera esta olhando
    target.setX(cos(yaw_rad) * cos(pitch_rad));
    target.setY(sin(pitch_rad));
    target.setZ(sin(yaw_rad) * cos(pitch_rad));
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
    
    Shader s("./mvp.vert", "./mvp.frag");

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

    // Associando nossa janela com eventos de teclado
    glfwSetKeyCallback(window, key_event); // teclado

    // Associando nossa janela com eventos de mouse
    glfwSetCursorPosCallback(window, mouse_event); // mouse

    // Exibindo nossa janela
    glfwShowWindow(window);


    glEnable(GL_DEPTH_TEST);// ### importante para 3D

    float angulo = 0.0, angulo_inc = 0.0001; 
    MatModel mt_obj1, mt_obj2, mt_obj3;
    Camera observador;
    observador.setWindowAspect(1);
    observador.setCameraCoordinates(0, 0, 1);
    observador.setCameraTarget(0.1, 0.1, 0.1);
    observador.setCameraViewUp(0, 1, 0);
    observador.setFovy(M_PI/2);
    observador.setZNear(-1);
    observador.setZFar(1);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0, 1.0, 1.0, 1.0);

        angulo += angulo_inc;

        mt_obj1.setScale(0.05);
        mt_obj1.setTranslation(0.5, 0, 0);

        mt_obj1.setRotationX(angulo);
        // mt_obj1.setRotationY(M_PI/2);
        // mt_obj1.setRotationZ(M_PI/2);

        // observador.setCameraCoordinates(coordinates.getX(), coordinates.getY(), coordinates.getZ());
        // observador.setCameraTarget(target.getX(), target.getY(), target.getZ());
        // observador.setCameraViewUp(view_up.getX(), view_up.getY(), view_up.getZ());

        GLuint loc_mat_projection = glGetUniformLocation(program, "projection");
        glUniformMatrix4fv(loc_mat_projection, 1, GL_FALSE, observador.getMatPerspective());

        GLuint loc_mat_view = glGetUniformLocation(program, "view");
        glUniformMatrix4fv(loc_mat_view, 1, GL_TRUE, observador.getMatView());

        // enviando a matriz de transformacao para a GPU
        GLuint loc_mat_model = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(loc_mat_model, 1, GL_TRUE, mt_obj1.getModelMatrix());

        // glActiveTexture(textureID);
        glBindTexture(GL_TEXTURE_2D, txture.getTextureID());
        glDrawArrays(obj1.getTypeRender(), obj1.getVertexStart(), obj1.getNormalsEnd());

        mt_obj2.setScale(0.1);
        mt_obj2.setTranslation(-0.5, 0, 0);

        // mt_obj2.setRotationX(angulo);
        mt_obj2.setRotationY(angulo);
        // mt_obj2.setRotationZ(angulo);

        loc_mat_projection = glGetUniformLocation(program, "projection");
        glUniformMatrix4fv(loc_mat_projection, 1, GL_FALSE, observador.getMatPerspective());

        loc_mat_view = glGetUniformLocation(program, "view");
        glUniformMatrix4fv(loc_mat_view, 1, GL_TRUE, observador.getMatView());

        loc_mat_model = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(loc_mat_model, 1, GL_TRUE, mt_obj2.getModelMatrix());

        // glActiveTexture(textureID);
        glBindTexture(GL_TEXTURE_2D, txture.getTextureID());
        glDrawArrays(obj1.getTypeRender(), obj1.getVertexStart(), obj1.getNormalsEnd());


        mt_obj3.setScale(0.3);
        mt_obj3.setTranslation(0, 0, 0);

        // mat_transformation.setRotationX(angulo);
        // mat_transformation.setRotationY(angulo);
        mt_obj3.setRotationZ(angulo);

        loc_mat_projection = glGetUniformLocation(program, "projection");
        glUniformMatrix4fv(loc_mat_projection, 1, GL_FALSE, observador.getMatPerspective());

        loc_mat_view = glGetUniformLocation(program, "view");
        glUniformMatrix4fv(loc_mat_view, 1, GL_TRUE, observador.getMatView());

        loc_mat_model = glGetUniformLocation(program, "model");
        glUniformMatrix4fv(loc_mat_model, 1, GL_TRUE, mt_obj3.getModelMatrix());

        // glActiveTexture(textureID);
        glBindTexture(GL_TEXTURE_2D, txture.getTextureID());
        glDrawArrays(obj1.getTypeRender(), obj1.getVertexStart(), obj1.getNormalsEnd());


        glfwSwapBuffers(window);   
    }
 
    glfwDestroyWindow(window);
 
    glfwTerminate();
    exit(EXIT_SUCCESS);
}