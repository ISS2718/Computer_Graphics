#include "OBJ3D.h"

OBJ3D::OBJ3D() {
    this->obj_path = nullptr;

    this->vertex_start = -1; 
    this->vertex_end = -1;
    this->vertex_size = -1;

    this->uvs_start = -1; 
    this->uvs_end = -1;
    this->uvs_size = -1;

    this->normals_start = -1; 
    this->normals_end = -1;
    this->normals_size = -1;

    this->type_render = -1;

    this->max_vertex_coordinates.set(0, 0, 0);
    this->min_vertex_coordinates.set(0, 0, 0);
}

OBJ3D::OBJ3D(std::string obj_path, int type_render) {
    this->obj_path = new std::string(obj_path);

    this->vertex_start = -1; 
    this->vertex_end = -1;
    this->vertex_size = -1;

    this->uvs_start = -1; 
    this->uvs_end = -1;
    this->uvs_size = -1;

    this->normals_start = -1; 
    this->normals_end = -1;
    this->normals_size = -1;

    this->type_render = type_render;

    this->max_vertex_coordinates.set(0, 0, 0);
    this->min_vertex_coordinates.set(0, 0, 0);
}

OBJ3D::OBJ3D(const char* obj_path, int type_render) {
    this->obj_path = new std::string(obj_path);

    this->vertex_start = -1; 
    this->vertex_end = -1;
    this->vertex_size = -1;

    this->uvs_start = -1; 
    this->uvs_end = -1;
    this->uvs_size = -1;

    this->normals_start = -1; 
    this->normals_end = -1;
    this->normals_size = -1;

    this->type_render = type_render;

    this->max_vertex_coordinates.set(0, 0, 0);
    this->min_vertex_coordinates.set(0, 0, 0);
}

OBJ3D::~OBJ3D() {
    delete obj_path;
}

int OBJ3D::getTypeRender() {
    return type_render; 
}

int OBJ3D::getVertexStart() {
    return vertex_start;
}

int OBJ3D::getVertexEnd() {
    return vertex_end;
}

int OBJ3D::getVertexSize() {
    return vertex_size;
}

int OBJ3D::getUVSStart() {
    return uvs_start;
}

int OBJ3D::getUVSEnd() {
    return uvs_end;
}

int OBJ3D::getUVSSize() {
    return uvs_size;
}

int OBJ3D::getNormalsStart() {
    return normals_start;
}

int OBJ3D::getNormalsEnd() {
    return normals_end;
}

int OBJ3D::getNormalsSize() {
    return normals_size;
}

Vec3 OBJ3D::getMaxVertexCoordinates() {
    return max_vertex_coordinates;
}

Vec3 OBJ3D::getMinVertexCoordinates() {
    return min_vertex_coordinates;
}

OBJ3D& OBJ3D::setTypeRender(int type_render) {
    this->type_render = type_render;
    return *this;
}

OBJ3D& OBJ3D::setTypeObjPath(std::string obj_path) {
    this->obj_path = new std::string(obj_path);
    return *this;
}

