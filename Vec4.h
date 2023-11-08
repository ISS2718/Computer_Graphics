#ifndef __VEC4__
#define __VEC4__

#include <cmath>

/**
 * @class Vec4
 * @brief Representa um vetor quaternário (quatro dimensões).
 */
class Vec4 {
private:
    float x; /**< Coordenada x.*/
    float y; /**< Coordenada y.*/
    float z; /**< Coordenada z.*/
    float w; /**< Coordenada w.*/

public:
    /**
     * Construtor padrão da classe Vec4. Inicializa o vetor com (0, 0, 0, 0).
     */
    Vec4();

    /**
     * Construtor da classe Vec4 com coordenadas especificadas.
     *
     * @param x A coordenada x do vetor.
     * @param y A coordenada y do vetor.
     * @param z A coordenada z do vetor.
     * @param w A coordenada w do vetor.
     */
    Vec4(const float &x, const float &y, const float &z, const float &w);

    /**
     * Construtor da classe Vec4 com um único valor que é atribuído a todas as coordenadas x, y, z e w.
     *
     * @param xyzw O valor que será atribuído às coordenadas x, y, z e w do vetor.
     */
    Vec4(const float &xyzw);

    // Métodos de acesso e modificação das coordenadas.

    /**
     * Obtém a coordenada x do vetor.
     *
     * @return A coordenada x do vetor.
     */
    float getX();

    /**
     * Obtém a coordenada y do vetor.
     *
     * @return A coordenada y do vetor.
     */
    float getY();

    /**
     * Obtém a coordenada z do vetor.
     *
     * @return A coordenada z do vetor.
     */
    float getZ();

    /**
     * Obtém a coordenada w do vetor.
     *
     * @return A coordenada w do vetor.
     */
    float getW();

    /**
     * Define as coordenadas x, y, z e w do vetor.
     *
     * @param x A coordenada x do vetor.
     * @param y A coordenada y do vetor.
     * @param z A coordenada z do vetor.
     * @param w A coordenada w do vetor.
     */
    void set(const float &x, const float &y, const float &z, const float &w);

    /**
     * Define a coordenada x do vetor.
     *
     * @param x A coordenada x do vetor.
     */
    void setX(const float &x);

    /**
     * Define a coordenada y do vetor.
     *
     * @param y A coordenada y do vetor.
     */
    void setY(const float &y);

    /**
     * Define a coordenada z do vetor.
     *
     * @param z A coordenada z do vetor.
     */
    void setZ(const float &z);

    /**
     * Define a coordenada w do vetor.
     *
     * @param w A coordenada w do vetor.
     */
    void setW(const float &w);

    // Métodos de operação do vetor.

    /**
     * Calcula o comprimento (magnitude) do vetor.
     *
     * @return O comprimento do vetor.
     */
    float length();

    /**
     * Normaliza o vetor, tornando-o unitário (com comprimento igual a 1).
     *
     * @return Uma referência para o vetor normalizado.
     */
    Vec4& normalized();

    /**
     * Calcula o valor absoluto das coordenadas do vetor.
     *
     * @return Uma referência para o vetor com coordenadas absolutas.
     */
    Vec4& abs();

    /**
     * Calcula o produto escalar entre este vetor e outro vetor.
     *
     * @param v O vetor com o qual o produto escalar será calculado.
     * @return O resultado do produto escalar.
     */
    float dot(const Vec4 &v);

    // Operadores de sobrecarga para operações com escalares.

    /**
     * Atribui um valor escalar a todas as coordenadas do vetor.
     *
     * @param v O valor escalar a ser atribuído.
     * @return Uma referência para o vetor atualizado.
     */
    Vec4& operator=(const float &v);

    /**
     * Multiplica o vetor por um valor escalar.
     *
     * @param v O valor escalar pelo qual o vetor será multiplicado.
     * @return Um novo vetor resultante da multiplicação.
     */
    Vec4 operator*(const float &v);

    /**
     * Multiplica o vetor por um valor escalar e atualiza o vetor atual.
     *
     * @param v O valor escalar pelo qual o vetor será multiplicado.
     * @return Uma referência para o vetor atualizado.
     */
    Vec4& operator*=(const float &v);

