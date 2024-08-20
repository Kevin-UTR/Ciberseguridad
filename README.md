# Ciberseguridad
Repositorio creado para guardar avances de **Keylogger**

******************************************************************************************************************************************************************************************************************************
## Keylogger en C para Linux (Ubuntu)


### **Descripción del programa**


+- Este programa es un keylogger simple desarrollado en C el cual captura las teclas presionadas en un teclado y las guarda en un archivo de extensión .txt. 

+-El programa está diseñado para ejecutarse en sistemas Linux y accede directamente a los dispositivos de entrada del sistema.

    
### **Pasos para compilar y ejecutar**


+- CLona el directorio: https://github.com/Kevin-UTR/Ciberseguridad

+- Compila el programa: gcc -o keylogger keylogger.c

+- Ejecuta el programa con permisos de superusuario: sudo ./keylogger

+- El programa comenzará a capturar las teclas presionadas


### **Pasos para visualizar el archivo de log** 

+- Para abrir el archivo .txt y monitorear como se van guardando los cambios tenemos que dirigirnos desde otra terminal: cat “Ruta/del/archivo/(nombredelprograma.txt)”

+- PActualiaciónven tiempo real: tail -f /”Ruta”/Archivo.txt

      
### **Finalizar programa:**

+- Como el programa tiene un ciclo while que no tiene fin tenemos que presionar Ctrl + C para finalizar el programa.

    
### **Características de uso** 

+- Se piensa que hay un dispositivo de teclado siempre conectado y el programa puede identificarlo a través del comando cat /proc/bus/input/devices.

+- El usuario que ejecuta el programa tiene los permisos necesarios para acceder al dispositivo de entrada del teclado (/dev/input/event*) y para escribir en el archivo de log.

+- El sistema operativo que utilizamos es Linux y el programa se ejecuta en un entorno compatible donde se pueden acceder a los dispositivos de entrada directamente a través de /dev/input/.

+- El programa asume que el teclado está configurado de manera estandar y que los códigos de teclas pueden mapearse directamente a caracteres ASCII.


### **Casos de uso**

+- Un administrador de sistemas podría usar este programa para monitorear la entrada del teclado en un sistema específico, buscando que no se rompan las reglas de uso de el mismo.

+- Podemos usar este programa en un entorno controlado para pruebas de seguridad, como parte de una auditoría para detectar vulnerabilidades relacionadas con la captura no autorizada de entrada de teclado.


### **Advertencias y consideraciones éticas**

+- Debemos utilizar este programa únicamente en entornos controlados, con propósitos educativos, de prueba, o con el permiso necesario.
