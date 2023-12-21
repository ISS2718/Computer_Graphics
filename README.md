# Computação Gráfica

Repositório feito para a disciplina de Computação Gráfica (SCC0650), lecionada pelo Docente Ricardo Marcondes Marcacini, para o curso de Engenharia de Computação - USP São Carlos.

## Organização do Repositório

Este Repositório está organizado em 6-Branchs principais, além de outras de teste (se houver mais).

### Main (**Essa aqui!**)

Aqui está a base para os projetos, e onde ficam as versões mais atualizadas da minha estrutura de classes. Como se fosse os arquivos do "Motor Gráfico" programado nessa disciplina.

### [Trabalho_1](https://github.com/ISS2718/Computer_Graphics/tree/Trabalho_1)

Nessa branch está o uso de uma das versões do meu "Motor Gráfico" para realização do primeiro trabalho dessa disciplina.

Esse trabalho consistiu em apresentar 5 objetos 3D texturizados distintos, abertos por meio da leitura de arquivos wavefront (.obj) distintos, aplicando transformações de escala, translação e rotação nesses objetos. 

Nesse trabalho não foi utlizado o modelo Model-View-Projection e nem modelos de iluminação.

**Para mais informações do trabalho 1 [**clique aqui**](https://github.com/ISS2718/Computer_Graphics/blob/Trabalho_1/COMPUTACAO%20GRAFICA%20PROJETO%201.pdf).**

### [Trabalho_2](https://github.com/ISS2718/Computer_Graphics/tree/Trabalho_2)

**Para mais informações do trabalho 1 [**clique aqui**](https://github.com/ISS2718/Computer_Graphics/blob/Trabalho_2/Trabalho%202%20-%20Computa%C3%A7%C3%A3o%20Gr%C3%A1fica%20-%202023-02%20(2).pdf).**

### [Exercícios](https://github.com/ISS2718/Computer_Graphics/tree/Exercícios)

Nessa branch estão alguns exercícios realizados para essa disciplina.

Esses exercícios foram sugeridos ao longo das aulas para inicio da compreensão do pipiline gráfico e utlização do OpenGL e Glew.

### [Exercício_Transformacoes2D](https://github.com/ISS2718/Computer_Graphics/tree/Exercício_Transformacoes2D)

Nessa branch está o primeiro exercício "grande" realizado nessa disciplina, onde foi feito a rendererização de um triangulo 2D e aplicado transformações básicas por meio de interações com o teclado.

### [Exercício_ObjetoWavefrontTextura](https://github.com/ISS2718/Computer_Graphics/tree/Exercício_ObjetoWavefrontTextura)

Nessa branch está o exercício de renderização de objetos 3D texturizados por meio da leitura de um arquivo wavefront (.obj) e uma imagem de textura.

Esse exercíco foi proprosto com intuito de aprender a estrutura de um arquivo wavefront e de texturização com OpenGL.

## Como Utilizar a Base

### Compilar + Executar

Para executar o pojeto, execute na pasta raiz

``` $ make all```

### Compilar

Para só compilar o projeto, execute na pasta raiz

``` $ make release```

### Executar

Para executar, compilar o projeto e, executar na pasta raiz

``` $ make run```

### Clean

Para limpar executar na pasta raiz

``` $ make clean```

## Dependências

* [glew](https://github.com/nigels-com/glew)
* [glfw3](https://github.com/glfw/glfw)
* [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h)
    * Essa biblioteca é apena um arquivo e ela **JÁ ESTÁ INCLUSA** no projeto base!
