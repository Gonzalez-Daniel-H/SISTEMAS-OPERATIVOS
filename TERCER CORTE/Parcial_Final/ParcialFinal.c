/********************************************
Fecha: 07 de Noviembre del 2024
Autor: Daniel Gonzalez
Materia: Sistemas Operativos
objetivo: Aplicar los conceptos vistos en clase
#include <stdio.h>
*********************************************/
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#define NUM_HILOS 5

sem_t semaforos[NUM_HILOS];

void* funcion_hilo(void* arg) {
    int indice = *(int*)arg;
    free(arg);  // Liberar la memoria asignada para el índice

    // Espera a que su semáforo este disponible
    sem_wait(&semaforos[indice]);

    pthread_t id = pthread_self();  // Obtener el ID real del hilo
    printf("Hilo %lu ha iniciado\n", id);

    // Contador simulado (simplemente para que el hilo haga algo)
    for (int i = 0; i < 300; i++);

    printf("Hilo %lu ha finalizado\n", id);

    // Desbloquear el siguiente semaforo 
    if (indice + 1 < NUM_HILOS) {
        sem_post(&semaforos[indice + 1]);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t hilos[NUM_HILOS];

    // Inicializar los semaforos
    for (int i = 0; i < NUM_HILOS; i++) {
        sem_init(&semaforos[i], 0, 0);
    }

    // Desbloquear el primer semaforo para el primer hilo
    sem_post(&semaforos[0]);

    // Crear los hilos
    for (int i = 0; i < NUM_HILOS; i++) {
        int* indice = malloc(sizeof(int));  
        *indice = i;
        pthread_create(&hilos[i], NULL, funcion_hilo, indice);
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < NUM_HILOS; i++) {
        pthread_join(hilos[i], NULL);
    }

    // Destruir los semaforos
    for (int i = 0; i < NUM_HILOS; i++) {
        sem_destroy(&semaforos[i]);
    }

    return 0;
}

