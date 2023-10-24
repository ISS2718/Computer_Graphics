#include "Shader.h"

Shader::Shader() {}

Shader::Shader(std::string vertex_shader_path, std::string fragment_shader_path) {
    this->vertex_shader_path = vertex_shader_path;
    this->fragment_shader_path = fragment_shader_path;
}

Shader::~Shader() {}

