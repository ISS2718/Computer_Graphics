#ifndef __SHADER__
#define __SHADER__

#include <GL/glew.h>  
#include <GLFW/glfw3.h>
#include <ios>
#include <istream>
#include <iomanip>
#include <fstream>
#include <string>

#define INFO_LENGTH 512

class Shader {
    private:
        std::string vertex_shader_path, fragment_shader_path;
        
        std::string s_vertex_shader, s_fragment_shader;
        
        GLint vertex_shader_ID, fragment_shader_ID;

        char* info;

        int loadShader(std::string &path,  std::string *shader);

    public:
        Shader();
        Shader(std::string vertex_path, std::string fragment_path);
        ~Shader();

        char* compileVertexShadder();
        char* compileFragmentShadder();

        int loadVertexShader(); 
        int loadFragmentShader();

        GLint getVertexShaderID();
        GLint getFragmentShaderID();
        const GLchar* getVertexShaderSource();
        const GLchar* getFragmentShaderSource();

        Shader& setVertexShader(std::string vertex_shader_path);
        Shader& setFragmentShader(std::string fragment_shader_path);
};


#endif