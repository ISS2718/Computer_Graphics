#include <GL/glew.h>  

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h> /* verifique no seu SO onde fica o glfw3.h */
#include<iostream>

#include "MatT.h"

// variaveis globais
typedef struct{
    float x, y, z;
} coordenadas;

float t_x = 0.0f; 
float t_y = 0.0f;

float s = 1.0f;

float angle = 0.0f;

const float dislocation = 0.01f;
const float rotation = 0.1f;
const float scaletion = 0.1f;

// funcao para processar eventos de teclado
static void key_event(GLFWwindow* window, int key, int scancode, int action, int mods){
    //printf("Pressionando tecla %d\n", key);

    if(key==GLFW_KEY_RIGHT || key==GLFW_KEY_D) {
        if(t_x <= 1) {
            t_x += dislocation; // tecla para direita
        } else {
            t_x = -1;
        }
    }
    if(key==GLFW_KEY_LEFT || key==GLFW_KEY_A) {
        if(t_x >= -1) {
            t_x -= dislocation; // tecla para esqueda
        } else {
            t_x = 1;
        }
    }

    if(key==GLFW_KEY_UP || key==GLFW_KEY_W) {
        if(t_y <= 1) {
            t_y += dislocation; // tecla para cima
        } else {
            t_y = -1;
        }
    }
    if(key==GLFW_KEY_DOWN || key==GLFW_KEY_S) {
        if(t_y >= -1) {
            t_y -= dislocation; // tecla para baixo
        } else {
            t_y = 1;
        }
    }

    if(key==GLFW_KEY_Q) angle += rotation;
    if(key==GLFW_KEY_E) angle -= rotation;

    if(key==GLFW_KEY_Z) {
        s += scaletion;
    }
    if(key==GLFW_KEY_X) {
        s -= scaletion;
    }
}

