/********************************************
Fecha: 10 de octubre del 2024
Autor: Daniel Gonzalez
Materia: Sistemas Operativos
objetivo: Aplicar los conceptos vistos en clase
*********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int* cargar_arreglo(const char* archivo, int* tamano) {
    FILE* f = fopen(archivo, "r");
    if (!f) {
        perror("Error al abrir archivo");
        exit(EXIT_FAILURE);
    }

    fscanf(f, "%d", tamano);  // Leer tamaño del arreglo
    int* arreglo = (int*)malloc((*tamano) * sizeof(int));
    if (!arreglo) {
        perror("Error al asignar memoria");
        fclose(f);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *tamano; i++) {
        fscanf(f, "%d", &arreglo[i]);
    }

    fclose(f);
    return arreglo;
}

int sumar_arreglo(int* arreglo, int tamano) {
    int suma = 0;
    for (int i = 0; i < tamano; i++) {
        suma += arreglo[i];
    }
    return suma;
}

void procesar_arreglo(const char* archivo, int tamano, int* pipe_fd) {
    int* arreglo = cargar_arreglo(archivo, &tamano);

    pid_t pid = fork();
    if (pid == -1) {
        perror("Error al crear proceso");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Proceso hijo
        close(pipe_fd[0]); 
        int suma = sumar_arreglo(arreglo, tamano);
        printf("Proceso [%d]: Suma de %s = %d\n", getpid(), archivo, suma);
        write(pipe_fd[1], &suma, sizeof(suma));
        close(pipe_fd[1]); 
        free(arreglo);
        exit(0);
    }

    free(arreglo);
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Uso: %s N1 archivo1 N2 archivo2\n", argv[0]);
        return EXIT_FAILURE;
    }

    int N1 = atoi(argv[1]);
    int N2 = atoi(argv[3]);
    const char* archivo1 = argv[2];
    const char* archivo2 = argv[4];

    int pipe_fd1[2], pipe_fd2[2];
    if (pipe(pipe_fd1) == -1 || pipe(pipe_fd2) == -1) {
        perror("Error al crear pipes");
        exit(EXIT_FAILURE);
    }

    // Procesar el primer archivo en un proceso hijo
    procesar_arreglo(archivo1, N1, pipe_fd1);

    // Procesar el segundo archivo en otro proceso hijo
    procesar_arreglo(archivo2, N2, pipe_fd2);

    // Proceso padre
    close(pipe_fd1[1]);  
    close(pipe_fd2[1]);  

    int suma1, suma2;
    read(pipe_fd1[0], &suma1, sizeof(suma1));  
    read(pipe_fd2[0], &suma2, sizeof(suma2));  

    close(pipe_fd1[0]);  
    close(pipe_fd2[0]);  

    int suma_total = suma1 + suma2;
    printf("Padre [%d]: Suma total = %d\n", getpid(), suma_total);

    wait(NULL);
    wait(NULL);

    return 0;
}