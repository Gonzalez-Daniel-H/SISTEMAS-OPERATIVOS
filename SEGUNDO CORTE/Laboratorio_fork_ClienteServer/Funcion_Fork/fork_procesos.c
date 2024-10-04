/**************************************************************
Autor: Daniel Gonzalez
Materia: Sistemas Operativos
Fecha: 03/10/24
Tema: Taller de usar la funcion Fork
*****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
  
  //Crea un proceso Hijo utilizando la funcion fork 
  void creacion_fork(int linea){
      pid_t proceso; //Variable para almacenar el ID del proceso gracias al bloque de control
      proceso = fork();
      if(proceso<0){ //Verifica si hubo un error  en la creacion 
          printf("Error creación proceso\n");
          exit(1); //Termina el programa si hay un error
      }else if (proceso==0)
          printf("%d: Proceso =HIJO=: %d\n",linea, getpid());//Codigo ejecutado por el hijo
      else
          printf("%d: Proceso =PADRE= %d\n",linea, getpid());//Codigo ejecutado por el Padre
  }
  
  int main(int argc, char *argv[]){
      int p = (int) atoi(argv[1]); //Convierte el argumento a un entero
      for(int i=0; i<p; i++)
          creacion_fork(i);
  
  
      printf("\n---\n\n");
      return 0;
  }