int main(void){
 
    // inicicializando o sistema de\ janelas
    glfwInit();

    // deixando a janela invisivel, por enquanto
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

 
    // criando uma janela
    GLFWwindow* window = glfwCreateWindow(800, 800, "Cubo", NULL, NULL);

    
    // tornando a janela como principal 
    glfwMakeContextCurrent(window);

    // inicializando Glew (para lidar com funcoes OpenGL)
    GLint GlewInitResult = glewInit();
    printf("GlewStatus: %s", glewGetErrorString(GlewInitResult));


    // GLSL para Vertex Shader
    const GLchar* vertex_code =
    "attribute vec3 position;\n"
    "uniform mat4 mat_transformation;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = mat_transformation * vec4(position, 1.0);\n"
    "}\n";

    // GLSL para Fragment Shader
    const GLchar* fragment_code =
    "uniform vec4 color;\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = color;\n"
    "}\n";

    // Requisitando slot para a GPU para nossos programas Vertex e Fragment Shaders
    GLuint program = glCreateProgram();
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

    // Associando nosso código-fonte GLSL aos slots solicitados
    glShaderSource(vertex, 1, &vertex_code, NULL);
    glShaderSource(fragment, 1, &fragment_code, NULL);

    // Compilando o Vertex Shader e verificando erros
    glCompileShader(vertex);

    GLint isCompiled = 0;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE){

        //descobrindo o tamanho do log de erro
        int infoLength = 512;
        glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &infoLength);

        //recuperando o log de erro e imprimindo na tela
        char info[infoLength];
        glGetShaderInfoLog(vertex, infoLength, NULL, info);

        printf("Erro de compilacao no Vertex Shader.\n");
        printf("--> %s\n",&info);

    }

    

    // Compilando o Fragment Shader e verificando erros
    glCompileShader(fragment);

    isCompiled = 0;
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE){

        //descobrindo o tamanho do log de erro
        int infoLength = 512;
        glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &infoLength);

        //recuperando o log de erro e imprimindo na tela
        char info[infoLength];
        glGetShaderInfoLog(fragment, infoLength, NULL, info);

        printf("Erro de compilacao no Fragment Shader.\n");
        printf("--> %s\n",&info);

    }

    // Associando os programas compilado ao programa principal
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    // Linkagem do programa e definindo como default
    glLinkProgram(program);
    glUseProgram(program);
 

    // Preparando vertices da esfera dados para enviar a GPU

    float r = 0.5f;//# raio
    int num_sectors = 30; // # qtd de sectors (longitude)
    int num_stacks = 30; //# qtd de stacks (latitude)

    //# grid sectos vs stacks (longitude vs latitude)
    float sector_step=(M_PI*2)/num_sectors; // # variar de 0 até 2π
    float stack_step=(M_PI)/num_stacks; // # variar de 0 até π



    //# vamos gerar um conjunto de vertices representantes poligonos
    //# para a superficie da esfera.
    //# cada poligono eh representado por dois triangulos
    int num_vertices = num_sectors*num_stacks*6; // sao 6 verticies, pois sao 2 triangulos por regiao
    coordenadas vertices[num_vertices]; 

    int counter = 0;
    for(int i=0; i < num_sectors; i++){
        for(int j=0; j < num_stacks; j++){
            float u = i * sector_step; // # angulo setor
            float v = j * stack_step; // # angulo stack
            
            float un = 0;  //# angulo do proximo sector
            if(i+1==num_sectors){
                un = M_PI*2;
            }
            else{
                un = (i+1)*sector_step;
            }
                
            float vn = 0; //# angulo do proximo stack
            if(j+1==num_stacks){
                vn = M_PI;
            }
            else{
                vn = (j+1)*stack_step;
            }
            
            //# verticies do poligono
            // coordenadas de p0, p1, p2 e p3
            float p0_x = r*sin(v)*cos(u);
            float p0_y = r*sin(v)*sin(u);
            float p0_z = r*cos(v);

            float p1_x = r*sin(vn)*cos(u);
            float p1_y = r*sin(vn)*sin(u);
            float p1_z = r*cos(vn);

            float p2_x = r*sin(v)*cos(un);
            float p2_y = r*sin(v)*sin(un);
            float p2_z = r*cos(v);

            float p3_x = r*sin(vn)*cos(un);
            float p3_y = r*sin(vn)*sin(un);
            float p3_z = r*cos(vn);

            // adicionando triangulo 1 (primeira parte do poligono)
            vertices[counter].x = p0_x; vertices[counter].y = p0_y; vertices[counter].z = p0_z; counter++;
            vertices[counter].x = p2_x; vertices[counter].y = p2_y; vertices[counter].z = p2_z; counter++;
            vertices[counter].x = p1_x; vertices[counter].y = p1_y; vertices[counter].z = p1_z; counter++;


            // adicionando triangulo 2 (segunda e ultima parte do poligono)
            vertices[counter].x = p3_x; vertices[counter].y = p3_y; vertices[counter].z = p3_z; counter++;
            vertices[counter].x = p1_x; vertices[counter].y = p1_y; vertices[counter].z = p1_z; counter++;
            vertices[counter].x = p2_x; vertices[counter].y = p2_y; vertices[counter].z = p2_z; counter++;

        }

    }

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);


    // Abaixo, nós enviamos todo o conteúdo da variável vertices.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);


    // Associando variáveis do programa GLSL (Vertex Shaders) com nossos dados
    GLint loc = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*) 0); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml
 
    // Associando variávels do programa GLSL (Fragment Shader) para definir cores
    GLint loc_color = glGetUniformLocation(program, "color");

    // Associando nossa janela com eventos de teclado
    glfwSetKeyCallback(window, key_event); // teclado

    // Exibindo nossa janela
    glfwShowWindow(window);
    
    // Criando Matrix de transformação
    MatT mat_transformation;

    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0, 1.0, 1.0, 1.0);

        // atualizando matriz de translação
        mat_transformation.setTranslation(t_x, t_y, 0);
        // atualizando matriz de escala
        mat_transformation.setScale(s);

        // atulizando matriz de rotação
        mat_transformation.setRotationX(angle);
        // atulizando matriz de rotação
        mat_transformation.setRotationY(angle);
        // atulizando matriz de rotação
        mat_transformation.setRotationZ(angle);

        // enviando a matriz de transformacao para a GPU
        loc = glGetUniformLocation(program, "mat_transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, mat_transformation.getTransformationMatrix());

        float R = 0, G = 0, B = 0;
        int flag = 0;
        for(int triangle=0; triangle < num_vertices; triangle=triangle+3){
            if(flag){
                if(R > 0) {
                    R-= 0.42;
                } else if(G > 0) {
                    G-= 0.55;
                } else if(B > 0) {
                    B-= 0.24;
                } else {
                    flag = 0; 
                }
            } else {
                if(R < 1) {
                    R+= 0.42;
                } else if(G < 1) {
                    G+= 0.55;
                } else if(B < 1) {
                    B+= 0.24;
                } else {
                    flag = 1; 
                }
            }
            
            glUniform4f(loc_color, R, G, B, 1.0);
            glDrawArrays(GL_TRIANGLES, triangle, 3);
        }
 
        glfwSwapBuffers(window);
    }
 
    glfwDestroyWindow(window);
 
    glfwTerminate();
    return 0;
}