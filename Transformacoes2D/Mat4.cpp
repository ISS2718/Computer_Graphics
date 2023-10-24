#include "./Mat4.h"

Mat4::Mat4(bool identity) {
    this->matrix = new float[16];
    for(int i = 0; i < 16; i++) {
        if(identity && ((i % 5) == 0)) {
            this->matrix[i] = 1.0;
        } else {
            this->matrix[i] = 0.0;
        }
    }
}

Mat4::Mat4(const Mat4 &v) {
    this->matrix = new float[16];
    for(int i = 0; i < 16; i++) {
        this->matrix[i] = v.matrix[i];
    }
}

Mat4::~Mat4() {
    delete[] this->matrix;
}

float* Mat4::getMatix() {
    return matrix;
}

float Mat4::getValueForIndex(unsigned int index) {
    if(index < 16) {
        return matrix[index];
    } 
    return 0.0;
}

float Mat4::getValuePosition(unsigned int column, unsigned int row) {
    if(column > 4 && row > 4){
        return 0;
    }

    return matrix[column * 4 + row];
}

void Mat4::setValuePosition(unsigned int column, unsigned int row, float value) {
    if(column < 4 && row < 4){
        matrix[column * 4 + row] = value;
    }
}

void Mat4::operator=(const Mat4 &v) {
    for(int i = 0; i < 16; i++) {
        this->matrix[i] = v.matrix[i];
    }
}

Mat4 Mat4::operator*(const Mat4 &v) {
    Mat4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.matrix[i * 4 + j] = 0;
            for (int k = 0; k < 4; k++) {
                result.matrix[i * 4 + j] += this->matrix[i * 4 + k] * v.matrix[k * 4 + j];
            }
        }
    }
    return result; 
}

void Mat4::operator*=(const Mat4 &v) {
    Mat4 coppy(*this);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->matrix[i * 4 + j] = 0;
            for (int k = 0; k < 4; k++) {
                this->matrix[i * 4 + j] += coppy.matrix[i * 4 + k] * v.matrix[k * 4 + j];
            }
        }
    }
}

Mat4 Mat4::operator+(const Mat4 &v) {
    Mat4 result;
    for(int i = 0; i < 16; i++) {
        result.matrix[i] = this->matrix[i] + v.matrix[i];
    }
    return result;
}

void Mat4::operator+=(const Mat4 &v) {
    for(int i = 0; i < 16; i++) {
        this->matrix[i] += v.matrix[i];
    }
}

Mat4 Mat4::operator-(const Mat4 &v) {
    Mat4 result;
    for(int i = 0; i < 16; i++) {
        result.matrix[i] = this->matrix[i] - v.matrix[i];
    }
    return result;
}

void Mat4::operator-=(const Mat4 &v) {
    for(int i = 0; i < 16; i++) {
        this->matrix[i] -= v.matrix[i];
    }
}