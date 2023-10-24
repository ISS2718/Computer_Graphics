#ifndef __SHADER__
#define __SHADER__

#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <iomanip>

class Shader {
    private:
        std::string vertex_shader_path;
        std::string fragment_shader_path;
    public:
        Shader();
        Shader(std::string vertex_path, std::string fragment_path);
        ~Shader();
        GLint compile();
};


#endif