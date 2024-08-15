# Ciberseguridad
Repositorio creado para guardar el progreso de la tarea Seguridad Informatica

******************************************************************************************************************************************************************************************************************************
**Keylogger en C para Linux (Ubuntu)**

**Descripción del programa**
   
    • Este programa es un keylogger simple desarrollado en C el cual captura las teclas presionadas en un teclado y las guarda en un archivo de extensión .txt. El programa está diseñado para ejecutarse en sistemas Linux y accede directamente a los dispositivos de entrada del sistema.
    
**Pasos para compilar y ejecutar**

    • Guarda el archivo en una extensión .c ejemplo = keylogger.c
    • Encuentra la dirección de medicante cd para dirigirte a una carpeta y ls revisando los archivos de la carpeta.
    • Compila el programa con: gcc -o keylogger keylogger.c
    • Ejecuta el programa con permisos de superusuario: sudo ./keylogger
    • El programa comenzará a capturar las teclas presionadas y las guardará en el archivo especificado por la constante LOGFILEPATH.

**Pasos para visualizar el archivo de log** 

    • Para abrir el archivo .txt y monitorear como se van guardando los cambios tenemos que dirigirnos desde otra terminal utilizando el código: cat “Ruta del archivo (nombredelprograma.txt)”
    • Para que se actualice en tiempo real utilizamos el código: tail -f /”Ruta”/Archivo.txt
      
**Finalizar programa:**

    • Como el programa tiene un ciclo while que no tiene fin tenemos que presionar Ctrl + C para finalizar el programa.
    
**Características** 

    ▪ Asumimos que hay un dispositivo de teclado conectado y que el programa puede identificarlo a través del comando cat /proc/bus/input/devices.
            ▪ El usuario que ejecuta el programa tiene los permisos necesarios para acceder al dispositivo de entrada del teclado (/dev/input/event*) y para escribir en el archivo de log.
            ▪ El sistema operativo que utilizamos es Linux y el programa se ejecuta en un entorno compatible donde se pueden acceder a los dispositivos de entrada directamente a través de /dev/input/.
            ▪ El programa asume que el teclado está configurado de manera estandar y que los códigos de teclas pueden mapearse directamente a caracteres ASCII.

**Casos de uso**

    • Un administrador de sistemas podría usar este programa para monitorear la entrada del teclado en un sistema específico, buscando que no se rompan las reglas de uso de un dispositivo de la empresa
    • Podemos usar este programa en un entorno controlado para pruebas de seguridad, como parte de una auditoría para detectar vulnerabilidades relacionadas con la captura no autorizada de entrada de teclado.

**Advertencias y consideraciones éticas**

    • Debemos utilizar este programa únicamente en entornos controlados, con propósitos educativos, de prueba, o con el permiso necesario.
