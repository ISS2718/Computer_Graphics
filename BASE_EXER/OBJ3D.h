#ifndef __OBJ3D__
#define __OBJ3D__

#include <iostream>
#include <ios>
#include <istream>
#include <fstream>
#include <limits>
#include <vector>
#include <string>
#include <GLFW/glfw3.h>

#include "Vec2.h"
#include "Vec3.h"


#define SIZE_LINE 256

class OBJ3D {
    private:
        std::string* obj_path;

        int vertex_start, vertex_end, vertex_size;
        int uvs_start, uvs_end, uvs_size;
        int normals_start, normals_end, normals_size;

        int type_render;

        Vec3 max_vertex_coordinates;
        Vec3 min_vertex_coordinates;

        int loadOBJ3D_TRIANGLES(char* line, std::vector<unsigned int> *vertexIndices, std::vector<unsigned int> *uvsIndices, std::vector<unsigned int> *normalsIndices, bool *have_normal);
        int loadOBJ3D_QUADS(char* line, std::vector<unsigned int> *vertexIndices, std::vector<unsigned int> *uvsIndices, std::vector<unsigned int> *normalsIndices, bool *have_normal);
        void updateMaxMinCoordinates(float x, float y, float z);
    public:
        OBJ3D();
        OBJ3D(std::string obj_path, int type_render);
        OBJ3D(const char* obj_path, int type_render);
        ~OBJ3D();

        int getTypeRender();

        int getVertexStart();
        int getVertexEnd();
        int getVertexSize();

        int getUVSStart();
        int getUVSEnd();
        int getUVSSize();

        int getNormalsStart();
        int getNormalsEnd();
        int getNormalsSize();

        Vec3 getMaxVertexCoordinates();
        Vec3 getMinVertexCoordinates();

        OBJ3D& setTypeRender(int type_render);
        OBJ3D& setTypeObjPath(std::string obj_path);

        int loadOBJ3D(std::vector<Vec3> *out_vertex, std::vector<Vec2> *out_uvs, std::vector<Vec3> *out_normals);

        OBJ3D& operator=(OBJ3D& v);
};

#endif