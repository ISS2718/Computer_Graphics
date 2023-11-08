#include <GL/glew.h>  

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h> /* verifique no seu SO onde fica o glfw3.h */
#include <iostream>
#include <iomanip>
#include <vector>
#include "stb_image.h"

#include "MatT.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "OBJ3D.h"

#define WAVEFRONT_PATH "./OBJ/obj/Skull.obj"
#define TEXTURE_PATH "./OBJ/obj/textures/Skull.jpg"

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
        "attribute vec2 texture_coord;\n"
        "varying vec2 out_texture;\n"
        "uniform mat4 mat_transformation;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = mat_transformation*vec4(position, 1.0);\n"
        "    out_texture = vec2(texture_coord);\n"
        "}\n";

    // GLSL para Fragment Shader
    const GLchar* fragment_code =
        "uniform vec4 color;\n"
        "varying vec2 out_texture;\n"
        "uniform sampler2D samplerTexture;\n"
        "void main()\n"
        "{\n"
        "   vec4 texture = texture2D(samplerTexture, out_texture);\n"
        "   gl_FragColor = texture;\n"
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
        printf("--> %s\n", info);

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
        printf("--> %s\n", info);

    }

    // Associando os programas compilado ao programa principal
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    // Linkagem do programa e definindo como default
    glLinkProgram(program);
    glUseProgram(program);
    
    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    std::cout << "Texture ID: " << textureID << std::endl;

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(TEXTURE_PATH, &width, &height, &nrChannels, 0);

    if(data == nullptr) {
        std::cout << "A imagem não foi carregada" << std::endl;
    } else {
        std::cout << "Altura: " << height << ", Largura: " << width << ", Num.Chanels: " << nrChannels << std::endl;
        // Give the image to OpenGL
        if(nrChannels == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        } else if(nrChannels == 3) {
             glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        stbi_image_free(data);
    }

    // Preparando dados para enviar a GPU
    std::vector<Vec3> vertices;
    std::vector<Vec3> normals;
    std::vector<Vec2> uvs;
    OBJ3D obj(WAVEFRONT_PATH, GL_TRIANGLES);
    int r = obj.loadOBJ3D_TRIANGLES(&vertices, &uvs, &normals);

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


    // Exibindo nossa janela
    glfwShowWindow(window);


    glEnable(GL_DEPTH_TEST);// ### importante para 3D

    float angulo = 0.0, angulo_inc = 0.0001; 
    MatT mat_transformation;
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0, 1.0, 1.0, 1.0);

        angulo += angulo_inc;

        mat_transformation.setScale(0.05);
        mat_transformation.setTranslation(0, -0.5, 0);

        mat_transformation.setRotationX(angulo);
        mat_transformation.setRotationY(M_PI/2);
        mat_transformation.setRotationZ(M_PI/2);

        // enviando a matriz de transformacao para a GPU
        GLuint loc_mat_transformation = glGetUniformLocation(program, "mat_transformation");
        glUniformMatrix4fv(loc_mat_transformation, 1, GL_TRUE, mat_transformation.getTransformationMatrix());

        // glActiveTexture(textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glDrawArrays(obj.getTypeRender(), 0, vertices.size());
 
        glfwSwapBuffers(window);   
    }
 
    glfwDestroyWindow(window);
 
    glfwTerminate();
    exit(EXIT_SUCCESS);
}