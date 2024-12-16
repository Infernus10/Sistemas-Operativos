# Actividad v2: Dispositivos de Entrada y Salida  

## Actividad 1: Listar dispositivos conectados

### Observaciones de comandos:
- **lsblk**: Permite visualizar los dispositivos de bloque, como discos duros y particiones. Aparecieron discos y particiones con nombres como `sda`, `sdb` y particiones específicas como `sda1`.
- **lsusb**: Enumeró dispositivos conectados a través de USB, incluyendo teclado y mouse USB.
- **lspci**: Mostró los dispositivos conectados al bus PCI, como la tarjeta gráfica y la tarjeta de red.
- **dmesg | grep usb**: Presentó un registro detallado con mensajes sobre la conexión o desconexión de dispositivos USB.

### Respuestas:
1. **lsblk** muestra dispositivos de almacenamiento como discos duros y sus particiones.
2. La diferencia entre **lsusb** y **lspci** es que `lsusb` se enfoca exclusivamente en dispositivos USB, mientras que `lspci` incluye todos los dispositivos conectados al bus PCI, como tarjetas gráficas o de sonido.
3. **dmesg | grep usb** proporciona información del kernel sobre eventos relacionados con dispositivos USB, como conexiones y problemas detectados.

---

## Actividad 2: Verificar dispositivos de almacenamiento

### Observaciones de comandos:
- **fdisk -l**: Mostró detalles sobre discos y particiones, como el tamaño y el tipo de partición.
- **blkid**: Enumeró los UUID y sistemas de archivos, incluyendo formatos como `ext4` o `NTFS`.
- **df -h**: Indicó los sistemas de archivos montados y el espacio libre disponible en ellos.

### Respuestas:
1. Los dispositivos de almacenamiento detectados incluyen un disco duro principal (`/dev/sda`) y una unidad USB externa (`/dev/sdb`).
2. Las particiones actualmente montadas son `/dev/sda1` como la raíz del sistema (`/`) y `/dev/sdb1` como almacenamiento externo (`/media/usb`).
3. Los sistemas de archivos empleados son `ext4` para las particiones internas y `FAT32` para la unidad USB.

---

## Actividad 3: Explorar dispositivos de entrada

### Observaciones de comandos:
- **cat /proc/bus/input/devices**: Listó dispositivos de entrada como teclado, mouse y un gamepad.
- **evtest**: Registró eventos generados por teclado y mouse, como códigos de teclas presionadas o movimientos.

### Respuestas:
1. El teclado genera eventos que corresponden a la presión y liberación de teclas, mientras que el mouse registra movimientos y clics.
2. Los dispositivos en `/proc/bus/input/devices` incluyen identificadores como nombres, controladores y descripciones, por ejemplo, "keyboard" o "mouse".

---

## Actividad 4: Examinar dispositivos de salida

### Observaciones de comandos:
- **xrandr**: Detectó una pantalla conectada con resolución configurada en `1920x1080`.
- **aplay -l**: Identificó dos tarjetas de sonido disponibles: una integrada y otra USB.
- **lsof /dev/snd/***: Señaló que el proceso `pulseaudio` estaba utilizando la tarjeta de sonido.

### Respuestas:
1. La salida de video disponible es una pantalla con resolución de `1920x1080`.
2. Se detectaron dos dispositivos de sonido: una tarjeta integrada y una externa conectada por USB.
3. El proceso `pulseaudio` es responsable de gestionar la tarjeta de sonido.

---

## Actividad 5: Crear un script de resumen

### Observaciones:
- El script `dispositivos.sh` consolidó toda la información sobre los dispositivos conectados en una sola ejecución.
- Modifiqué el script para guardar la salida en un archivo llamado `resumendispositivos.txt` utilizando el operador de redirección `> resumendispositivos.txt`.

### Respuestas:
1. La principal ventaja de usar un script es la automatización de tareas repetitivas, lo que ahorra tiempo y esfuerzo al recopilar información.
2. Personalizaría el script agregando comandos como `smartctl` para verificar el estado de discos duros o `ip link` para listar interfaces de red.

---

## Actividad 6: Reflexión y discusión

### Respuestas:
1. El comando más útil fue **lsblk**, ya que permite identificar rápidamente los discos y particiones disponibles.
2. Conocer los dispositivos conectados al sistema es crucial para diagnosticar problemas, optimizar recursos y garantizar el correcto funcionamiento de hardware y software.
3. Este conocimiento es fundamental en la administración de sistemas, pues permite configurar y gestionar hardware de manera eficiente, además de solucionar posibles inconvenientes. 