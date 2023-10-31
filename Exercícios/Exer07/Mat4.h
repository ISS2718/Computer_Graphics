#ifndef __MAT_4_4__
#define __MAT_4_4__
class Mat4 {
    private:
        float* matrix;
    public:
        Mat4(const bool &identity = false);
        Mat4(const Mat4 &v);
        ~Mat4();

        float* getMatix();
        float getValueForIndex(const unsigned int &index);
        float getValuePosition(const unsigned int &column, const unsigned int &row);
        void setValuePosition(const unsigned int &column, const unsigned int &row, const float &value);

        Mat4& operator=(const Mat4 &v);
        Mat4 operator*(const Mat4 &v);
        Mat4& operator*=(const Mat4 &v);
        Mat4 operator+(const Mat4 &v);
        Mat4& operator+=(const Mat4 &v);
        Mat4 operator-(const Mat4 &v);
        Mat4& operator-=(const Mat4 &v);
};
#endif