int OBJ3D::loadOBJ3D(std::vector<Vec3> *out_vertex, std::vector<Vec2> *out_uvs, std::vector<Vec3> *out_normals) {
    std::cout << obj_path->c_str() << "\n";
    std::ifstream file(*obj_path, std::ifstream::in);
    if(!file.is_open()) {
        return -1;
    }

    long vertex_start = out_vertex->size();
    long uvs_start = out_uvs->size();
    long normals_start = out_normals->size();
    
    char* line = new char[SIZE_LINE];

    std::vector<unsigned int> vertexIndices, uvsIndices, normalsIndices;
    std::vector<Vec3> temp_vertex, temp_normals;
    std::vector<Vec2> temp_uvs;

    bool have_normal = true;
    while(!file.eof()) {
        file.getline(line, SIZE_LINE);
        
        if(line[0] == 'v') {
            if(line[1] == ' ') { // Coordenadas Vertices
                float x, y, z;
                sscanf(line, "v %f %f %f", &x, &y, &z);
                updateMaxMinCoordinates(x, y, z);
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
            if(type_render == GL_TRIANGLES || type_render == GL_TRIANGLE_STRIP) {
                // Faces comppostas por triângulos
                if(loadOBJ3D_TRIANGLES(line, &vertexIndices, &uvsIndices, &normalsIndices, &have_normal) == -1) {
                    return -2;
                }
            } else if(type_render == GL_QUADS || type_render == GL_QUAD_STRIP) {
                // Faces comppostas por quadrados
                if(loadOBJ3D_QUADS(line, &vertexIndices, &uvsIndices, &normalsIndices, &have_normal) == -1) {
                    return -2;
                }
            } else {
                // As faces não são compostas por poligonos conhecidos.
                return -3;
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
    this->vertex_end = out_vertex->size();
    this->vertex_size = this->vertex_end - this->vertex_start;
    
    size = uvsIndices.size();
    for(int i = 0; i < size; i++) {
        out_uvs->push_back(temp_uvs[uvsIndices[i] - 1]);
    }

    // Guardando começo e fim dos uvs
    this->uvs_start = uvs_start;
    this->uvs_end = out_uvs->size();
    this->uvs_size = this->uvs_end - this->uvs_start;

    if(have_normal) {
        size = normalsIndices.size() - 1;
        for(int i = 0; i < size; i++) {
            out_normals->push_back(temp_normals[normalsIndices[i] - 1]);
        }

        // Guardando começo e fim dos uvs
        this->normals_start = normals_start;
        this->normals_end = out_normals->size();
        this->normals_size = this->normals_end - this->normals_start;
    }

    return 0;
}

int OBJ3D::loadOBJ3D_QUADS(char* line, std::vector<unsigned int> *vertexIndices, std::vector<unsigned int> *uvsIndices, std::vector<unsigned int> *normalsIndices, bool *have_normal) {
    int index_v[4];
    int index_vt[4];
    int index_vn[4];
    int mach = sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &index_v[0], &index_vt[0], &index_vn[0], &index_v[1], &index_vt[1], &index_vn[1], &index_v[2], &index_vt[2], &index_vn[2], &index_v[3], &index_vt[3], &index_vn[3]);
    if(mach != 12) {
        // se não tiver vetor normal
        *have_normal = false;
        printf("%s\n", line);
        mach = sscanf(line, "f %d/%d %d/%d %d/%d %d/%d\n", &index_v[0], &index_vt[0], &index_v[1], &index_vt[1], &index_v[2], &index_vt[2], &index_v[3], &index_vt[3]);
        if(mach != 8) {
            return -1;
        }
    }

    for(int i = 0; i < 4; i++) { // Salvando index para utilizalção dos vertices.
        vertexIndices->push_back(index_v[i]);
        uvsIndices->push_back(index_vt[i]);
        if(*have_normal) {
            normalsIndices->push_back(index_vn[i]);
        }
    }
    return 0;
}

int OBJ3D::loadOBJ3D_TRIANGLES(char* line, std::vector<unsigned int> *vertexIndices, std::vector<unsigned int> *uvsIndices, std::vector<unsigned int> *normalsIndices, bool *have_normal) {
    int index_v[3];
    int index_vt[3];
    int index_vn[3];
        
    int mach = sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d\n", &index_v[0], &index_vt[0], &index_vn[0], &index_v[1], &index_vt[1], &index_vn[1], &index_v[2], &index_vt[2], &index_vn[2]);
    if(mach != 9) {
        // se não tiver vetor normal
        *have_normal = false;
        mach = sscanf(line, "f %d/%d %d/%d %d/%d\n", &index_v[0], &index_vt[0], &index_v[1], &index_vt[1], &index_v[2], &index_vt[2]);
        if(mach != 6) {
            return -1;
        }
    }
        
    for(int i = 0; i < 3; i++) { // Salvando index para utilizalção dos vertices.
        vertexIndices->push_back(index_v[i]);
        uvsIndices->push_back(index_vt[i]);
        if(*have_normal) {
            normalsIndices->push_back(index_vn[i]);
        }
    }
    
    return 0;
}

void OBJ3D::updateMaxMinCoordinates(float x, float y, float z) {
    if(x > max_vertex_coordinates.getX()) {
        max_vertex_coordinates.setX(x);
    } 
    
    if(x < min_vertex_coordinates.getX()) {
        min_vertex_coordinates.setX(x);
    }

    if(y > max_vertex_coordinates.getY()) {
        max_vertex_coordinates.setY(y);
    } 
    
    if(y < min_vertex_coordinates.getY()) {
        min_vertex_coordinates.setY(y);
    }

    if(z > max_vertex_coordinates.getZ()) {
        max_vertex_coordinates.setX(z);
    }
    
    if(z < min_vertex_coordinates.getZ()) {
        min_vertex_coordinates.setX(z);
    }
}

OBJ3D& OBJ3D::operator=(const OBJ3D& v) {
    // Verifica se é uma autoatribuição
    if (this == &v) {
        return *this;
    }

    // Libera recursos alocados no objeto atual
    if (this->obj_path != nullptr) {
        delete this->obj_path;
    }

    // Realiza a cópia dos membros
    if (v.obj_path != nullptr) {
        this->obj_path = new std::string(*v.obj_path);
    } else {
        this->obj_path = nullptr;
    }

    this->vertex_start = v.vertex_start; 
    this->vertex_end = v.vertex_end;
    this->vertex_size = v.vertex_size;

    this->uvs_start = v.uvs_start; 
    this->uvs_end = v.uvs_end;
    this->uvs_size = v.uvs_size;

    this->normals_start = v.normals_start; 
    this->normals_end = v.normals_end;
    this->normals_size = v.normals_size; 

    this->type_render = v.type_render;

    return *this;
}