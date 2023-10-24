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