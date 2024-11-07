/********************************************
Fecha: 07 de Noviembre del 2024
Autor: Daniel Gonzalez
Materia: Sistemas Operativos
objetivo: Aplicar los conceptos vistos en clase
*********************************************/
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#define NUM_THREADS 5

sem_t semaphores[NUM_THREADS]; // Un arreglo de semaforos para controlar el orden de ejecucion

void* threadFunction(void* threadid) {
    long tid = (long)threadid;

    // Espera en el semaforo correspondiente
    sem_wait(&semaphores[tid]);

    // Imprime mensaje de inicio
    printf("Hilo %ld ha iniciado\n", tid);

    // Bucle que cuenta hasta 300
    for (int i = 0; i < 300; i++) {
        // Simulacion de trabajo, el bucle no hace nada especifico
    }

    // Imprime mensaje de finalización
    printf("Hilo %ld ha finalizado\n", tid);

    // Libera el siguiente semaforo si no es el altimo hilo
    if (tid < NUM_THREADS - 1) {
        sem_post(&semaphores[tid + 1]);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    long t;

    for (t = 0; t < NUM_THREADS; t++) {
        sem_init(&semaphores[t], 0, (t == 0) ? 1 : 0); 
    }

    // Creacion de los hilos
    for (t = 0; t < NUM_THREADS; t++) {
        if (pthread_create(&threads[t], NULL, threadFunction, (void*)t)) {
            fprintf(stderr, "Error al crear el hilo %ld\n", t);
            exit(1);
        }
    }

    // Esperar a que todos los hilos terminen
    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    for (t = 0; t < NUM_THREADS; t++) {
        sem_destroy(&semaphores[t]);
    }

    pthread_exit(NULL);
}
