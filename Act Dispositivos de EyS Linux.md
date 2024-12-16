# Ejercicios de LINUX en Máquina Virtual 

## Ejercicio 1: Montar y Desmontar Discos

 Se inserto una memoria USB en mi máquina virtual y abro la terminal. Escribo:

```bash
lsblk
```

Este comando me muestra una lista de dispositivos y particiones. Identifico mi memoria USB como `/dev/sdb1`.

Creo un directorio donde montaré la memoria:

```bash
sudo mkdir /mnt/usb
sudo mount /dev/sdb1 /mnt/usb
```

Ahora la memoria está montada y puedo acceder a su contenido en `/mnt/usb`.

Verifico que la memoria está montada correctamente:

```bash
df -h
```

Aquí veo la memoria USB listada con su tamaño y uso de espacio.

Copio un archivo a la memoria:

```bash
cp ~/archivo.txt /mnt/usb/
```

El archivo `archivo.txt` de mi directorio personal ahora está en la memoria USB.

Desmonto la memoria USB:

```bash
sudo umount /mnt/usb
```

Ahora es seguro desconectar la memoria USB.

---

## Ejercicio 2: Redirección de Entrada y Salida

Listo los archivos en mi directorio actual y guardo la salida en `listado.txt`:

```bash
ls -l > listado.txt
```

Esto genera un archivo `listado.txt` con el listado de archivos y permisos del directorio.

Verifico el contenido de `listado.txt`:

```bash
cat listado.txt
```

Veo en la terminal la lista de archivos que se guardó en el archivo.

Añado la fecha actual al archivo:

```bash
date >> listado.txt
```

Ahora, al final de `listado.txt`, se añade la fecha y hora actuales.

Reviso nuevamente el archivo para confirmar:

```bash
cat listado.txt
```

Veo el contenido original más la fecha añadida.

## Ejercicio 3: Copiar y Mover Archivos

Creo un archivo llamado `archivo1.txt`:

```bash
echo "Este es un archivo de prueba" > archivo1.txt
```

Esto crea un archivo con el texto "Este es un archivo de prueba".

Copio el archivo al directorio `/tmp`:

```bash
cp archivo1.txt /tmp/
```

Ahora hay una copia de `archivo1.txt` en `/tmp`.

Renombro el archivo en `/tmp`:

```bash
mv /tmp/archivo1.txt /tmp/archivo2.txt
```

El archivo en `/tmp` ahora se llama `archivo2.txt`.

Muevo el archivo `archivo2.txt` de vuelta a mi directorio actual:

```bash
mv /tmp/archivo2.txt .
```

Ahora el archivo `archivo2.txt` está en mi directorio actual.



## Ejercicio 4: Comprimir y Descomprimir Archivos

Creo un directorio llamado `backup` y copio algunos archivos en él:

```bash
mkdir backup
cp archivo1.txt archivo2.txt backup/
```

Esto crea el directorio `backup` y copia `archivo1.txt` y `archivo2.txt` dentro de él.

Comprimí el directorio `backup` en un archivo `.tar.gz`:

```bash
tar -czvf backup.tar.gz backup/
```

Esto genera el archivo `backup.tar.gz` que contiene el directorio comprimido.

Borro el directorio original:

```bash
rm -r backup/
```

El directorio `backup` se elimina, quedando solo el archivo comprimido.

Extraigo el contenido del archivo comprimido para restaurarlo:

```bash
tar -xzvf backup.tar.gz
```

Esto recrea el directorio `backup` con los archivos originales.


## Ejercicio 5: Permisos y Propiedades de Archivos

Creo un archivo llamado `privado.txt`:

```bash
touch privado.txt
```

Esto genera un archivo vacío llamado `privado.txt`.

Cambio los permisos para que solo el propietario pueda leer y escribir:

```bash
chmod 600 privado.txt
```

Ahora solo el propietario tiene acceso al archivo.

Cambio el propietario del archivo (necesito ser administrador):

```bash
sudo chown otro_usuario privado.txt
```

El archivo ahora pertenece al usuario `otro_usuario`.

---


## Ejercicio 6: Exploración de Dispositivos

Listo los discos y particiones con:

```bash
lsblk
```

Esto me muestra todos los discos conectados y cómo están particionados.

Verifico el tamaño de un directorio específico:

```bash
du -sh ~/Documentos
```

El comando me devuelve el tamaño total del contenido en la carpeta `Documentos`.

Compruebo el uso de disco general:

```bash
df -h
```

Veo el uso y disponibilidad de espacio en todas las particiones del sistema.



## Ejercicio 7: Crear y Formatear Particiones

Identifico un disco no particionado:

```bash
sudo fdisk -l
```

Encuentro un disco sin particiones, por ejemplo, `/dev/sda1`.

Creo una nueva partición en el disco:

```bash
sudo fdisk /dev/sdc
```

Dentro de `fdisk`, utilizo las opciones:

- `n` para nueva partición
- `p` para partición primaria

Selecciono el tamaño y guardo con `w`.

Formateo la partición recién creada como `ext4`:

```bash
sudo mkfs.ext4 /dev/sdc1
```

Esto prepara la partición para ser usada.

Creo un punto de montaje y monto la nueva partición:

```bash
sudo mkdir /mnt/nueva_particion
sudo mount /dev/sdc1 /mnt/nueva_particion
```

Escribo un archivo de prueba:

```bash
echo "Prueba de escritura" > /mnt/nueva_particion/test.txt
```


