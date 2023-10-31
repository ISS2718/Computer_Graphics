attribute vec3 position;
attribute vec2 texture_coord;
varying vec2 out_texture;
uniform mat4 mat_transformation;

void main() {
    gl_Position = mat_transformation*vec4(position, 1.0);
    out_texture = vec2(texture_coord);
}