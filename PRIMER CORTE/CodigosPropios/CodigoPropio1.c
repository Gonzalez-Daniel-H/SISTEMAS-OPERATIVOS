/**************************************************************
Autor: Daniel Gonzalez
Materia: Sistemas Operativos
Fecha: 18/07/24
Tema: Aprendiendo C
-Programa propio
*****************************************************************/
#include <stdio.h>
#include <stdlib.h>
void valor(int bonificacion,int age); 
int numero(int num);
int tapu(int numdias);

int main(){
  int opcion;
  int edad=12;
  int bono,n;
  int dias=0;
  
while(1){

  printf("\n 1.Citypark \n 2.Fibonacci \n 3.Poblacion Conejos \n 4.Salir \n");
  scanf(" %d", &opcion);
  switch(opcion){

    case 1:
      
      valor(bono,edad); 

    break;

    case 2:
      
      printf(" Ingrese el valor de la tabla que quiere \n");
      scanf(" %d",&n);
      numero(n);

    break;

    case 3:
      
    printf("el numero de dias que se demoro en pasar los 70k fueron %d \n ",tapu(dias));

    break;

    case 4:

      printf(" Gracias por su visita, vuelva pronto ;) \n");
      
    break;

    default:

    printf("Opcion no valida \n");

  }

  if(opcion==4){
    break;
  }
  
}
  return 0;
}

void valor(int bonificacion,int age){
 for(int i=0;i<age;i++){
   int bonofiant=bonificacion;
   
   age+=1;
   bonificacion=bonificacion*2;
   if(bonificacion>1000){
     bonificacion=bonofiant;

     break;
   }
 }
  printf(" La edad de la persona sera\n %d",age);
  printf(" La cantidad dada sera \n %d",bonificacion);
  
}
int numero(int num){

  int f=0;
  int x=0;
  int y=1;
  

  for(int i=0;i<num;i++){
    printf(" %d",f);

    x=y;
    y=f;
    f=x+y;
  }
  return f;
}
int tapu(int numdias){
  
  int poblacion_ayer,poblacion_hoy,poblacion_mañana;
  printf(" Ingrese la poblacion de conejos de ayer \n");
  scanf(" %d",&poblacion_ayer);
  printf(" Ingrese la poblacion de conejos de hoy \n");
  scanf(" %d",&poblacion_hoy);

while(poblacion_hoy<70000){

  poblacion_mañana=poblacion_ayer+poblacion_hoy;
  printf(" La poblacion va en %d\n",poblacion_mañana);

  poblacion_ayer=poblacion_hoy;
  poblacion_hoy=poblacion_mañana;

  numdias++;
 printf(" el numero de dia es %d\n",numdias);
}  
  return numdias;
}