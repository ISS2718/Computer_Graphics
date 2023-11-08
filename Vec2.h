#ifndef __VEC2__
#define __VEC2__

#include <cmath>

/**
 * @class Vec2
 * @brief Representa um vetor bidimensional.
 */
class Vec2 {
private:
    float x; /**< Coordenada x.*/
    float y; /**< Coordenada y.*/

public:
    /**
     * Construtor padrão da classe Vec2. Inicializa o vetor com (0, 0).
     */
    Vec2();

    /**
     * Construtor da classe Vec2 com coordenadas especificadas.
     *
     * @param x A coordenada x do vetor.
     * @param y A coordenada y do vetor.
     */
    Vec2(const float &x, const float &y);

    /**
     * Construtor da classe Vec2 com uma única coordenada que é atribuída a ambas as coordenadas x e y.
     *
     * @param xy O valor que será atribuído às coordenadas x e y do vetor.
     */
    Vec2(const float &xy);

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
     * Define as coordenadas x e y do vetor.
     *
     * @param x A coordenada x do vetor.
     * @param y A coordenada y do vetor.
     */
    void set(const float &x, const float &y);

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
    Vec2& normalized();

    /**
     * Calcula o valor absoluto das coordenadas do vetor.
     *
     * @return Uma referência para o vetor com coordenadas absolutas.
     */
    Vec2& abs();

    /**
     * Calcula o produto escalar entre este vetor e outro vetor.
     *
     * @param v O vetor com o qual o produto escalar será calculado.
     * @return O resultado do produto escalar.
     */
    float dot(const Vec2 &v);

    /**
     * Calcula o produto vetorial entre este vetor e outro vetor.
     *
     * @param v O vetor com o qual o produto vetorial será calculado.
     * @return O resultado do produto vetorial.
     */
    float cross(const Vec2 &v);

    // Operadores de sobrecarga para operações com escalares.

    /**
     * Atribui um valor escalar a ambas as coordenadas do vetor.
     *
     * @param v O valor escalar a ser atribuído.
     * @return Uma referência para o vetor atualizado.
     */
    Vec2& operator=(const float &v);

    /**
     * Multiplica o vetor por um valor escalar.
     *
     * @param v O valor escalar pelo qual o vetor será multiplicado.
     * @return Um novo vetor resultante da multiplicação.
     */
    Vec2 operator*(const float &v);

    /**
     * Multiplica o vetor por um valor escalar e atualiza o vetor atual.
     *
     * @param v O valor escalar pelo qual o vetor será multiplicado.
     * @return Uma referência para o vetor atualizado.
     */
    Vec2& operator*=(const float &v);

    
    /**
     * Divide o vetor por um valor escalar.
     *
     * @param v O valor escalar pelo qual o vetor será dividido.
     * @return Um novo vetor resultante da divisão.
     */
    Vec2 operator/(const float &v);

    /**
     * Divide o vetor por um valor escalar e atualiza o vetor atual.
     *
     * @param v O valor escalar pelo qual o vetor será dividido.
     * @return Uma referência para o vetor atualizado.
     */
    Vec2& operator/=(const float &v);

    /**
     * Soma o vetor por um valor escalar.
     *
     * @param v O valor escalar pelo qual o vetor será somado.
     * @return Um novo vetor resultante da soma.
     */
    Vec2 operator+(const float &v);

    /**
     * Soma o vetor por um valor escalar e atualiza o vetor atual.
     *
     * @param v O valor escalar pelo qual o vetor será somado.
     * @return Uma referência para o vetor atualizado.
     */
    Vec2& operator+=(const float &v);

    /**
     * Subtrai o vetor por um valor escalar.
     *
     * @param v O valor escalar pelo qual o vetor será subitraido.
     * @return Um novo vetor resultante da subtração.
     */
    Vec2 operator-(const float &v);

    /**
     * Subtrai o vetor por um valor escalar e atualiza o vetor atual.
     *
     * @param v O valor escalar pelo qual o vetor será subitraido.
     * @return Uma referência para o vetor atualizado.
     */
    Vec2& operator-=(const float &v);

    // Operadores de sobrecarga para operações com vetores.

    /**
     * Atribui as coordenadas de outro vetor a este vetor.
     *
     * @param v O vetor cujas coordenadas serão atribuídas a este vetor.
     * @return Uma referência para o vetor atualizado.
     */
    Vec2& operator=(const Vec2 &v);

    /**
     * Multiplica o vetor por outro vetor componente a componente.
     *
     * @param v O vetor pelo qual este vetor será multiplicado.
     * @return Um novo vetor resultante da multiplicação componente a componente.
     */
    Vec2 operator*(const Vec2 &v);

    /**
     * Multiplica o vetor por outro vetor componente a componente e atualiza o vetor atual.
     *
     * @param v O vetor pelo qual este vetor será multiplicado.
     * @return Uma referência para o vetor atualizado.
     */
    Vec2& operator*=(const Vec2 &v);

    /**
     * Divide o vetor por outro vetor componente a componente.
     *
     * @param v O vetor pelo qual este vetor será dividido.
     * @return Um novo vetor resultante da divisão componente a componente.
     */
    Vec2 operator/(const Vec2 &v);

    /**
     * Divide o vetor por outro vetor componente a componente e atualiza o vetor atual.
     *
     * @param v O vetor pelo qual este vetor será dividido.
     * @return Uma referência para o vetor atualizado.
     */
    Vec2& operator/=(const Vec2 &v);

    /**
     * Soma o vetor por outro vetor componente a componente.
     *
     * @param v O vetor pelo qual este vetor será somado.
     * @return Um novo vetor resultante da soma componente a componente.
     */
    Vec2 operator+(const Vec2 &v);

    /**
     * Soma o vetor por outro vetor componente a componente e atualiza o vetor atual.
     *
     * @param v O vetor pelo qual este vetor será somado.
     * @return Uma referência para o vetor atualizado.
     */
    Vec2& operator+=(const Vec2 &v);

    /**
     * Subtrai o vetor por outro vetor componente a componente.
     *
     * @param v O vetor pelo qual este vetor será subtraído.
     * @return Um novo vetor resultante da soma componente a componente.
     */
    Vec2 operator-(const Vec2 &v);

    /**
     * Subtrai o vetor por outro vetor componente a componente e atualiza o vetor atual.
     *
     * @param v O vetor pelo qual este vetor será subtraído.
     * @return Uma referência para o vetor atualizado.
     */
    Vec2& operator-=(const Vec2 &v);
};

#endif