/********************************************
Fecha: 10 de octubre del 2024
Autor: Daniel Gonzalez
Materia: Sistemas Operativos
objetivo: Aplicar los conceptos vistos en clase
*********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

// Función para leer el arreglo desde un archivo
void leer_arreglo(const char* archivo, int* n, int** arreglo) {
    FILE* f = fopen(archivo, "r");
    if (!f) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    // Leer la cantidad de elementos
    fscanf(f, "%d", n);
    *arreglo = malloc(*n * sizeof(int));

    // Leer los enteros del archivo
    char buffer[1024];
    fscanf(f, "%s", buffer);

    // Tokenizar el buffer
    char* token = strtok(buffer, ",");
    int i = 0;
    while (token != NULL && i < *n) {
        (*arreglo)[i++] = atoi(token);
        token = strtok(NULL, ",");
    }

    fclose(f);
}

// Función para calcular la suma 
int suma(int* arreglo, int n) {
    
    int total_cant = 0;
    for (int i = 0; i < n; i++) {
        total_cant += arreglo[i];
    }
    return total_cant;
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Uso: %s N1 archivo00 N2 archivo01\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Declarar el tamaño de los arreglos
    int N1 = atoi(argv[1]);
    char* archivo00 = argv[2];
    int N2 = atoi(argv[3]);
    char* archivo01 = argv[4];

    int *arreglo1 = NULL, *arreglo2 = NULL;

    // Leer los arreglos de los archivos
    leer_arreglo(archivo00, &N1, &arreglo1);
    leer_arreglo(archivo01, &N2, &arreglo2);

    // Crear pipes para comunicación entre procesos
    int fd1[2], fd2[2], fd3[2];
    pipe(fd1); 
    pipe(fd2); 
    pipe(fd3);

    pid_t pid1 = fork();
    if (pid1 == 0) { // Primer hijo
        close(fd1[0]); 
        int sumaA = suma(arreglo1, N1);
        printf("GranHijo: [%d] Sum_File1 = %d \n", getpid(), sumaA);
        write(fd1[1], &sumaA, sizeof(sumaA));
        close(fd1[1]);
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) { // Segundo hijo
        close(fd2[0]); 
        int sumaB = suma(arreglo2, N2);
        printf("SegundoHijo: [%d] Sum_File2 = %d \n", getpid(), sumaB);
        write(fd2[1], &sumaB, sizeof(sumaB));
        close(fd2[1]);
        exit(0);
    }

    pid_t pid3 = fork();
    if (pid3 == 0) { // Tercer hijo
        // Cerrar escritura en ambos pipes
        close(fd1[1]); 
        close(fd2[1]); 

        int sumaA, sumaB;
        read(fd1[0], &sumaA, sizeof(sumaA));
        read(fd2[0], &sumaB, sizeof(sumaB));

        int total_cant = sumaA + sumaB;
        printf("PrimerHijo: [%d] Suma total_cant = %d \n", getpid(), total_cant);
        write(fd3[1], &total_cant, sizeof(total_cant));

        // Cerrar lectura en todos los pipes
        close(fd1[0]); 
        close(fd2[0]); 
        close(fd3[1]); 
        exit(0);
    }

    // Proceso padre
    close(fd1[1]); 
    close(fd2[1]); 
    close(fd3[1]);

    int total_cant;
    read(fd3[0], &total_cant, sizeof(total_cant));
    printf("Padre: [%d] Suma total_cant = %d \n", getpid(), total_cant);

    // Liberar memoria
    free(arreglo1); 
    free(arreglo2);

    return 0;
}