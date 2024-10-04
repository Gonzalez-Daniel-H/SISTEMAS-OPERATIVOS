/**************************************************************
Autor: Daniel Gonzalez
Materia: Sistemas Operativos
Fecha: 03/10/24
Tema: Pipe Named o FIFO o Tuberia
Topico: Comunicacion Uni-Direccional

 *********************** SERVIDOR **************
*****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


#define FIFO_FILE "MYFIFO"

int main() {
     int fd;
     char readbuf[80];
     char end[10];
     int to_end;
     int read_bytes;
     
    printf("\n\t <<< BIENVENIDOS AL SERVIDOR >>> \n");
    printf("┌───────────────────────────────────────────────┐\n");
    printf("│                Estado del Servidor            │\n");
    printf("├───────────────────────────────────────────────┤\n");
    printf("│ Estado: ✅ En funcionamiento                  │\n");
    printf("│ Conexiones: 12 / 100                          │\n");
    printf("│ Uptime: 5 días, 3 horas                       │\n");
    printf("| Acontinuacion Iniciaran los mensajes          |\n");                     
    printf("└───────────────────────────────────────────────┘\n");

     /* Crea el FIFO si no existe */
     mknod(FIFO_FILE, S_IFIFO|0640, 0); //Crea un FIFO con permisos de escritura y lectura
     strcpy(end, "fin");//Copia la cadena "fin" en la variable 'end'
     while(1) {
        fd = open(FIFO_FILE, O_RDONLY); //Abre el FIFO en lectura
        read_bytes = read(fd, readbuf, sizeof(readbuf)); //Lee el FIFO
               readbuf[read_bytes] = '\0'; //Añade un nulo a cada final de linea
               
               //Imprime lo que recibio del usuaio y la longitud
               printf("El mensaje que recibimos es : \"%s\" y su longitud es %d\n", readbuf, (int)strlen    (readbuf));
               //Compara el mensaje con fin
        to_end = strcmp(readbuf, end);
        //Si el emnsaje  es "fin", cierra el programa
        if (to_end == 0) {
           close(fd);
           break;//Sale del bucle
        }
     }
     }
