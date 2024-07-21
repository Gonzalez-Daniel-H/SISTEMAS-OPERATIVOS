/**************************************************************
Autor: Daniel Gonzalez
Materia: Sistemas Operativos
Fecha: 18/07/24
Tema: Indroduccion al lenguaje C y los demas entornos
  -Entornos en la web(CLOUD/NUBE)
  -Comandos Pricipales de Linux
  -Programa 0:hola mundo
*****************************************************************/
#include <stdio.h>

int main(int argc, char *argv[]){
  
  int opcion; 
  
  
  while(1){
      
  printf(" \n");
  printf("Hola soy un PROFESIONAL EN FORMACION y que informacion quier saber sobre mi? \n");
  printf(" \n 1: Mi Nombre y edad \n 2: El semestre que estoy cursando y Carrera \n 3: Cuantas materias esto viendo \n 4: Salir del programa \n ");
   scanf("%d", &opcion);

 
  switch(opcion){
      
    case 1:
      printf("Soy Daniel Gonzalez y tengo 18 años \n");
      break;
    case 2:
        printf("Voy en 4 semestre de ingenieria de Sistemas \n");
      break;
    case 3:
      
        printf("Actualmente estoy viendo 5 materias  \n");
        break;
    case 4:
          printf(" \n Hasta pronto ;) \n");
          break;
        
        default:
        printf(" Opcion incorrecta agregue una de las que aparecen en el menu \n ");


        }
    
            if(opcion==4){
               break;
    }
 
  }
  
  return 0;
}
  

    
  
