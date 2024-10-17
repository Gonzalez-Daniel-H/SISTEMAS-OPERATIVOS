guardar el codigo gcc ServidorBidreccional.c -o servidor.
./servidor

guardar el codigo gcc ClienteBidreccional.c -o Cliente.
./Cliente

El cliente  envia mensajes al servidor (FIFO_CLIENTE) y otro para recibir respuestas (FIFO_SERVER). Abre ambos FIFOs y entra en un bucle donde solicita al usuario que ingrese un mensaje. Si el mensaje no es "end", lo envía al servidor a través del FIFO y espera una respuesta, la cual imprime junto con su longitud. Si el usuario introduce "end", el cliente envía este mensaje al servidor, imprime un mensaje de despedida y cierra ambos FIFOs, finalizando así la comunicación.

Servidor:
El servidor recibe mensajes del cliente (FIFO_CLIENTE) y enviar respuestas . Crea los FIFOs si no existen y los abre para lectura y escritura. En un bucle infinito, espera recibir un mensaje del cliente, lo imprime y verifica si es "end". Si el mensaje no es "end", el servidor invierte la cadena recibida mediante la función reverse_string y envía la cadena invertida de vuelta al cliente. Al recibir "end", cierra ambos FIFOs y elimina los archivos FIFO, finalizando su ejecución.