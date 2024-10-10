/********************************************
Fecha: 10 de octubre del 2024
Autor: Daniel Gonzalez
Materia: Sistemas Operativos
objetivo: Aplicar los conceptos vistos en clase
*********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Función para leer el arreglo desde un archivo
void cargar_arreglo(const char* archivo, int* tamano, int** arreglo) {
    FILE* f = fopen(archivo, "r");
    if (!f) {
        perror("Error al abrir archivo");
        exit(EXIT_FAILURE);
    }

    fscanf(f, "%d", tamano);
    *arreglo = malloc(*tamano * sizeof(int));

    char buffer[1024];
    fscanf(f, "%s", buffer);

    char* token = strtok(buffer, ",");
    int i = 0;
    while (token != NULL && i < *tamano) {
        (*arreglo)[i++] = atoi(token);
        token = strtok(NULL, ",");
    }

    fclose(f);
}

// Función para sumar los elementos de un arreglo
int sumar_arreglo(int* arreglo, int tamano) {
    int suma_total = 0;
    for (int i = 0; i < tamano; i++) {
        suma_total += arreglo[i];
    }
    return suma_total;
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Uso: %s N1 archivo1 N2 archivo2\n", argv[0]);
        return EXIT_FAILURE;
    }

    int N1 = atoi(argv[1]), N2 = atoi(argv[3]);
    char* archivo1 = argv[2], *archivo2 = argv[4];

    int *arreglo1 = NULL, *arreglo2 = NULL;

    // Cargar arreglos
    cargar_arreglo(archivo1, &N1, &arreglo1);
    cargar_arreglo(archivo2, &N2, &arreglo2);

    int fd1[2], fd2[2], fd3[2];
    pipe(fd1); 
    pipe(fd2); 
    pipe(fd3);

    pid_t pid1 = fork();
    if (pid1 == 0) { // Primer proceso hijo
        close(fd1[0]);
        int suma1 = sumar_arreglo(arreglo1, N1);
        printf("Proceso A [%d]: Suma archivo1 = %d\n", getpid(), suma1);
        write(fd1[1], &suma1, sizeof(suma1));
        close(fd1[1]);
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) { // Segundo proceso hijo
        close(fd2[0]);
        int suma2 = sumar_arreglo(arreglo2, N2);
        printf("Proceso B [%d]: Suma archivo2 = %d\n", getpid(), suma2);
        write(fd2[1], &suma2, sizeof(suma2));
        close(fd2[1]);
        exit(0);
    }

    pid_t pid3 = fork();
    if (pid3 == 0) { // Tercer proceso hijo
        close(fd1[1]);
        close(fd2[1]);

        int suma1, suma2;
        read(fd1[0], &suma1, sizeof(suma1));
        read(fd2[0], &suma2, sizeof(suma2));

        int suma_total = suma1 + suma2;
        printf("Proceso C [%d]: Suma total = %d\n", getpid(), suma_total);
        write(fd3[1], &suma_total, sizeof(suma_total));

        close(fd1[0]);
        close(fd2[0]);
        close(fd3[1]);
        exit(0);
    }

    close(fd1[1]);
    close(fd2[1]);
    close(fd3[1]);

    int suma_final;
    read(fd3[0], &suma_final, sizeof(suma_final));
    printf("Padre [%d]: Suma final = %d\n", getpid(), suma_final);

    free(arreglo1);
    free(arreglo2);

    return 0;
}