/**************************************************************
Autor: Daniel Gonzalez
Materia: Sistemas Operativos
Fecha: 26/07/24
Tema: Aprendiendo C
-Programa propio
*****************************************************************/
#include <stdio.h>

void residente(float pf, float sv, float cp);
void negocio(float npf, float nsv, float ncp);
int main() {
  int residentes, negocios;
  char cliente;
  float procesa_factura = 4.50;
  float servi_basi = 20.50;
  float canal_pre = 7.50;
  float Neprocesa_factura = 15.00;
  float Neservi_basi = 75.00;
  float Necanal_pre = 50.00;

  printf("ingrese el Tipo de Cliente que es \n");
  printf("Si eres Residente R y si eres Negocioante N \n");
  scanf(" %c", &cliente);

  switch (cliente) {
  case 'r':

    residente(procesa_factura, servi_basi, canal_pre);
    break;

  case 'R':

    residente(procesa_factura, servi_basi, canal_pre);

    break;

  case 'n':

    negocio(Neprocesa_factura, Neservi_basi, Necanal_pre);

    break;

  case 'N':

    negocio(Neprocesa_factura, Neservi_basi, Necanal_pre);

    break;

  default:
    printf(" Opcion incorrecta");
  }

  return 0;
}
void residente(float pf, float sv, float cp) {
  int cuenta;
  printf("ingrese el numero de cuenta \n");
  scanf(" %d", &cuenta);
  float pago = pf + sv + cp;
  printf(" su numero de cuenta es %d y su pago es %f", cuenta, pago);
}
void negocio(float npf, float nsv, float ncp) {
  int cuenta;
  int cant;
  int incre=0;
  float pagoincre;
  int numcana;
  printf("ingrese el numero de cuenta \n");
  scanf(" %d", &cuenta);
  printf(" ingrese la cantidad de servicios basicos que tiene \n");
  scanf(" %d", &cant);
  printf(" ingrese la cantidad de canales premium \n");
  scanf(" %d", &numcana);
  if (cant > 10) {
    incre = cant - 10;
    printf(" hola %d \n",incre);
    pagoincre = (incre * 5);
    printf(" hola %f \n", pagoincre);

  }
  ncp*=numcana;
  float pago = npf + nsv + ncp + pagoincre;
  printf(" su numero de cuenta es %d y su pago es %f", cuenta, pago);
}
