#ifndef __VEC3__
#define __VEC3__

#include <cmath>

/**
 * @class Vec3
 * @brief Representa um vetor tridimencional.
 */
class Vec3 {
private:
    float x; /**< Coordenada x.*/
    float y; /**< Coordenada y.*/
    float z; /**< Coordenada z.*/

public:
    /**
     * Construtor padrão da classe Vec3. Inicializa o vetor com (0, 0, 0).
     */
    Vec3();

    /**
     * Construtor da classe Vec3 com coordenadas especificadas.
     *
     * @param x A coordenada x do vetor.
     * @param y A coordenada y do vetor.
     * @param z A coordenada z do vetor.
     */
    Vec3(const float &x,const float &y,const float &z);

    /**
     * Construtor da classe Vec3 com uma única coordenada que é atribuída a ambas as coordenadas x, y, z.
     *
     * @param xyz O valor que será atribuído às coordenadas x, y e z do vetor.
     */
    Vec3(const float &xyz);

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
     * Define as coordenadas x, y e z do vetor.
     *
     * @param x A coordenada x do vetor.
     * @param y A coordenada y do vetor.
     * @param z A coordenada z do vetor.
     */
    void set(const float &x, const float &y, const float &z);

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
    Vec3& normalized();

    /**
     * Calcula o valor absoluto das coordenadas do vetor.
     *
     * @return Uma referência para o vetor com coordenadas absolutas.
     */    
    Vec3& abs();

    /**
     * Calcula o produto escalar entre este vetor e outro vetor.
     *
     * @param v O vetor com o qual o produto escalar será calculado.
     * @return O resultado do produto escalar.
     */    
    float dot(const Vec3 &v);

    /**
     * Calcula o produto vetorial entre este vetor e outro vetor.
     *
     * @param v O vetor com o qual o produto vetorial será calculado.
     * @return O resultado do produto vetorial.
     */
    Vec3 cross(const Vec3& v);


    // Operadores de sobrecarga para operações com escalares.

    /**
     * Atribui um valor escalar a ambas as coordenadas do vetor.
     *
     * @param v O valor escalar a ser atribuído.
     * @return Uma referência para o vetor atualizado.
     */
    Vec3& operator=(const float &v);

    /**
     * Multiplica o vetor por um valor escalar.
     *
     * @param v O valor escalar pelo qual o vetor será multiplicado.
     * @return Um novo vetor resultante da multiplicação.
     */
    Vec3 operator*(const float &v);

    /**
     * Multiplica o vetor por um valor escalar e atualiza o vetor atual.
     *
     * @param v O valor escalar pelo qual o vetor será multiplicado.
     * @return Uma referência para o vetor atualizado.
     */
    Vec3& operator*=(const float &v);

    
    /**
     * Divide o vetor por um valor escalar.
     *
     * @param v O valor escalar pelo qual o vetor será dividido.
     * @return Um novo vetor resultante da divisão.
     */
    Vec3 operator/(const float &v);

    /**
     * Divide o vetor por um valor escalar e atualiza o vetor atual.
     *
     * @param v O valor escalar pelo qual o vetor será dividido.
     * @return Uma referência para o vetor atualizado.
     */
    Vec3& operator/=(const float &v);

    /**
     * Soma o vetor por um valor escalar.
     *
     * @param v O valor escalar pelo qual o vetor será somado.
     * @return Um novo vetor resultante da soma.
     */
    Vec3 operator+(const float &v);

    /**
     * Soma o vetor por um valor escalar e atualiza o vetor atual.
     *
     * @param v O valor escalar pelo qual o vetor será somado.
     * @return Uma referência para o vetor atualizado.
     */
    Vec3& operator+=(const float &v);

    /**
     * Subtrai o vetor por um valor escalar.
     *
     * @param v O valor escalar pelo qual o vetor será subitraido.
     * @return Um novo vetor resultante da subtração.
     */
    Vec3 operator-(const float &v);

    /**
     * Subtrai o vetor por um valor escalar e atualiza o vetor atual.
     *
     * @param v O valor escalar pelo qual o vetor será subitraido.
     * @return Uma referência para o vetor atualizado.
     */
    Vec3& operator-=(const float &v);

