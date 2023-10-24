    const GLchar* fragment_code =
    "uniform vec4 color;\n"
    "varying vec2 out_texture;\n"
    "uniform sampler2D samplerTexture;\n"
    "void main()\n"
    "{\n"
    "   vec4 texture = texture2D(samplerTexture, out_texture);\n"
    "   gl_FragColor = color;\n"
    "}\n";