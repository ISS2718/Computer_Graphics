#include "OBJ3D.h"

OBJ3D::OBJ3D(std::string obj_path, int type_render)
{
    this->obj_path = new std::string(obj_path);
    this->vertex_start = -1; 
    this->vertex_end = -1;
    this->uvs_start = -1; 
    this->uvs_end = -1;
    this->normals_start = -1; 
    this->normals_end = -1; 
    this->type_render = type_render;
}

OBJ3D::~OBJ3D()
{
    delete obj_path;
}

int OBJ3D::getTypeRender() {
    return type_render; 
}

int OBJ3D::loadOBJ3D(std::vector<Vec3> *out_vertex, std::vector<Vec2> *out_uvs, std::vector<Vec3> *out_normals) {
    if(type_render == GL_TRIANGLES || type_render == GL_TRIANGLE_STRIP) {
        // da pra deixar só o while desas funções separdas ou até modularizar melhor...
        //=======================REFATORAR DPS=======================
        return loadOBJ3D_TRIANGLES(out_vertex, out_uvs, out_normals);
    } else if(type_render == GL_QUADS || type_render == GL_QUAD_STRIP) {
        return loadOBJ3D_QUADS(out_vertex, out_uvs, out_normals);
    }

    return -3;
}

int OBJ3D::loadOBJ3D_QUADS(std::vector<Vec3> *out_vertex, std::vector<Vec2> *out_uvs, std::vector<Vec3> *out_normals) {
    std::ifstream file(*obj_path, std::ifstream::in);
    
    if(!file.is_open()) {
        return -1;
    }

    long vertex_start = out_vertex->size();
    long uvs_start = out_uvs->size();
    long normals_start = out_normals->size();
    
    char* line = new char[SIZE_LINE];

    std::vector< unsigned int > vertexIndices, uvsIndices, normalsIndices;
    std::vector<Vec3> temp_vertex, temp_normals;
    std::vector<Vec2> temp_uvs;

    while(!file.eof()) {
        file.getline(line, SIZE_LINE);
        
        if(line[0] == 'v') {
            if(line[1] == ' ') { // Coordenadas Vertices
                float x, y, z;
                sscanf(line, "v %f %f %f", &x, &y, &z);
                temp_vertex.push_back(Vec3(x, y, z));
            } else if(line[1] == 't') { // Coordenadas Teaxels
                float u, v;
                sscanf(line, "vt %f %f", &u, &v);
                temp_uvs.push_back(Vec2(u, v));
            } else if(line[1] == 'n') { // Coordenadas Normais
                float x, y, z;
                sscanf(line, "vn %f %f %f", &x, &y, &z);
                temp_normals.push_back(Vec3(x, y, z));
            }
        } else if(line[0] == 'f') {
            int index_v[4];
            int index_vt[4];
            int index_vn[4];
            int size = 4;
            int mach = sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &index_v[0], &index_vt[0], &index_vn[0], &index_v[1], &index_vt[1], &index_vn[1], &index_v[2], &index_vt[2], &index_vn[2], &index_v[3], &index_vt[3], &index_vn[3]);
            if(mach != 12) {
                //------------------Não sei o q eu vou fazer aqui ainda------------------//
                std::cout << "QUADS Read faces mach: " << mach << std::endl;
                //sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d\n", &index_v[0], &index_vt[0], &index_vn[0], &index_v[1], &index_vt[1], &index_vn[1], &index_v[2], &index_vt[2], &index_vn[2]);
                //size = 3;
            }

            for(int i = 0; i < size; i++) { // Salvando index para utilizalção dos vertices.
                vertexIndices.push_back(index_v[i]);
                uvsIndices.push_back(index_vt[i]);
                normalsIndices.push_back(index_vn[i]);
            }
        }
    }
    // Fechando o arquivo
    file.close();

    // Colocando vertices, uvs, normals nos vetores externos na ordem e com quantidade correta
    int size = vertexIndices.size();
    for(int i = 0; i < size; i++) {
        out_vertex->push_back(temp_vertex[vertexIndices[i] - 1]);
    }
    
    size = uvsIndices.size();
    for(int i = 0; i < size; i++) {
        out_uvs->push_back(temp_uvs[uvsIndices[i] - 1]);
    }

    size = normalsIndices.size();
    for(int i = 0; i < size; i++) {
        out_normals->push_back(temp_normals[normalsIndices[i] - 1]);
    }


    // Guardando começo e fim dos vertices
    this->vertex_start = vertex_start;
    this->vertex_end = out_vertex->size() -1;

    // Guardando começo e fim dos uvs
    this->uvs_start = uvs_start;
    this->uvs_end = out_uvs->size() -1;

    // Guardando começo e fim dos uvs
    this->normals_start = normals_start;
    this->normals_end = out_normals->size() -1;

    return 0;
}

