#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Parte 1. Parâmetros por "referência".
//----------------------------------------------------------------------------------------------------------------------
void set(int *a, int val)
{
  *a = val;
}

// Implemente a seguinte função para fazer a troca dos valores entre a e b.
// Exemplo: a = 7, b = 8. Após a troca: a = 8, b = 7.
void swap(int *a, int *b)
{
}


// Teste do swap.
void test_1()
{
  int a = 7, b = 8;
  {// Podemos fazer a troca da seguinte forma:
    int aux = a; // Primeiro guardamos o valor de em uma variável auxiliar.
    a = b; // Agora sobrescrevemos o valor de a com o valor de b.
    b = aux; // Por fim, resgatamos o valor de a que guardamos anteriormente e atualizamos b.
  }
  assert(a == 8 && b == 7);
  // Agora após usar a função swap, os valores de a e b devem voltar aos valores originais.
  swap(&a, &b);
  assert(a == 7 && b == 8);
}


// Parte 2. Strings.
//----------------------------------------------------------------------------------------------------------------------
// A seguir alguns exercícios com strings. Note que também podem ser resolvidos usando notação de arrays, mas neste
// momento o objetivo é praticar o uso de ponteiros.

// Implementação no livro, pág. 103.
// Retorna a quantidade de caracteres em s.
int livro_strlen(char *s)
{
  char *p = s;

  while (*p != '\0')
    p++;
  return p - s;
}

// Implementação no livro, pág. 105.
// Copia todos os caracteres de t em s.
void livro_strcpy(char *s, char *t)
{
}

// Implementação no livro, pág. 106.
// Compara as string s e t.
// Retorna 0 se forem iguais.
// Retorna um número menor que 0 se s < t.
// Retorna um número maior que 0 se s > t.
int livro_strcmp(char *s, char *t)
{
  return 0;
}

// Concatena a string str no final de dest, copiando no máximo n caracteres de src.
// Implementação no manual da biblioteca ($ man strncat) ou online (https://linux.die.net/man/3/strncat).
// Note que se o array dest não tiver tamanho strlen(dest) + n, a função poderá resultar em um segfault.
char *manual_strncat(char *dest, char *src, size_t n)
{
  return NULL;
}

// Implemente uma função que retorne o índice onde a substring sub começa em str.
// Exemplo:
// str = "motocicleta"
// sub = "cicle"
// resposta = 4.
// Caso sub não se encontre em str, retorne -1.
// Exemplo: str = "abcd", sub = "z", resposta = -1.
int substring(char *str, char *sub)
{
  return 0;
}

void test_2()
{
  // strlen.
  assert(livro_strlen("") == 0);
  assert(livro_strlen("teste strlen") == 12);

  // strcpy.
  char strcpy_test[] = "resposta errada ";
  livro_strcpy(strcpy_test + 9, "correta");
  assert(!memcmp(strcpy_test, "resposta correta", strlen("resposta correta")));

  // strcmp.
  assert(livro_strcmp("aba", "abc") < 0);
  assert(livro_strcmp("abc", "abcd") < 0);
  assert(livro_strcmp("abcdz", "abcde") > 0);
  assert(livro_strcmp("abcdea", "abcde") > 0);
  assert(livro_strcmp("igual", "igual") == 0);

  // strncat.
  char strncat_test[255] = "primeira string";
  manual_strncat(strncat_test, " e segunda string", 11);
  assert(!memcmp(strncat_test, "primeira string e segunda", strlen("primeira string e segunda")));

  // substring.
  assert(substring("to", "totoro") == -1);
  assert(substring("totoro", "to") == 0);
  assert(substring("totoro", "toro") == 2);
  assert(substring("totoro", "z") == -1);
}

