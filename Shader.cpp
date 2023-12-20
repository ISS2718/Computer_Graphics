#include "Shader.h"

Shader::Shader() {
    this->vertex_shader_ID = -1;
    this->fragment_shader_ID = -1;

    this->info = new char[INFO_LENGTH];
}

Shader::Shader(std::string vertex_shader_path, std::string fragment_shader_path) {
    this->vertex_shader_path = vertex_shader_path;
    this->fragment_shader_path = fragment_shader_path;
    
    this->vertex_shader_ID = -1;
    this->fragment_shader_ID = -1;

    this->info = new char[INFO_LENGTH];
}

Shader::~Shader() {
    delete[] info;
}

Shader& Shader::setVertexShader(std::string vertex_shader_path){
    this->vertex_shader_path = vertex_shader_path;
    return *this;
}

Shader& Shader::setFragmentShader(std::string vertex_shader_path) {
    this->fragment_shader_path = fragment_shader_path;
    return *this;
}

char* Shader::compileVertexShader() {
    glCompileShader(vertex_shader_ID);
    GLint r;
    glGetShaderiv(vertex_shader_ID, GL_COMPILE_STATUS, &r);
    if(r == GL_FALSE){
        // Informando tamanho da string do log de erro
        int infoLength = INFO_LENGTH;
        glGetShaderiv(vertex_shader_ID, GL_INFO_LOG_LENGTH, &infoLength);

        if(info == nullptr) {
            info = new char[INFO_LENGTH];
        }

        //recuperando o log de erro e imprimindo na tela
        glGetShaderInfoLog(vertex_shader_ID, infoLength, NULL, info);
        return info;
    }
    return nullptr;
}

char* Shader::compileFragmentShader() {
    glCompileShader(fragment_shader_ID);
    GLint r;
    glGetShaderiv(fragment_shader_ID, GL_COMPILE_STATUS, &r);
    if(r == GL_FALSE){
        // Informando tamanho da string do log de erro.
        int infoLength = INFO_LENGTH;
        glGetShaderiv(fragment_shader_ID, GL_INFO_LOG_LENGTH, &infoLength);

        if(info == nullptr) {
            info = new char[INFO_LENGTH];
        }

        //recuperando o log de erro e imprimindo na tela
        glGetShaderInfoLog(fragment_shader_ID, infoLength, NULL, info);
        return info;
    }
    return nullptr;
}

int Shader::loadVertexShader() {
    // Solicitando slots de vertex shader.
    vertex_shader_ID = glCreateShader(GL_VERTEX_SHADER);

    if(loadShader(vertex_shader_path, &s_vertex_shader)) {
        return -1;
    }
    const GLchar* vertex_shader = s_vertex_shader.c_str();

    // Associando nosso código-fonte GLSL ao slot de vertex shader solicitado.
    glShaderSource(vertex_shader_ID, 1, &vertex_shader, NULL);
    return 0;
}

int Shader::loadFragmentShader() {
    // Solicitando slots de fragment shader.
    fragment_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);
    
    if(loadShader(fragment_shader_path, &s_vertex_shader)) {
        return -1;
    }
    const GLchar* fragment_shader = s_vertex_shader.c_str();
    
    // Associando nosso código-fonte GLSL ao slot de fragment shader solicitado.
    glShaderSource(fragment_shader_ID, 1, &fragment_shader, NULL);
    return 0;
}

int Shader::loadShader(const std::string &path,  std::string *shader) {
    std::ifstream file(path, std::ifstream::in);

    if(!file.is_open()) {
        return -1;
    }

    shader->clear();
    char line[512];
    while(!file.eof()) {
        file.getline(line, 512);
        strcat(line, "\n");
        shader->append(line);
    }
    shader->push_back('\0');

    return 0;
}

GLint Shader::getVertexShaderID() {
    return vertex_shader_ID;
}

GLint Shader::getFragmentShaderID() {
    return fragment_shader_ID;
}

const GLchar* Shader::getVertexShaderSource() {
    return (const GLchar*) s_vertex_shader.c_str();
}

const GLchar* Shader::getFragmentShaderSource() {
    return (const GLchar*) s_fragment_shader.c_str();
}