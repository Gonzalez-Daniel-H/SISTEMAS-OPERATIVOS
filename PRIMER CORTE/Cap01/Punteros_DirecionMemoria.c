/**************************************************************
Autor: Daniel Gonzalez
Materia: Sistemas Operativos
Fecha: 08/08/24
Tema: Punteros y Direccion de Memoria
*****************************************************************/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
  int var=480;
  int *varptr=&var;
  int **doubleptr=&varptr;
  printf("Valor de var: \t\t= %d\n", var);
  printf("Valor del puntero: \t\t= %d\n",*varptr);
  printf("Valor del puntero doble: %d\n",**doubleptr);
  
  printf("Direccion de la variable \t= %p\n",&var);

  printf("Direccion del puntero \t= %p\n",&varptr);
  printf("valor en el  puntero doble \t\t= %p\n", varptr);

  printf("Direccion del puntero doble \t= %p\n",&doubleptr);
  printf("Valor en el puntero doble= %p\n",doubleptr);
  
  
  return 0;
}