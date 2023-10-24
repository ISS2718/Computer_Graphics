#ifndef __OBJ3D__
#define __OBJ3D__

#include <iostream>
#include <ios>
#include <istream>
#include <fstream>
#include <vector>
#include <string>
#include <GLFW/glfw3.h>

#include "Vec2.h"
#include "Vec3.h"


#define SIZE_LINE 256

class OBJ3D {
    private:
        std::string* obj_path;

        long vertex_start, vertex_end;
        long uvs_start, uvs_end;
        long normals_start, normals_end;
        
        int type_render;
    public:
        OBJ3D(std::string obj_path, int type_render);
        ~OBJ3D();

        int getTypeRender();
        int loadOBJ3D(std::vector<Vec3> *out_vertex, std::vector<Vec2> *out_uvs, std::vector<Vec3> *out_normals);
        int loadOBJ3D_TRIANGLES(std::vector<Vec3> *out_vertex, std::vector<Vec2> *out_uvs, std::vector<Vec3> *out_normals);
        int loadOBJ3D_QUADS(std::vector<Vec3> *out_vertex, std::vector<Vec2> *out_uvs, std::vector<Vec3> *out_normals);
};

#endif