    /**
     * Divide o vetor por um valor escalar.
     *
     * @param v O valor escalar pelo qual o vetor será dividido.
     * @return Um novo vetor resultante da divisão.
     */
    Vec4 operator/(const float &v);

    /**
     * Divide o vetor por um valor escalar e atualiza o vetor atual.
     *
     * @param v O valor escalar pelo qual o vetor será dividido.
     * @return Uma referência para o vetor atualizado.
     */
    Vec4& operator/=(const float &v);

    /**
     * Soma o vetor por um valor escalar.
     *
     * @param v O valor escalar pelo qual o vetor será somado.
     * @return Um novo vetor resultante da soma.
     */
    Vec4 operator+(const float &v);

    /**
     * Soma o vetor por um valor escalar e atualiza o vetor atual.
     *
     * @param v O valor escalar pelo qual o vetor será somado.
     * @return Uma referência para o vetor atualizado.
     */
    Vec4& operator+=(const float &v);

    /**
     * Subtrai o vetor por um valor escalar.
     *
     * @param v O valor escalar pelo qual o vetor será subtraído.
     * @return Um novo vetor resultante da subtração.
     */
    Vec4 operator-(const float &v);

    /**
     * Subtrai o vetor por um valor escalar e atualiza o vetor atual.
     *
     * @param v O valor escalar pelo qual o vetor será subtraído.
     * @return Uma referência para o vetor atualizado.
     */
    Vec4& operator-=(const float &v);

    // Operadores de sobrecarga para operações com vetores.

    /**
     * Atribui as coordenadas de outro vetor a este vetor.
     *
     * @param v O vetor cujas coordenadas serão atribuídas a este vetor.
     * @return Uma referência para o vetor atualizado.
     */
    Vec4& operator=(const Vec4 &v);

    /**
     * Multiplica o vetor por outro vetor componente a componente.
     *
     * @param v O vetor pelo qual este vetor será multiplicado.
     * @return Um novo vetor resultante da multiplicação componente a componente.
     */
    Vec4 operator*(const Vec4 &v);

    /**
     * Multiplica o vetor por outro vetor componente a componente e atualiza o vetor atual.
     *
     * @param v O vetor pelo qual este vetor será multiplicado.
     * @return Uma referência para o vetor atualizado.
     */
    Vec4& operator*=(const Vec4 &v);

    /**
     * Divide o vetor por outro vetor componente a componente.
     *
     * @param v O vetor pelo qual este vetor será dividido.
     * @return Um novo vetor resultante da divisão componente a componente.
     */
    Vec4 operator/(const Vec4 &v);

    /**
     * Divide o vetor por outro vetor componente a componente e atualiza o vetor atual.
     *
     * @param v O vetor pelo qual este vetor será dividido.
     * @return Uma referência para o vetor atualizado.
     */
    Vec4& operator/=(const Vec4 &v);

    /**
     * Soma o vetor por outro vetor componente a componente.
     *
     * @param v O vetor pelo qual este vetor será somado.
     * @return Um novo vetor resultante da soma componente a componente.
     */
    Vec4 operator+(const Vec4 &v);

    /**
     * Soma o vetor por outro vetor componente a componente e atualiza o vetor atual.
     *
     * @param v O vetor pelo qual este vetor será somado.
     * @return Uma referência para o vetor atualizado.
     */
    Vec4& operator+=(const Vec4 &v);

    /**
     * Subtrai o vetor por outro vetor componente a componente.
     *
     * @param v O vetor pelo qual este vetor será subtraído.
     * @return Um novo vetor resultante da subtração componente a componente.
     */
    Vec4 operator-(const Vec4 &v);

    /**
     * Subtrai o vetor por outro vetor componente a componente e atualiza o vetor atual.
     *
     * @param v O vetor pelo qual este vetor será subtraído.
     * @return Uma referência para o vetor atualizado.
     */
    Vec4& operator-=(const Vec4 &v);
};

#endif
