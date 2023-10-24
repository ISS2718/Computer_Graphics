#ifndef __MAT_4_4__
#define __MAT_4_4__
class Mat4
{
    private:
        float* matrix;
    public:
        Mat4(bool identity = false);
        Mat4(const Mat4 &v);
        ~Mat4();

        float* getMatix();
        float getValueForIndex(unsigned int index);
        float getValuePosition(unsigned int column, unsigned int row);
        void setValuePosition(unsigned int column, unsigned int row, float value);

        void operator=(const Mat4 &v);
        Mat4 operator*(const Mat4 &v);
        void operator*=(const Mat4 &v);
        Mat4 operator+(const Mat4 &v);
        void operator+=(const Mat4 &v);
        Mat4 operator-(const Mat4 &v);
        void operator-=(const Mat4 &v);
};
#endif