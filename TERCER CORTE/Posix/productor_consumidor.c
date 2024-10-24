/********************************
Fecha: 24/10/2024
Autores: Daniel Gonzalez
Materia: Sistemas Operativos
Tema: Taller 5 - Poroductor y consumidor

Descripción:
        Este programa permite la comunicación bidireccional de un productor y un consumidor usando 
        NamePipes y un archivo FiFO.
********************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Variables compartidas y configuraciones iniciales
int counter = 0; // Contador que representa los recursos producidos/consumidos
int max = 4; // Número máximo de hilos productor y consumidor que se ejecutarán

// Declaración de mutex (bloqueos) para evitar condiciones de carrera
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER; // Protección para el acceso al contador
pthread_mutex_t condp_mutex = PTHREAD_MUTEX_INITIALIZER; // Protección para la sincronización del productor
pthread_mutex_t condc_mutex = PTHREAD_MUTEX_INITIALIZER; // Protección para la sincronización del consumidor

// Variables de condición para la sincronización de hilos
pthread_cond_t condVarProd = PTHREAD_COND_INITIALIZER; // Condición que el productor espera
pthread_cond_t condVarCons = PTHREAD_COND_INITIALIZER; // Condición que el consumidor espera

// Función que ejecuta el hilo productor
void *productor() {
    while(1) {
        // Bloqueo del mutex condicional del productor
        pthread_mutex_lock(&condp_mutex);

        // Si el contador ha alcanzado el máximo (10), el productor espera
        while(counter >= 10) {
            pthread_cond_wait(&condVarProd, &condp_mutex); // Espera hasta que el consumidor lo notifique
        }

        // Libera el mutex del productor
        pthread_mutex_unlock(&condp_mutex);

        // Bloquea el acceso al contador para incrementar de forma segura
        pthread_mutex_lock(&counter_mutex);
        counter++; // Incrementa el contador (produce un recurso)

        // Notifica al consumidor que se ha producido un recurso
        pthread_cond_signal(&condVarCons);
        printf("Soy productor %d valor contador = %d\n", (int)pthread_self(), counter); // Muestra el estado del productor

        // Desbloquea el acceso al contador
        pthread_mutex_unlock(&counter_mutex);
        pthread_mutex_unlock(&condp_mutex);

        // Si el contador es igual a 5, el productor duerme 1 segundo
        if(counter == 5)
            sleep(1);
    }
}

// Función que ejecuta el hilo consumidor
void *consumidor() {
    while(1) {
        sleep(1); // El consumidor duerme un segundo antes de consumir
        pthread_mutex_lock(&condc_mutex); // Bloquea el mutex del consumidor

        // Si el contador es 0 o menor, espera a que el productor lo notifique
        while(counter <= 0) {
            pthread_cond_signal(&condVarProd); // Notifica al productor que el contador está en 0
            pthread_cond_wait(&condVarCons, &condc_mutex); // Espera hasta que el productor produzca
        }

        pthread_mutex_unlock(&condc_mutex); // Desbloquea el mutex del consumidor

        // Bloquea el acceso al contador para disminuir de forma segura
        pthread_mutex_lock(&counter_mutex);

        if(counter > 0) {
            printf("Soy consumidor %d valor contador = %d\n", (int)pthread_self(), counter); // Muestra el estado del consumidor
            counter--; // Decrementa el contador (consume un recurso)
            pthread_cond_signal(&condVarProd); // Notifica al productor que ha consumido un recurso
        }

        // Desbloquea el acceso al contador
        pthread_mutex_unlock(&counter_mutex);
        pthread_mutex_unlock(&condc_mutex);
    }
}

// Función principal donde se crean y se gestionan los hilos
int main() {
    pthread_t proHilo[max], conHilo[max]; // Arrays para almacenar los hilos productores y consumidores
    int i;

    // Creación de hilos productores y consumidores
    for(i = 0; i < 5; i++) {
        pthread_create(&proHilo[i], NULL, &productor, NULL); // Crea un hilo productor
        pthread_create(&conHilo[i], NULL, &consumidor, NULL); // Crea un hilo consumidor
    }

    // Se espera a que todos los hilos terminen su ejecución
    for(i = 0; i < 5; i++) {
        pthread_join(proHilo[i], NULL); // Espera a que el hilo productor termine
        pthread_join(conHilo[i], NULL); // Espera a que el hilo consumidor termine
    }

    return 0; // Finaliza el programa
}
