/**************************************************************
Autor: Daniel Gonzalez
Materia: Sistemas Operativos
Fecha: 08/08/24
Tema: Asignacion de memoria dinamica
*****************************************************************/
/*************
  //MALOCC
#include <stdio.h>
#include <stdlib.h>

int main() {
  int *varptr1=malloc(4*sizeof(int));//Asignacion para un vector de 4 enteros
  int *varptr2=malloc(sizeof(int[4]));//Asignacion para un vector de 4 enteros
  int *varptr3=malloc(4*sizeof *varptr3);//Asignacion para un vector de 4 enteros

  if (varptr1) {
    for (int i = 0; i < 4; i++)
        varptr1[i] = i;  // Llena el vector con valores del 0 al 3
    for (int i = 0; i < 4; i++)
      printf("varptr1[%d] == %d\n", i, varptr1[i]);  // Imprime los valores del vector
      }

    printf("Se libera memoria reservada\n");
    free(varptr1);  // Libera la memoria asignada a varptr1
    free(varptr2);  // Libera la memoria asignada a varptr2
    free(varptr3);  // Libera la memoria asignada a varptr3

      return 0;
  }
*************/
/************
// REALLOC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Info_Almacenamiento(const int *siguiente, const int *anterior, int valores) {
    if (siguiente) {
        printf("%s ubicación = %p. Tamaño reservado: %d enteros (%ld bytes)\n",
               (siguiente != anterior ? "Nuevo" : "Anterior"),
               (void*)siguiente, valores, valores * sizeof(int));
    }
}

int main() {
    // Define un arreglo de enteros que sirve como patrón inicial
    const int patron[] = {1, 2, 3, 4, 5, 6, 7, 8};
    // Calcula el número de enteros en el patrón
    const int patron_size = sizeof(patron) / sizeof(int);
    // Punteros para manejar la memoria reservada
    int *siguiente = NULL, *anterior = NULL;

    // Reserva memoria para copiar el patrón
    if ((siguiente = (int *)malloc(patron_size * sizeof(*siguiente)))) {
        // Copia el patrón en la nueva memoria reservada
        memcpy(siguiente, patron, sizeof(patron));
        // Muestra información sobre la memoria reservada
        Info_Almacenamiento(siguiente, anterior, patron_size);
    } else {
        // Si falla la reserva de memoria, termina con un error
        return EXIT_FAILURE;
    }

    // Define tamaños diferentes para reasignar memoria
    const int realloc_size[] = {10, 20, 30, 40, 50, 60, 70, 80};
    // Itera sobre los tamaños para reasignar la memoria
    for (int i = 0; i < sizeof(realloc_size) / sizeof(int); i++) {
        // Reasigna memoria y actualiza el puntero anterior
        if ((siguiente = (int *)realloc(anterior = siguiente, realloc_size[i] * sizeof(int)))) {
            // Muestra información sobre la nueva memoria asignada
            Info_Almacenamiento(siguiente, anterior, realloc_size[i]);
            // Verifica que el patrón original no haya cambiado
            assert(!memcmp(siguiente, patron, sizeof(patron)));
        } else {
            // Si falla la reasignación de memoria, libera la memoria y termina con un error
            printf("Se libera la memoria reservada\n");
            free(anterior);
            return EXIT_FAILURE;
        }
    }

    // Libera la memoria reservada al final
    free(siguiente);

    return 0;
}

**************************/
/************
// CALLOC
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, *ptr, sum = 0;

    // Solicita al usuario el número de elementos
    printf("Enter number of elements: ");
    scanf("%d", &n);

    // Reserva memoria para n enteros usando calloc
    ptr = (int*) calloc(n, sizeof(int));

    // Verifica si la memoria fue asignada correctamente
    if(ptr == NULL) {
        printf("Error! Memory not allocated.");
        exit(0);  // Sale del programa si no se pudo asignar la memoria
    }

    // Solicita al usuario que ingrese los elementos
    printf("Enter elements: ");
    for(i = 0; i < n; ++i) {
        scanf("%d", ptr + i);  // Lee cada entero y lo almacena en la memoria reservada
        sum += *(ptr + i);     // Suma cada elemento al total
    }

    // Muestra la suma de los elementos
    printf("Sum = %d", sum);

    // Libera la memoria reservada para evitar fugas de memoria
    free(ptr);

    return 0;  // Termina el programa con éxito
}

}
******************************/
