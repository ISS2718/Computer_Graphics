#ifndef __BMP_TEXTURE__ 
#define __BMP_TEXTURE__

#include <iostream>
#include <ios>
#include <istream>
#include <fstream>
#include <string>

class BMPTexture
{
private:
    std::string *bmp_path;
    
    char *header;
    int data_pos;

    int width, height;
    int image_size;
    char *data;
public:
    BMPTexture(std::string bmp_path);
    ~BMPTexture();

    int getWidth();
    int getHeight();
    int getImageSize();
    char* getData();

    int loadTexture();
};


#endif