int OBJ3D::loadOBJ3D_TRIANGLES(std::vector<Vec3> *out_vertex, std::vector<Vec2> *out_uvs, std::vector<Vec3> *out_normals) {
    std::ifstream file(*obj_path, std::ifstream::in);
    
    if(!file.is_open()) {
        return -1;
    }

    long vertex_start = out_vertex->size();
    long uvs_start = out_uvs->size();
    long normals_start = out_normals->size();
    
    char* line = new char[SIZE_LINE];

    std::vector< unsigned int > vertexIndices, uvsIndices, normalsIndices;
    std::vector<Vec3> temp_vertex, temp_normals;
    std::vector<Vec2> temp_uvs;

    bool normal = true;
    while(!file.eof()) {
        file.getline(line, SIZE_LINE);
        
        if(line[0] == 'v') {
            if(line[1] == ' ') { // Coordenadas Vertices
                float x, y, z;
                sscanf(line, "v %f %f %f", &x, &y, &z);
                temp_vertex.push_back(Vec3(x, y, z));
            } else if(line[1] == 't') { // Coordenadas Teaxels
                float u, v;
                sscanf(line, "vt %f %f", &u, &v);
                temp_uvs.push_back(Vec2(u, v));
            } else if(line[1] == 'n') { // Coordenadas Normais
                float x, y, z;
                sscanf(line, "vn %f %f %f", &x, &y, &z);
                temp_normals.push_back(Vec3(x, y, z));
            }
        } else if(line[0] == 'f') {
            int index_v[3];
            int index_vt[3];
            int index_vn[3];

                
            int mach = sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d\n", &index_v[0], &index_vt[0], &index_vn[0], &index_v[1], &index_vt[1], &index_vn[1], &index_v[2], &index_vt[2], &index_vn[2]);
            if(mach != 9) {
                // se não tiver vetor normal

                normal = false;
                printf("%s\n", line);
                mach = sscanf(line, "f %d/%d %d/%d %d/%d\n", &index_v[0], &index_vt[0], &index_v[1], &index_vt[1], &index_v[2], &index_vt[2]);
                printf("    =f %d/%d %d/%d %d/%d\n", index_v[0], index_vt[0], index_v[1], index_vt[1], index_v[2], index_vt[2]);
                //std::cout << "TRIANGLES Read faces mach: " << mach << std::endl;
            }
                
            for(int i = 0; i < 3; i++) { // Salvando index para utilizalção dos vertices.
                vertexIndices.push_back(index_v[i]);
                uvsIndices.push_back(index_vt[i]);
                if(normal) {
                    normalsIndices.push_back(index_vn[i]);
                }
            }
        }
    }
    // Fechando o arquivo
    file.close();

    // Colocando vertices, uvs, normals nos vetores externos na ordem e com quantidade correta
    int size = vertexIndices.size();
    for(int i = 0; i < size; i++) {
        out_vertex->push_back(temp_vertex[vertexIndices[i] - 1]);
    }
    
    // Guardando começo e fim dos vertices
    this->vertex_start = vertex_start;
    this->vertex_end = out_vertex->size() -1;
    
    size = uvsIndices.size();
    for(int i = 0; i < size; i++) {
        out_uvs->push_back(temp_uvs[uvsIndices[i] - 1]);
    }

    // Guardando começo e fim dos uvs
    this->uvs_start = uvs_start;
    this->uvs_end = out_uvs->size() -1;

    if(normal) {
        size = normalsIndices.size();
        for(int i = 0; i < size; i++) {
            out_normals->push_back(temp_normals[normalsIndices[i] - 1]);
        }

        // Guardando começo e fim dos uvs
        this->normals_start = normals_start;
        this->normals_end = out_normals->size() -1;
    }

    return 0;
}