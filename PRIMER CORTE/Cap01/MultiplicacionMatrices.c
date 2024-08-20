/*******
Autor: Daniel Gonzalez
Materia: Sistemas operativos
Fecha: 15-08-24
Tema: Gestion de memoria
    - Diferencias entre usar o no usar Punteros
 *******/

#include <stdio.h>
#include <stdlib.h>

// impresion matrices
void impresionMatriz(int size, int *matriz, int salto) {
  for (int i = 0; i < size; i++) {
    if (i % salto == 0) {
      printf("\n");
    }
    printf(" %d ", *(matriz + i));
  }
  printf("\n");
}
// inicializacion
void inicializacion(int size, int *mA, int *mB, int *mC) {
  for (int i = 0; i < size; i++) {
    *(mA + i) = 3;
    *(mB + i) = 2;
    *(mC + i) = 0;
  }
}
// multiplicacion de matrices
void multiplicarMatrices(int *A, int *B, int *C, int n) {
 
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < n; ++k) {
        C[i * n + j] += A[i * n + k] * B[k * n + j];
      }
    }
  }
}
int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s tamanoFilaMatriz \n", argv[0]);
    exit(0);
  }
  int n = atoi(argv[1]);
  int size = n * n;
  int mA[size];
  int mB[size];
  int mC[size];

  inicializacion(size, mA, mB, mC);
  // impresion mA
  impresionMatriz(size, mA, n);
  // impresion mB
  impresionMatriz(size, mB, n);
  // impresion mC
  impresionMatriz(size, mC, n);

  // multiplicacion de matrices mAxmB=mC
  multiplicarMatrices(mA, mB, mC, n);
  impresionMatriz(size, mC, n);

  printf("\n\n\n. . .Fin del programa =) \n");
  return 0;
}