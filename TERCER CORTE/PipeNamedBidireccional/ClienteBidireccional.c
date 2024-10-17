/**************************************************************


Autor: Daniel Gonzalez
Materia: Sistemas Operativos
Fecha: 17/10/24
Tema: Pipe Named o FIFO o Tuberia
Topico: Comunicacion Uni-Direccional
El cliente  envia mensajes al servidor (FIFO_CLIENTE) y otro para recibir respuestas (FIFO_SERVER). 
Abre ambos FIFOs y entra en un bucle donde solicita al usuario que ingrese un mensaje. Si el mensaje no es "end", lo envía al servidor a través del FIFO y espera una respuesta, 
la cual imprime junto con su longitud. Si el usuario introduce "end", el cliente envía este mensaje al servidor, imprime un mensaje de despedida y cierra ambos FIFOs, finalizando 
así la comunicación.

 *********************** CLIENTE **************
*****************************************************************/
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO_CLIENT "FIFO_CLIENTE" // FIFO para enviar mensajes al servidor
#define FIFO_SERVER "FIFO_SERVER"  // FIFO para recibir mensajes del servidor

int main() {
    int fd_client, fd_server;
    int end_process;
    int stringlen;
    int read_bytes;
    char readbuf[80];
    char end_str[5];

    printf("FIFO_CLIENT: Send messages, to end enter \"end\"\n");

    // Abre los FIFOs: escribe en el cliente y lee del servidor
    fd_client = open(FIFO_CLIENT, O_WRONLY); // Cliente escribe en FIFO_CLIENTE
    fd_server = open(FIFO_SERVER, O_RDONLY); // Cliente lee de FIFO_SERVER

    strcpy(end_str, "end");

    while (1) {
        printf("Enter string: ");
        fgets(readbuf, sizeof(readbuf), stdin);
        stringlen = strlen(readbuf);
        readbuf[stringlen - 1] = '\0'; // Elimina el salto de lÃ­nea final
        end_process = strcmp(readbuf, end_str);

        if (end_process != 0) {
            // Enviar mensaje al servidor
            write(fd_client, readbuf, strlen(readbuf));
            printf("FIFO_CLIENT: Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));

            // Leer respuesta del servidor
            read_bytes = read(fd_server, readbuf, sizeof(readbuf));
            readbuf[read_bytes] = '\0';
            printf("FIFO_CLIENT: Received string: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf));
        } else {
            // Enviar el mensaje de finalizaciÃ³n
            write(fd_client, readbuf, strlen(readbuf));
            printf("FIFO_CLIENT: Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));
            close(fd_client);
            close(fd_server);
            break;
        }
    }
    return 0;
}

