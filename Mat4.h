#ifndef __MAT_4_4__
#define __MAT_4_4__

/**
 * @class Mat4
 * @brief Representa uma matriz 4x4.
 */
class Mat4 {
private:
    float* matrix; /**< Vetor que representa matriz 4x4.*/

public:
    /**
     * Construtor da classe Mat4. Inicializa a matriz como uma matriz identidade ou uma matriz zerada, dependendo do valor do parâmetro `identity`.
     *
     * @param identity Define se a matriz deve ser uma matriz identidade (se verdadeiro) ou uma matriz zerada (se falso).
     */
    Mat4(const bool &identity = false);

    /**
     * Construtor de cópia da classe Mat4.
     *
     * @param v A matriz a ser copiada.
     */
    Mat4(const Mat4 &v);

    /**
     * Destrutor da classe Mat4. Libera a memória alocada para a matriz.
     */
    ~Mat4();

    /**
     * Obtém um ponteiro para a matriz 4x4.
     *
     * @return Um ponteiro para a matriz.
     */
    float* getMatrix();

    /**
     * Obtém o valor em uma posição específica da matriz com base em um índice linear.
     *
     * @param index O índice linear da matriz.
     * @return O valor da matriz na posição especificada.
     */
    float getValueForIndex(const unsigned int &index);

    /**
     * Obtém o valor em uma posição específica da matriz com base nas coordenadas de coluna e linha.
     *
     * @param column A coordenada da coluna (0 a 3).
     * @param row A coordenada da linha (0 a 3).
     * @return O valor da matriz na posição especificada.
     */
    float getValuePosition(const unsigned int &column, const unsigned int &row);

    /**
     * Define o valor em uma posição específica da matriz com base nas coordenadas de coluna e linha.
     *
     * @param column A coordenada da coluna (0 a 3).
     * @param row A coordenada da linha (0 a 3).
     * @param value O valor a ser definido na posição especificada.
     */
    void setValuePosition(const unsigned int &column, const unsigned int &row, const float &value);

    /**
     * Sobrecarga do operador de atribuição para matrizes.
     *
     * @param v A matriz cujos valores serão copiados para esta matriz.
     * @return Uma referência para esta matriz atualizada.
     */
    Mat4& operator=(const Mat4 &v);

    /**
     * Sobrecarga do operador de multiplicação de matrizes.
     *
     * @param v A matriz a ser multiplicada por esta matriz.
     * @return Uma nova matriz resultante da multiplicação das duas matrizes.
     */
    Mat4 operator*(const Mat4 &v);

    /**
     * Sobrecarga do operador de multiplicação de matrizes e atualização desta matriz.
     *
     * @param v A matriz a ser multiplicada por esta matriz.
     * @return Uma referência para esta matriz atualizada.
     */
    Mat4& operator*=(const Mat4 &v);

    /**
     * Sobrecarga do operador de adição de matrizes.
     *
     * @param v A matriz a ser somada a esta matriz.
     * @return Uma nova matriz resultante da adição das duas matrizes.
     */
    Mat4 operator+(const Mat4 &v);

    /**
     * Sobrecarga do operador de adição de matrizes e atualização desta matriz.
     *
     * @param v A matriz a ser somada a esta matriz.
     * @return Uma referência para esta matriz atualizada.
     */
    Mat4& operator+=(const Mat4 &v);

    /**
     * Sobrecarga do operador de subtração de matrizes.
     *
     * @param v A matriz a ser subtraída desta matriz.
     * @return Uma nova matriz resultante da subtração das duas matrizes.
     */
    Mat4 operator-(const Mat4 &v);

    /**
     * Sobrecarga do operador de subtração de matrizes e atualização desta matriz.
     *
     * @param v A matriz a ser subtraída desta matriz.
     * @return Uma referência para esta matriz atualizada.
     */
    Mat4& operator-=(const Mat4 &v);
};

#endif
