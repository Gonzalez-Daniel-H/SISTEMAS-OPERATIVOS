/**************************************************************************************
autor: Daniel Gonzalez
materia: Sistemas Operativos
fecha: 31 - 09 - 2024

Lab de compliacion modular:
    -Primera parte: funcionamiento del codigo
    -Segunda parte: Modularizcion del codigo
    -Ultima parte: Creacion de fichero de automatizacion de compilacion


***************************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "librerialab.h"

#define CAPACIDAD_INICIAL 4


int main(){
        int i;
        vectorDinamico editor;
        vectorInicio(&editor);

        addVector(&editor, "Hola");
        addVector(&editor, "Profesional");
        addVector(&editor, "en");
        addVector(&editor, "formacion");
        addVector(&editor, "de");
        addVector(&editor, "ingenieria");
         

        for (i = 0; i < totalVector(&editor); i++)
          printf("%s ", (char *) getVector(&editor, i));
        printf("\n");
        borrarVector(&editor, 1);
        borrarVector(&editor, 1);
        borrarVector(&editor, 1);
        borrarVector(&editor, 1);
        
        setVector(&editor, 1, "Buenos");
        addVector(&editor, "dias");


        for (i = 0; i < totalVector(&editor); i++)
        printf("%s ", (char *) getVector(&editor, i));
        freeVector(&editor);  
  }
