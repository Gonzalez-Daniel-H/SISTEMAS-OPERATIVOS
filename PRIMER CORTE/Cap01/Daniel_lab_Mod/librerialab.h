/**************************************************************************************
autor: Daniel Gonzalez
materia: Sistemas Operativos
fecha: 31 - 09 - 2024

Lab de compliacion modular:
    -Primera parte: funcionamiento del codigo
    -Segunda parte: Modularizcion del codigo
    -Ultima parte: Creacion de fichero de automatizacion de compilacion


***************************************************************************************
                INTERFAZ DE LIBRERIA DE FUNCIONES:MENU DE FUNCIONES

***************************************************************************************/
#ifndef _LIBRERIASLAB_H_
#define _LIBRERIASLAB_H_

#define CAPACIDAD_INICIAL 4
/*Creación Estructura de Datos para el Vector, define como se conforma*/
typedef struct vectorDinamico{
        int capacidad;
        int totalElementos;
        void **elementos;
} vectorDinamico;
/* inicia con la capacidad en 4 (declarado linea 8), con 0 elementos y con malloc se guarda espacio en memoria de 4 apuntadores */
void vectorInicio(vectorDinamico *V);

// retorna la cantidad de elementos del vector
int totalVector(vectorDinamico *V);

// imprime la capacidad inicial y por cuanto la va a cambiar, reserva otro espacio de memoria con el contenido de los elementos del vector pero con diferente tamaño, y luego ese espacio se lo asigna al apuntador de elementos del vector.
static void resizeVector(vectorDinamico *V, int capacidad);

/* si llega a la capacidad maximo, multiplica el tamaño por dos dando mas espacio para elementos, ademas le asigna un nuevo elemento al vector*/
void addVector(vectorDinamico *V, void *elemento);

/*libera totalmente el espacioque ocupaban los elementos del vector*/
void freeVector(vectorDinamico *V);

//regresa el valor del elemento al que apunte el indice, cabe reacalcar que verfica que el indice tenga coherencia, si no tiene regesa NULL
void *getVector(vectorDinamico *V, int indice);

//reasigna el valor de uno de los elementos del vector, usando el vector, el indice del elemento y el nuevo valor.
void setVector(vectorDinamico *V, int indice, void *elemento);

//borra e elemento del indice ingresado, no queda un espacio vacio ya que si elimina un valor el siguiente valor aeste pasa al lugar del que se borro y asi sucesivamente, resta uno a los elementos totales y si la totalidad de elemento es mayor a 0  y es 4 veces menor a la capacidad se divide en 2 la capacidad.
void borrarVector(vectorDinamico *V, int indice);

#endif