    /**
     * Sobrecarga do operador de atribuição com igualdade a um valor escalar.
     *
     * @param v O valor escalar que será comparado com as coordenadas do vetor.
     * @return `true` se todas as coordenadas do vetor forem iguais a `v`, `false` caso contrário.
     */
    bool operator==(const float &v);

    /**
     * Sobrecarga do operador de maior ou igual a um valor escalar.
     *
     * @param v O valor escalar que será comparado com as coordenadas do vetor.
     * @return `true` se todas as coordenadas do vetor forem maiores ou iguais a `v`, `false` caso contrário.
     */
    bool operator>=(const float &v);

    /**
     * Sobrecarga do operador de menor ou igual a um valor escalar.
     *
     * @param v O valor escalar que será comparado com as coordenadas do vetor.
     * @return `true` se todas as coordenadas do vetor forem menores ou iguais a `v`, `false` caso contrário.
     */
    bool operator<=(const float &v);


    // Operadores de sobrecarga para operações com vetores.

    /**
     * Atribui as coordenadas de outro vetor a este vetor.
     *
     * @param v O vetor cujas coordenadas serão atribuídas a este vetor.
     * @return Uma referência para o vetor atualizado.
     */
    Vec3& operator=(const Vec3 &v);

    /**
     * Multiplica o vetor por outro vetor componente a componente.
     *
     * @param v O vetor pelo qual este vetor será multiplicado.
     * @return Um novo vetor resultante da multiplicação componente a componente.
     */
    Vec3 operator*(const Vec3 &v);

    /**
     * Multiplica o vetor por outro vetor componente a componente e atualiza o vetor atual.
     *
     * @param v O vetor pelo qual este vetor será multiplicado.
     * @return Uma referência para o vetor atualizado.
     */
    Vec3& operator*=(const Vec3 &v);

    /**
     * Divide o vetor por outro vetor componente a componente.
     *
     * @param v O vetor pelo qual este vetor será dividido.
     * @return Um novo vetor resultante da divisão componente a componente.
     */
    Vec3 operator/(const Vec3 &v);

    /**
     * Divide o vetor por outro vetor componente a componente e atualiza o vetor atual.
     *
     * @param v O vetor pelo qual este vetor será dividido.
     * @return Uma referência para o vetor atualizado.
     */
    Vec3& operator/=(const Vec3 &v);

    /**
     * Soma o vetor por outro vetor componente a componente.
     *
     * @param v O vetor pelo qual este vetor será somado.
     * @return Um novo vetor resultante da soma componente a componente.
     */
    Vec3 operator+(const Vec3 &v);

    /**
     * Soma o vetor por outro vetor componente a componente e atualiza o vetor atual.
     *
     * @param v O vetor pelo qual este vetor será somado.
     * @return Uma referência para o vetor atualizado.
     */
    Vec3& operator+=(const Vec3 &v);

    /**
     * Subtrai o vetor por outro vetor componente a componente.
     *
     * @param v O vetor pelo qual este vetor será subtraído.
     * @return Um novo vetor resultante da soma componente a componente.
     */
    Vec3 operator-(const Vec3 &v);

    /**
     * Subtrai o vetor por outro vetor componente a componente e atualiza o vetor atual.
     *
     * @param v O vetor pelo qual este vetor será subtraído.
     * @return Uma referência para o vetor atualizado.
     */
    Vec3& operator-=(const Vec3 &v);

    /**
     * Sobrecarga do operador de igualdade com outro vetor.
     *
     * @param v O vetor que será comparado com este vetor.
     * @return `true` se as coordenadas deste vetor forem iguais às coordenadas de `v`, `false` caso contrário.
     */
    bool operator==(const Vec3 &v);

    /**
     * Sobrecarga do operador de maior ou igual com outro vetor.
     *
     * @param v O vetor que será comparado com este vetor.
     * @return `true` se as coordenadas deste vetor forem maiores ou iguais às coordenadas de `v`, `false` caso contrário.
     */
    bool operator>=(const Vec3 &v);

    /**
     * Sobrecarga do operador de menor ou igual com outro vetor.
     *
     * @param v O vetor que será comparado com este vetor.
     * @return `true` se as coordenadas deste vetor forem menores ou iguais às coordenadas de `v`, `false` caso contrário.
     */
    bool operator<=(const Vec3 &v);
};

#endif