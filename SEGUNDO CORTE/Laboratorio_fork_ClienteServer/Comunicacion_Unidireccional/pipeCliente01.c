/**************************************************************

Autor: Daniel Gonzalez
Materia: Sistemas Operativos
Fecha: 03/10/24
Tema: Pipe Named o FIFO o Tuberia
Topico: Comunicacion Uni-Direccional

 *********************** CLIENTE **************
*****************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_FILE "MYFIFO"
   int main() {
     int fd;      //Descriptor de archivo para el FIFO  
     int end_process;   //Variable para Cadenas
     int stringlen;  //Longitud de la linea leida
     char readbuf[80];  //Buffer que almacena lo del Usuario
     char end_str[5];   
     
     //Mensaje de bienvenida e instrucciones 
     printf("FIFO_CLIENT: Enviar Mensajes, infinitamente, para terminar, ingresa \"fin.\"\n");
     
     fd = open(FIFO_FILE, O_CREAT|O_WRONLY); //Abre el FIFO en modo escritura
     strcpy(end_str, "end");
  
    // Bucle Infinito
     while (1) {
        printf("Frase: ");
        fgets(readbuf, sizeof(readbuf), stdin);
        stringlen = strlen(readbuf);
        readbuf[stringlen - 1] = '\0';
        end_process = strcmp(readbuf, end_str);
  
        //Si la cadena no es "fin" sigue en el proceso
        if (end_process != 0) {
           write(fd, readbuf, strlen(readbuf));
           printf("La cadena es: \"%s\" y su longitud es %d\n", readbuf, (int)    strlen(readbuf));
        } else {
        //si la cadena es fin termina el proceso
           write(fd, readbuf, strlen(readbuf));
           printf("La cadena es: \"%s\" y su longitud es %d\n", readbuf, (int)    strlen(readbuf));
           close(fd); //Cierra el descriptor
           break; //Sale del bucle
        }
     }
     return 0;
     }
