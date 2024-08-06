#include <stdio.h>
#include<math.h>
 float Area(int a,float *b){
     
     float pi=3.1415;
     float area;
     
     area = pi*(a * a);
     *b=area;
     
 }
 
 float perimetro(int a,float *b){
     float pi=3.1415;
     float peri;
     
     peri = pi*a;
     *b=peri;
     
 }
 
 float hipotenusa(int a,int b,float *c){
     
     float hipo;
     hipo=sqrt((a*a)+(b*b));
     
     *c=hipo;
 }


 int main(){
     int n,x,opcion;
     float resultado;
     
    while(opcion!=4){

     printf("\n 1.Desea saber el area de un circulo\n 2.Desea saber el perimetro de un circulo\n 3.Desea saber la hipotenusa de un triangulo\n 4.Salir\n ");
     scanf("%d",&opcion);
     switch(opcion){
         case 1:
         printf("Cual es el radio del circulo?\n");
         scanf("%d",&n);
          Area(n,&resultado);
         printf("El area del circulo es %f\n",resultado);


         break;
         case 2:
         
         printf("\n Ingrese el diametro del circulo\n ");
         scanf("%d",&n);
         perimetro(n,&resultado);
         printf("El perimetro del circulo es %f\n",resultado);

         
         break;
         
         case 3:
         printf("\n Ingrese el valor del cateto adyacente\n Ingrese el valor del cateto opuesto\n");
         scanf("%d %d \n",&n,&x);
         hipotenusa(n,x,&resultado);
         printf("El valor de la hipotenusa es %d \n ",resultado);

         
         
         break;
         case 4:
         printf("\n Vuelva pronto\n");
         
         default:
         printf("\n Opcion incorrecta\n");
     }
     
     
        }
     return 0;
 }