// Parte 3. Matrizes, arrays de ponteiros e ponteiros de ponteiros.
//----------------------------------------------------------------------------------------------------------------------
// Arrays podem ter mais de uma dimensão. Neste caso, costumam ser chamados de matrizes, ou arrays multidimensionais.
// Embora técnicamente um array de uma dimensão também pode ser considerado uma matriz unidimensional.
// Seguem alguns exemplos de arrays de mais de uma dimensão.
void exemplo_matrizes()
{
  int x = 10, y = 4, z = 2;

  // Para declarar um array comum colocamos entre colchetes o número de elementos que desejamos.
  // Isto faz com que recebamos uma sequência de n elementos um após o outro.
  int array_unidimensional[x];
  // O laço de repetição for é ideal para percorrer arrays.
  for (int i = 0; i < x; ++i) {
    array_unidimensional[i] = i;
  }
  printf("Array\n");
  for (int i = 0; i < x; ++i)
    printf("[%d]", array_unidimensional[i]);
  putchar('\n');


  // Para declarar uma matriz bidimensional adicionamos o tamanho da segunda dimensão após o primeiro.
  int matriz_bidimensional[y][x];
  // Para percorrer um matriz de duas dimensões precisamos de dois laços for aninhados. O de fora percorre a matriz
  // na dimensão das linhas, e o de dentro percorre as colunas j da linha i.
  for (int i = 0; i < y; ++i) {// Linhas.
    for (int j = 0; j < x; ++j) {// Colunas.
      matriz_bidimensional[i][j] = i + j;
    }
  }
  printf("Matriz 2\n");
  printf("{\n");
  for (int i = 0; i < y; ++i) {
    for (int j = 0; j < x; ++j)
      printf("[%d]", matriz_bidimensional[i][j]);
    putchar('\n');
  }
  printf("}\n");


  // Podemos continuar adicionando quantas dimensões precisarmos.
  int matriz_tridimensional[z][y][x];
  for (int i = 0; i < z; ++i) {
    for (int j = 0; j < y; ++j) {
      for (int k = 0; k < x; ++k) {
        matriz_tridimensional[i][j][k] = i + j + k;
      }
    }
  }
  printf("Matriz 3\n");
  printf("{\n");
  for (int i = 0; i < z; ++i) {
    printf("{\n");
    for (int j = 0; j < y; ++j) {
      for (int k = 0; k < x; ++k)
        printf("[%d]", matriz_tridimensional[i][j][k]);
      putchar('\n');
    }
    printf("}\n");
  }
  printf("}\n");

  // Uma matriz com n linhas e m colunas tem n * m elementos.
  // Sendo assim, uma outra forma de representar uma matriz é em um array de n * m elementos.
  int linhas = 4, colunas = 6;
  int array_matriz[linhas * colunas];
  for (int i = 0; i < linhas; ++i) {
    for (int j = 0; j < colunas; ++j) {
      array_matriz[i * colunas + j] = i + j;
    }
  }
  printf("Matriz array\n");
  printf("{\n");
  for (int i = 0; i < linhas; ++i) {
    for (int j = 0; j < colunas; ++j)
      printf("[%d]", array_matriz[i * colunas + j]);
    putchar('\n');
  }
  printf("}\n");
}

void matriz_identidade(int n)
{
  int matriz[n][n];
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      matriz[i][j] = (i == j) ? 1 : 0;
    }
  }
  printf("Matriz\n");
  printf("{\n");
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j)
      printf("[%d]", matriz[i][j]);
    putchar('\n');
  }
  printf("}\n");

}

/* n = 8.
1 1 1 1 1 1 1 1
1 2 2 2 2 2 2 1
1 2 3 3 3 3 2 1
1 2 3 4 4 3 2 1
1 2 3 4 4 3 2 1
1 2 3 3 3 3 2 1
1 2 2 2 2 2 2 1
1 1 1 1 1 1 1 1
 */
void matriz_piramide(int n)
{
}

/*
a a a a a a a a
d e e e e e e b
d h i i i i f b
d h l m m j f b
d h k k k j f b
d h e e e e f b
d g g g g g f b
c c c c c c c b
*/
void matriz_espiral(int n)
{
  char matriz[n][n];
}


void test_3()
{
//  exemplo_matrizes();
//  matriz_identidade(6);
//  matriz_piramide(6);
}

//----------------------------------------------------------------------------------------------------------------------
int main()
{
//  test_1();
//  test_2();
//  test_3();
}
