#include "BMPTexture.h"

BMPTexture::BMPTexture(std::string bmp_path) {
    this->bmp_path = new std::string(bmp_path);
    this->header = new char[54];
    this->data_pos = -1;
    this->width = -1;
    this->height = -1;
    this-> image_size = -1;
    this->data = nullptr; 
}

BMPTexture::~BMPTexture() {
    delete bmp_path;
    delete[] header;

    if(data != nullptr){
        delete[] data;
    }
}

int BMPTexture::getWidth() {
    return width;
}

int BMPTexture::getHeight() {
    return height;
}

int BMPTexture::getImageSize(){
    return image_size;
}

char* BMPTexture::getData() {
    return data;
}

int BMPTexture::loadTexture() {
    std::ifstream file(*bmp_path, std::ifstream::binary);

    if(!file.is_open()) {
        // erro de abertura de arquivo
        return -1;
    } 

    if(file.read(header, 54 * sizeof(char)).fail()) {
        // erro de leitura header de arquivo
        return -2;
    } 

    if(header[0] != 'B' && header[1] != 'M') {
        // erro de leitura headear de arquivo
        return -2;
    }

    data_pos = *(int*)&(header[0x0A]);
    width = *(int*)&(header[0x12]);
    height = *(int*)&(header[0x16]);   
    image_size = *(int*)&(header[0x22]);

    if(image_size == 0) {
        // 3 : um byte para os componentes Red, Green and Blue.
        image_size = width*height*3;
    }

    if(data_pos == 0) {
        data_pos = 54;
    }

    data = new char[image_size];

    if(file.read(data, image_size * sizeof(char)).fail()) {
        // erro de leitura dos dados do arquivo.
        return -3;
    }

    file.close();
    return 0;
}