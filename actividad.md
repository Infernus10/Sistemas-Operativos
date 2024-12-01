
### BRUNO LEONARDO PARRA FERNANDEZ - 22121338

### Administración de Memoria

#### 3.1 Política y filosofía

1. **¿Cuál es la diferencia entre fragmentación interna y externa? Explique cómo cada una afecta el rendimiento de la memoria.**

   - **Fragmentación interna:** 
   Es la pérdida de espacio en disco o memoria debido a que el tamaño de un archivo o proceso es menor que el tamaño del bloque o cluster asignado. Esto ocurre porque los bloques tienen un tamaño fijo, y si un archivo ocupa menos espacio que el bloque, la parte sobrante no se puede utilizar para otros archivos.
    
     - **Impacto en el rendimiento:** 
     Reduce la capacidad útil del almacenamiento, ya que el espacio desaprovechado no puede reutilizarse. No afecta directamente la velocidad de acceso, pero puede ser un problema en sistemas con almacenamiento limitado.

   - **Fragmentación externa:** 
   Aparece cuando los bloques libres en disco o memoria no son contiguos, debido a la creación y eliminación sucesiva de archivos o procesos de diferentes tamaños. Esto genera huecos dispersos en el espacio libre, que no pueden ser utilizados si un archivo o proceso necesita un bloque mayor que los fragmentos disponibles.

     - **Impacto en el rendimiento:** 
     Dificulta la asignación de memoria o almacenamiento, ya que los huecos pequeños no pueden satisfacer ciertas aplicaciones.

2. **Investiga y explica las políticas de reemplazo de páginas en sistemas operativos. ¿Cuál consideras más eficiente y por qué?**

   - **Políticas de reemplazo de páginas:**

     - **FIFO (First-In, First-Out):**
     
      Reemplaza la página que lleva más tiempo en memoria. Es fácil de implementar, pero puede eliminar las páginas que se siguen utilizando, aumentando los errores de página.
     
     - **LRU (Least Recent Used):**
     
      Reemplaza la página menos utilizada recientemente. Captura la localidad temporal, reduciendo errores de página, pero requiere estructuras de datos más complejas para rastrear accesos.

     - **LFU (Least Frequency Used):**

      Reemplaza la página menos utilizada en términos de frecuencia. Favorece páginas con usos frecuentes, pero puede mantener páginas antiguas que ya no se usan, causando ineficiencia.
     
     - **OPT (Óptima):** 
     
     Reemplaza la página que no se usará durante más tiempo en el futuro. Es ideal en teoría, ya que minimiza los errores de página, pero no es práctica porque requiere conocer los accesos futuros.

   - **MI ELECCION MAS EFICIENTE:**

    LRU se considera la más eficiente en la práctica, ya que aprovecha la localidad temporal de referencia, reduciendo significativamente los errores de página.

#### 3.2 Memoria real

1. **Escribe un programa en C o Python que simule la administración de memoria mediante particiones fijas.**

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PARTICIONES 10
#define MAX_PROCESOS 10

typedef struct {
    int tamano;
    bool ocupado;
    int proceso_id;
} Particion;

typedef struct {
    int id;
    int tamano;
    int particion_asignada;
} Proceso;

Particion particiones[MAX_PARTICIONES];
Proceso procesos[MAX_PROCESOS];
int num_particiones = 0;
int num_procesos = 0;

void mostrar_memoria() {
    if (num_particiones == 0) {
        printf("No hay particiones definidas. Por favor, configura las particiones primero.\n");
        return;
    }
    printf("Estado de la memoria:\n");
    for (int i = 0; i < num_particiones; i++) {
        printf("Partición %d: Tamano = %d KB, ", i + 1, particiones[i].tamano);
        if (particiones[i].ocupado)
            printf("Ocupado por Proceso %d\n", particiones[i].proceso_id);
        else
            printf("Libre\n");
    }
}

void definir_particiones() {
    int tamano_total, tamano;
    printf("Define el tamaño total de la memoria (en KB): ");
    scanf("%d", &tamano_total);
    printf("Cuantas particiones quieres crear (max %d): ", MAX_PARTICIONES);
    scanf("%d", &num_particiones);
    int suma_tamanos = 0;
    for (int i = 0; i < num_particiones; i++) {
        printf("Tamano de la partición %d (en KB): ", i + 1);
        scanf("%d", &tamano);
        if (suma_tamanos + tamano > tamano_total) {
            printf("No hay suficiente memoria restante. Intenta un tamano menor.\n");
            i--;
            continue;
        }
        particiones[i].tamano = tamano;
        particiones[i].ocupado = false;
        particiones[i].proceso_id = -1;
        suma_tamanos += tamano;
    }
    printf("Particiones configuradas correctamente.\n");
}

void asignar_proceso() {
    if (num_particiones == 0) {
        printf("No hay particiones definidas. Por favor, configura las particiones primero.\n");
        return;
    }
    int tamano;
    printf("Tamano del nuevo proceso (en KB): ");
    scanf("%d", &tamano);
    for (int i = 0; i < num_particiones; i++) {
        if (!particiones[i].ocupado && particiones[i].tamano >= tamano) {
            procesos[num_procesos].id = num_procesos + 1;
            procesos[num_procesos].tamano = tamano;
            procesos[num_procesos].particion_asignada = i;
            particiones[i].ocupado = true;
            particiones[i].proceso_id = procesos[num_procesos].id;
            printf("Proceso %d asignado a la particion %d\n", procesos[num_procesos].id, i + 1);
            num_procesos++;
            return;
        }
    }
    printf("No hay particiones disponibles para este proceso.\n");
}

void liberar_proceso() {
    if (num_particiones == 0) {
        printf("No hay particiones definidas. Por favor, configura las particiones primero.\n");
        return;
    }
    int proceso_id;
    printf("ID del proceso a liberar: ");
    scanf("%d", &proceso_id);
    for (int i = 0; i < num_particiones; i++) {
        if (particiones[i].ocupado && particiones[i].proceso_id == proceso_id) {
            particiones[i].ocupado = false;
            particiones[i].proceso_id = -1;
            printf("Proceso %d liberado de la particion %d\n", proceso_id, i + 1);
            return;
        }
    }
    printf("Proceso no encontrado.\n");
}

int main() {
    int opcion;
    while (1) {
        printf("\nMenú: \n");
        printf("1. Definir o redefinir particiones\n");
        printf("2. Asignar proceso\n");
        printf("3. Liberar proceso\n");
        printf("4. Mostrar memoria\n");
        printf("5. Salir\n");
        printf("Elige una opción: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1: definir_particiones(); break;
            case 2: asignar_proceso(); break;
            case 3: liberar_proceso(); break;
            case 4: mostrar_memoria(); break;
            case 5: printf("Saliendo del programa.\n"); return 0;
            default: printf("Opcion invalida. Intenta de nuevo.\n");
        }
    }
    return 0;
}
```

2. **Diseña un algoritmo para calcular qué procesos pueden ser asignados a un sistema con memoria real limitada utilizando el algoritmo de "primera cabida".**

```c
#include <stdio.h>

typedef struct {
    int size;
    int is_occupied;
} Block;

typedef struct {
    int id;
    int size;
} Process;

void allocateMemory(Block blocks[], int num_blocks, Process processes[], int num_processes) {
    for (int i = 0; i < num_processes; i++) {
        int assigned = 0;
        for (int j = 0; j < num_blocks; j++) {
            if (!blocks[j].is_occupied && blocks[j].size >= processes[i].size) {
                blocks[j].is_occupied = 1;
                printf("Proceso %d asignado a bloque de tamaño %d\n", processes[i].id, blocks[j].size);
                assigned = 1;
                break;
            }
        }
        if (!assigned) {
            printf("El proceso %d no pudo ser asignado: no hay suficiente memoria.\n", processes[i].id);
        }
    }
}

void displayMemory(Block blocks[], int num_blocks) {
    printf("\nEstado de la memoria:\n");
    for (int i = 0; i < num_blocks; i++) {
        if (blocks[i].is_occupied) {
            printf("Bloque %d: Ocupado\n", i + 1);
        } else {
            printf("Bloque %d: Libre\n", i + 1);
        }
    }
}
```

## 3.3 Organización de memoria virtual

### 1. Investiga y explica el concepto de "paginación" y "segmentación". ¿Cuáles son las ventajas y desventajas de cada técnica?

**Paginación**

La paginación es un mecanismo de almacenamiento que permite al sistema operativo recuperar procesos del almacenamiento secundario a la memoria principal en forma de páginas. En el método de paginación, la memoria principal se divide en pequeños bloques de direcciones físicas de tamaño fijo, que se denominan tramas.

**Segmentación**

El método de segmentación funciona de manera similar a la paginación, pero la diferencia principal es que los segmentos son de longitud variable, mientras que en el método de paginación, las páginas siempre tienen un tamaño fijo. Un segmento de programa incluye la función principal del programa, las estructuras de datos, y las funciones de utilidad.

**Ventajas de la paginación**

- Gestión de memoria fácil de usar.
- No hay necesidad de fragmentacion externa.
- El intercambio es fácil entre páginas y marcos de página del mismo tamaño.

**Desventajas de la paginación**

- Puede causar fragmentación interna.
- Las tablas de páginas consumen memoria adicional.
- La paginación multinivel puede generar una sobrecarga de referencia de memoria.

**Ventajas de la segmentación**

- Ofrece protección dentro de los segmentos.
- Puede lograr compartir segmentando y haciendo referencia a múltiples procesos.
- No ofrece fragmentación interna.
- Las tablas de segmentos usan menos memoria que la paginación.

**Desventajas de la segmentación**

- Los procesos se cargan o eliminan de la memoria principal, separando el espacio libre de memoria en pequeños trozos, lo que puede crear un problema de fragmentación externa.
- Algoritmo costoso de gestión de memoria.

### 2. Escribe un programa que simule una tabla de páginas para procesos con acceso aleatorio a memoria virtual.

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VIRTUAL_PAGES 16 
#define PHYSICAL_FRAMES 8 
#define PAGE_SIZE 256 
#define ACCESS_COUNT 10 


typedef struct {
    int valid; 
    int frame; 
} PageTableEntry;


void initializePageTable(PageTableEntry *pageTable) {
    for (int i = 0; i < VIRTUAL_PAGES; i++) {
        pageTable[i].valid = rand() % 2; 
        pageTable[i].frame = pageTable[i].valid ? rand() % PHYSICAL_FRAMES : -1;
    }
}


void translateAddress(PageTableEntry *pageTable, int virtualAddress) {
    int pageNumber = virtualAddress / PAGE_SIZE;
    int offset = virtualAddress % PAGE_SIZE;
    if (pageNumber >= VIRTUAL_PAGES) {
        printf("Error: Dirección virtual %d fuera del rango.\n", virtualAddress);
        return;
    }
    PageTableEntry entry = pageTable[pageNumber];
    if (entry.valid) {
        int physicalAddress = entry.frame * PAGE_SIZE + offset;
        printf("Virtual: %d -> Física: %d (Página %d -> Marco %d, Desplazamiento %d)\n",
               virtualAddress, physicalAddress, pageNumber, entry.frame, offset);
    } else {
        printf("Virtual: %d -> Página no válida (Página %d no mapeada).\n",
               virtualAddress, pageNumber);
    }
}

int main() {
    PageTableEntry pageTable[VIRTUAL_PAGES];
    srand(time(NULL)); 


    initializePageTable(pageTable);

    printf("Tabla de páginas:\n");
    for (int i = 0; i < VIRTUAL_PAGES; i++) {
        printf("Página %d: %s, Marco: %d\n", i, pageTable[i].valid ? "Válida" : "Inválida", pageTable[i].frame);
    }
    printf("\n");

    
    printf("Accesos aleatorios a direcciones virtuales:\n");
    for (int i = 0; i < ACCESS_COUNT; i++) {
        int virtualAddress = rand() % (VIRTUAL_PAGES * PAGE_SIZE);
        translateAddress(pageTable, virtualAddress);
    }

    return 0;
}
```
#### 3.4 Administración de memoria virtual

**1.  Escribe un código que implemente el algoritmo de reemplazo de página "Least Recently Used" (LRU).**
```c
#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 4 
#define MAX_REFERENCES 20 

int findLRU(int time[], int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

void lruPageReplacement(int pages[], int n, int frames) {
    int frame[MAX_FRAMES]; 
    int time[MAX_FRAMES];  
    int count = 0; 
    int pageFaults = 0; 
    int pageHits = 0;   
    int flag1, flag2;

  
    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
        time[i] = 0;
    }

    printf("Secuencia de referencia:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n\n");

    printf("Estado de los marcos:\n");
    for (int i = 0; i < n; i++) {
        flag1 = flag2 = 0; 
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                flag1 = flag2 = 1;
                time[j] = ++count;
                pageHits++;
                break;
            }
        }

        if (flag1 == 0) {
            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    frame[j] = pages[i];
                    time[j] = ++count;
                    pageFaults++;
                    flag2 = 1;
                    break;
                }
            }
        }

        if (flag2 == 0) {
            int pos = findLRU(time, frames);
            frame[pos] = pages[i];
            time[pos] = ++count;
            pageFaults++;
        }

        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1) {
                printf("%d ", frame[j]);
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }

    printf("\nTotal de fallos de página: %d\n", pageFaults);
    printf("Total de aciertos de página: %d\n", pageHits);
}

int main() {
    int pages[MAX_REFERENCES];
    int n, frames;

    printf("Ingrese el número de referencias a páginas: ");
    scanf("%d", &n);
    printf("Ingrese la secuencia de referencias a páginas:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    printf("Ingrese el número de marcos disponibles: ");
    scanf("%d", &frames);

    if (frames > MAX_FRAMES) {
        printf("El número de marcos no puede exceder %d.\n", MAX_FRAMES);
        return 1;
    }

    lruPageReplacement(pages, n, frames);
    return 0;
}
```
### 2. Diseña un diagrama que represente el proceso de traducción de direcciones virtuales a físicas en un sistema con memoria virtual

El proceso de traducción de direcciones virtuales a físicas en un sistema con memoria virtual se realiza a través de una **Tabla de Páginas**, la cual mapea las direcciones virtuales a las físicas. 
Este proceso incluye varios pasos, como la consulta de la tabla de páginas, la búsqueda de la página en memoria y, si es necesario, la gestión de los fallos de página.



**Diagrama de traducción de direcciones virtuales a físicas**(https://chsos20122910022.wordpress.com/wp-content/uploads/2012/10/imagen4.jpg)



### Integración: 

**Análisis de la administración de memoria virtual en sistemas operativos modernos**

En sistemas operativos modernos como *Windows*, la administración de memoria virtual es un aspecto clave para gestionar la memoria de manera eficiente, permitiendo que cada proceso tenga la impresión de estar utilizando toda la memoria disponible, aunque esta sea limitada. A continuación se detallan algunos aspectos importantes de cómo Windows administra la memoria virtual:

#### Windows (32 y 64 bits)

- **Sistemas de 32 bits**: 

  El espacio de direcciones virtuales es de 4 GB, donde 2 GB están destinados al proceso (o hasta 3 GB si se habilita la opción /3GB en el kernel) y los 2 GB restantes son reservados para el sistema operativo.

- **Sistemas de 64 bits**: 

  El espacio de direcciones virtuales es mucho mayor, alcanzando hasta *256 TB* dependiendo de la edición de Windows. Cada proceso tiene su propio espacio de direcciones virtuales, que está mapeado en bloques a la memoria física (RAM) o al archivo de paginación en disco.
  

-**Realiza una simulación en cualquier lenguaje de programación que emule el swapping de procesos en memoria virtual**: 

 ```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_SIZE 1000
#define MAX_PROCESSES 10 
#define SWAP_SPACE 2000  

typedef struct {
    int id;          
    int size;        
    int inMemory;  
} Process;

void displayMemory(Process processes[], int n, int memoryUsed) {
    printf("\nEstado de la memoria:\n");
    printf("ID\tTamaño\tEn Memoria\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d KB\t%s\n", processes[i].id, processes[i].size, processes[i].inMemory ? "Sí" : "No");
    }
    printf("Memoria usada: %d KB / %d KB\n", memoryUsed, MEMORY_SIZE);
    printf("\n");
}

void simulationSwapping(Process processes[], int n) {
    int memoryUsed = 0; 
    int swapUsed = 0;   

    for (int i = 0; i < n; i++) {
        printf("Cargando proceso %d (%d KB):\n", processes[i].id, processes[i].size);

        if (processes[i].size <= (MEMORY_SIZE - memoryUsed)) { 
            memoryUsed += processes[i].size;
            processes[i].inMemory = 1;
            printf("-> Proceso %d cargado en memoria física.\n", processes[i].id);
        } else { 
            printf("-> Memoria física insuficiente. Realizando swapping...\n");

            for (int j = 0; j < i; j++) {
                if (processes[j].inMemory) {
                    printf("-> Cargando proceso %d en espacio de intercambio (%d KB).\n", processes[j].id, processes[j].size);
                    memoryUsed -= processes[j].size;
                    swapUsed += processes[j].size;
                    processes[j].inMemory = 0;
                }

                if (processes[i].size <= (MEMORY_SIZE - memoryUsed)) {
                    memoryUsed += processes[i].size;
                    processes[i].inMemory = 1;
                    printf("-> Proceso %d cargado en memoria física.\n", processes[i].id);
                    break;
                }
            }

            if (!processes[i].inMemory) {
                printf("-> Espacio de intercambio insuficiente para cargar el proceso %d.\n", processes[i].id);
                break;
            }
        }

        displayMemory(processes, n, memoryUsed);

        if (swapUsed > SWAP_SPACE) {
            printf("-> Espacio de intercambio agotado. Simulación detenida.\n");
            break;
        }
    }

    printf("\nSimulación completa.\n");
    printf("Memoria física usada: %d KB / %d KB\n", memoryUsed, MEMORY_SIZE);
    printf("Espacio de intercambio usado: %d KB / %d KB\n", swapUsed, SWAP_SPACE);
}

int main() {
    Process processes[MAX_PROCESSES];
    int n;

    printf("Ingrese el número de procesos (máximo %d): ", MAX_PROCESSES);
    scanf("%d", &n);

    if (n > MAX_PROCESSES || n <= 0) {
        printf("Número de procesos inválido.\n");
        return 1;
    }

    printf("Ingrese el tamaño de cada proceso en KB:\n");
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Tamaño del proceso %d: ", i + 1);
        scanf("%d", &processes[i].size);
        processes[i].inMemory = 0; 
    }

    simulationSwapping(processes, n); 

    return 0;
}
```

# Administración de Entrada/Salida

## 4.1 Dispositivos y manejadores de dispositivos

### 1. Explique la diferencia entre dispositivos de bloque y dispositivos de carácter. Da un ejemplo de cada uno.

- **Dispositivos de bloque**: 

Se caracterizan por transferir la información en grupos de tamaño fijo, denominados bloques. Un ejemplo de este tipo de dispositivo es el **disco magnético*, que puede leer y escribir datos en bloques.

- **Dispositivos de tipo carácter**: 

Estos dispositivos pueden transmitir la información carácter a carácter. Un ejemplo es un **módem*, que envía y recibe datos de manera secuencial, caracter por caracter.

### 2. Diseña un programa que implemente un manejador de dispositivos sencillo para un dispositivo virtual de entrada.

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEVICE_NAME "VirtualInputDevice"
#define BUFFER_SIZE 256

typedef struct {
    int isOpen;
    char buffer[BUFFER_SIZE];
    int bufferPosition;
} Device;

Device virtualDevice;

void initializeDevice() {
    virtualDevice.isOpen = 0;
    memset(virtualDevice.buffer, 0, BUFFER_SIZE);
    virtualDevice.bufferPosition = 0;
    printf("Dispositivo %s inicializado.\n", DEVICE_NAME);
}

int openDevice() {
    if (virtualDevice.isOpen) {
        printf("Error: El dispositivo ya está abierto.\n");
        return -1;
    }
    virtualDevice.isOpen = 1;
    printf("Dispositivo %s abierto.\n", DEVICE_NAME);
    return 0;
}

int readDevice(char *output, int size) {
    if (!virtualDevice.isOpen) {
        printf("Error: El dispositivo no está abierto.\n");
        return -1;
    }
    if (virtualDevice.bufferPosition + size > BUFFER_SIZE) {
        size = BUFFER_SIZE - virtualDevice.bufferPosition;
    }
    strncpy(output, virtualDevice.buffer + virtualDevice.bufferPosition, size);
    virtualDevice.bufferPosition += size;
    printf("Leído %d bytes del dispositivo.\n", size);
    return size;
}

int writeDevice(const char *input) {
    if (!virtualDevice.isOpen) {
        printf("Error: El dispositivo no está abierto.\n");
        return -1;
    }
    int length = strlen(input);
    if (length > BUFFER_SIZE) {
        printf("Error: Entrada demasiado grande para el buffer.\n");
        return -1;
    }
    strncpy(virtualDevice.buffer, input, BUFFER_SIZE);
    virtualDevice.bufferPosition = 0;
    printf("Datos escritos en el dispositivo.\n");
    return length;
}

int closeDevice() {
    if (!virtualDevice.isOpen) {
        printf("Error: El dispositivo ya está cerrado.\n");
        return -1;
    }
    virtualDevice.isOpen = 0;
    virtualDevice.bufferPosition = 0;
    printf("Dispositivo %s cerrado.\n", DEVICE_NAME);
    return 0;
}

int main() {
    char readBuffer[BUFFER_SIZE];
    int choice;
    char input[BUFFER_SIZE];
    int bytesRead;

    initializeDevice();

    do {
        printf("\n--- Menú del Manejador de Dispositivo ---\n");
        printf("1. Abrir dispositivo\n");
        printf("2. Leer desde el dispositivo\n");
        printf("3. Escribir en el dispositivo\n");
        printf("4. Cerrar dispositivo\n");
        printf("5. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &choice);
        getchar(); // Consumir el salto de línea

        switch (choice) {
            case 1:
                openDevice();
                break;
            case 2:
                printf("¿Cuántos bytes desea leer?: ");
                scanf("%d", &bytesRead);
                getchar();
                bytesRead = readDevice(readBuffer, bytesRead);
                if (bytesRead > 0) {
                    readBuffer[bytesRead] = '\0';
                    printf("Datos leídos: %s\n", readBuffer);
                }
                break;
            case 3:
                printf("Ingrese los datos para escribir en el dispositivo: ");
                fgets(input, BUFFER_SIZE, stdin);
                input[strcspn(input, "\n")] = '\0';
                writeDevice(input);
                break;
            case 4:
                closeDevice();
                break;
            case 5:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción inválida. Intente de nuevo.\n");
        }
    } while (choice != 5);

    return 0;
}

```

 ### 4.2 Mecanismos y Funciones de los Manejadores de Dispositivos

#### 1. Investiga qué es la interrupción por E/S y cómo la administra el sistema operativo. Escribe un ejemplo en pseudocódigo para simular este proceso.

Una *interrupción por E/S* ocurre cuando un dispositivo de entrada/salida (como un disco duro, teclado, impresora, etc.) notifica al procesador que ha terminado una operación o requiere atención. Esto permite que el sistema operativo administre las operaciones de E/S de manera eficiente, sin que el procesador se bloquee esperando que estas operaciones finalicen.

##### Cómo administra el sistema operativo la interrupción por E/S:

1. **Inicio de la operación**:
 
 El sistema operativo inicia una operación de E/S, configurando el controlador del dispositivo y especificando los datos o comandos necesarios. La CPU puede continuar ejecutando otras tareas mientras el dispositivo realiza la operación de E/S de manera autónoma.

2. **Generación de la interrupción**: 

Cuando el dispositivo completa su tarea o encuentra un error, envía una señal de interrupción a la CPU. Esto activa el controlador de interrupciones (PIC/APIC), que detiene temporalmente la ejecución de la CPU y transfiere el control a una rutina especial.

3. **Atención de la interrupción**: 

El sistema operativo ejecuta una rutina de servicio de interrupción (ISR) para gestionar el evento del dispositivo. En el ISR, el sistema operativo procesa la interrupción, recopila datos, actualiza las estructuras del kernel (como colas de E/S) y decide qué hacer a continuación.

4. **Reanudación**: 

Después de atender la interrupción, el sistema operativo reanuda la ejecución de las tareas que estaban siendo interrumpidas.


#### Ejemplo en Pseudocódigo para simular una interrupción por E/S:

```c
Inicio

    Definir ProcesoA
    Definir ProcesoB
    Definir Estado "Ejecutando"
    
    Función ProcesoA()
        Mientras Verdadero
            Imprimir "Proceso A: Realizando operación"
            Esperar(2)
            Imprimir "Proceso A: Listo para E/S"
            Estado <- "Esperando E/S"
            Llamar a InterrupciónE_S()
        Fin Mientras
    Fin Función

    Función ProcesoB()
        Mientras Verdadero
            Si Estado = "Esperando E/S" Entonces
                Imprimir "Proceso B: Ejecutando tarea alternativa"
                Esperar(2)
                Estado <- "Ejecutando"
                Imprimir "Proceso B: Proceso A puede continuar."
            Fin Si
        Fin Mientras
    Fin Función

    Función InterrupciónE_S()
        Imprimir "Interrupción por E/S: Proceso A detenido, Proceso B en ejecución."
    Fin Función

    Iniciar ProcesoA()
    Iniciar ProcesoB()

Fin
``` 



## 2. Manejo de Interrupciones en un Sistema Básico de Simulación

Este programa simula el manejo de interrupciones mediante el uso de señales en C. El temporizador genera una señal SIGALRM cada segundo, y el programa maneja esta señal incrementando un contador.

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

volatile int interrupt_count = 0;

void timer_interrupt_handler(int signum) {
    (void)signum;  
    interrupt_count++;
    printf("Interrupción manejada. Contador: %d\n", interrupt_count);
}

int main() {
    signal(SIGALRM, timer_interrupt_handler);

    
    struct itimerval timer;
    timer.it_value.tv_sec = 1;          
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 1;    
    timer.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &timer, NULL);

    printf("Sistema de simulación iniciado. Esperando interrupciones...\n");
     }
   
    while (1) {
       
        printf("Programa principal ejecutándose...\n");
        sleep(2);  

    return 0;
}
```
### 4.3 Estructuras de Datos para Manejo de Dispositivos

## 1. . Investiga y explica qué es una cola de E/S.


Las colas de E/S son estructuras que gestionan las solicitudes de entrada y salida en sistemas operativos. Un controlador de dispositivo puede crear una o más colas de E/S, cada una de las cuales mantiene las solicitudes de operaciones para un dispositivo en particular. Estas solicitudes se procesan de acuerdo con el orden de llegada o pueden estar ordenadas según otros criterios como la prioridad.

Los objetos de cola de marco representan estas colas, actuando como contenedores que almacenan las solicitudes de E/S. Estas colas permiten gestionar de manera eficiente las operaciones de los dispositivos, y pueden tener funciones de devolución de llamada (callbacks) para gestionar eventos, como cuando un dispositivo está listo para procesar una solicitud.

## 2. Escribe un programa que simule las operaciones de un manejador de dispositivos utilizando una tabla de estructuras.

```c
#include <stdio.h>
#include <string.h>

typedef struct {
    char name[20];                       
    int is_open;                          
    void (*open)(void);                   
    void (*close)(void);                
    void (*read)(void);                   
    void (*write)(const char *data);       
} Device;

void open_device(void) {
    printf("Dispositivo abierto.\n");
}

void close_device(void) {
    printf("Dispositivo cerrado.\n");
}

void read_device(void) {
    printf("Leyendo datos del dispositivo...\n");
}

void write_device(const char *data) {
    printf("Escribiendo datos en el dispositivo: %s\n", data);
}

Device devices[] = {
    {"Teclado", 0, open_device, close_device, read_device, write_device},
    {"Pantalla", 0, open_device, close_device, read_device, write_device},
    {"Impresora", 0, open_device, close_device, read_device, write_device},
};

const int num_devices = sizeof(devices) / sizeof(Device);

Device *find_device(const char *name) {
    for (int i = 0; i < num_devices; i++) {
        if (strcmp(devices[i].name, name) == 0) {
            return &devices[i];
        }
    }
    return NULL; 
}

int main() {
    char command[20], device_name[20], data[100];
    printf("Manejador de dispositivos iniciado.\n");

    while (1) {
        printf("\nComandos disponibles:\n");
        printf("  open [nombre]\n");
        printf("  close [nombre]\n");
        printf("  read [nombre]\n");
        printf("  write [nombre] [data]\n");
        printf("  exit\n");
        printf("Ingrese un comando: ");

        scanf("%s", command);

        if (strcmp(command, "exit") == 0) {
            printf("Saliendo del manejador de dispositivos.\n");
            break;
        }

        scanf("%s", device_name);
        Device *device = find_device(device_name);
        if (!device) {
            printf("Dispositivo '%s' no encontrado.\n", device_name);
            continue;
        }

        if (strcmp(command, "open") == 0) {
            if (device->is_open) {
                printf("El dispositivo ya está abierto.\n");
            } else {
                device->open();
                device->is_open = 1;
            }
        } else if (strcmp(command, "close") == 0) {
            if (!device->is_open) {
                printf("El dispositivo ya está cerrado.\n");
            } else {
                device->close();
                device->is_open = 0;
            }
        } else if (strcmp(command, "read") == 0) {
            if (device->is_open) {
                device->read();
            } else {
                printf("Abra el dispositivo antes de leer.\n");
            }
        } else if (strcmp(command, "write") == 0) {
            if (device->is_open) {
                scanf(" %[^\n]s", data); 
                device->write(data);
            } else {
                printf("Abra el dispositivo antes de escribir.\n");
            }
        } else {
            printf("Comando desconocido.\n");
        }
    }

    return 0;
}
```

### 4.4 Operaciones de Entrada/Salida

## 1. Diseña un flujo que describa el proceso de lectura de un archivo desde un disco magnético. Acompáñalo con un programa básico que simule el proceso.


El proceso de lectura de un archivo desde un disco magnético involucra varios pasos que son gestionados por el sistema operativo, el sistema de archivos y el hardware del disco. Aquí te mostramos un flujo simplificado del proceso:

1. *Inicio*: El usuario solicita la lectura de un archivo.
2. *Solicitud de lectura del archivo*: El sistema operativo recibe la solicitud del usuario para abrir el archivo.
3. *El sistema de archivos identifica la ubicación del archivo*: El sistema de archivos consulta su tabla para encontrar la ubicación física del archivo en el disco.
4. *El controlador del disco envía un comando al hardware del disco*: El sistema de archivos envía una señal al controlador del disco indicando que debe empezar a buscar los datos.
5. *El cabezal del disco se mueve a la pista correspondiente*: El controlador mueve el cabezal de lectura/escritura del disco hacia la pista donde se encuentra el archivo.
6. *Los datos se leen del disco y se almacenan en un búfer*: Una vez en la pista correcta, los datos son leídos del disco y almacenados en un búfer en la memoria.
7. *El sistema de archivos procesa los datos leídos*: El sistema de archivos puede procesar los datos antes de pasárselos a la aplicación.

## Programa Básico para Simular el Proceso de Lectura

El siguiente programa en C simula el proceso de lectura de un archivo desde un "disco magnético". El programa pide al usuario el nombre del archivo y la pista donde se encuentra, y luego simula el proceso de búsqueda y lectura.

```c
#include <stdio.h>
#include <string.h>

void buscar_archivo(const char *nombre) {
    printf("Buscando archivo '%s' en el sistema de archivos...\n", nombre);
}

void mover_cabezal(int pista) {
    printf("Moviendo el cabezal a la pista %d...\n", pista);
}

void leer_datos(const char *archivo) {
    printf("Leyendo datos del archivo '%s' desde el disco...\n", archivo);
}

int main() {
    char archivo[50];
    int pista;

    printf("Ingrese el nombre del archivo a leer: ");
    scanf("%s", archivo);

    printf("Ingrese la pista del archivo (0-100): ");
    scanf("%d", &pista);

    buscar_archivo(archivo); 
    mover_cabezal(pista);     
    leer_datos(archivo);     

    printf("Proceso de lectura completado.\n");
    return 0;
}

```
### Implementa un programa en Python, C o java que realice operaciones de entrada/salida asíncronas usando archivos.

## Código del Programa python

```python
import asyncio
import aiofiles

async def leer_archivo(nombre_archivo):
    print(f"Leyendo archivo: {nombre_archivo}")
    async with aiofiles.open(nombre_archivo, mode='r') as archivo:
        contenido = await archivo.read()
    print(f"Contenido del archivo:\n{contenido}")

async def escribir_archivo(nombre_archivo, datos):
    print(f"Escribiendo en archivo: {nombre_archivo}")
    async with aiofiles.open(nombre_archivo, mode='w') as archivo:
        await archivo.write(datos)
    print("Escritura completada.")

async def main():
    await escribir_archivo("archivo.txt", "Este es un ejemplo de E/S asíncrona.\n")
    await leer_archivo("archivo.txt")

```

### INTEGRACION 

# Escribe un programa que implemente el algoritmo de planificación de discos "Elevator (SCAN)".



```c
#include <stdio.h>
#include <stdlib.h>

void elevator_scan(int requests[], int n, int start, int direction) {
    int i, seek = 0, pos = start;
    printf("Orden de accesos al disco: ");
    
    for (i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    if (direction == 1) {  
        for (i = 0; i < n; i++) {
            if (requests[i] >= start) {
                printf("%d ", requests[i]);
                seek += abs(pos - requests[i]);
                pos = requests[i];
            }
        }
    }

    for (i = n - 1; i >= 0; i--) {
        if (requests[i] < start) {
            printf("%d ", requests[i]);
            seek += abs(pos - requests[i]);
            pos = requests[i];
        }
    }

    printf("\nMovimiento total del cabezal: %d\n", seek);
}

int main() {
    int requests[] = {95, 180, 34, 119, 11, 123, 62, 64};
    int n = sizeof(requests) / sizeof(requests[0]); 
    int start = 50, direction = 1;  
    printf("Algoritmo SCAN (Elevator):\n");
    elevator_scan(requests, n, start, direction); 
    return 0;
}
```
### Diseña un sistema que maneje múltiples dispositivos simulados (disco duro, impresora, teclado) y muestra cómo se realiza la comunicación entre ellos.



# Dispositivos Simulados:
- *Teclado*: Captura texto de entrada.
- *Disco Duro*: Almacena el texto capturado.
- *Impresora*: Imprime el archivo guardado desde el disco.

## Código en Python

```python
import threading
import time

class Device:
    def _init_(self, name):
        self.name = name

    def operate(self, operation, data=None):
        """
        Simula una operación en el dispositivo.
        - operation: El tipo de operación a realizar (por ejemplo, 'Capturar entrada', 'Guardar archivo', etc.)
        - data: Los datos necesarios para la operación (opcional)
        """
        print(f"{self.name}: {operation} iniciado.")
        time.sleep(2)  
        if data:
            print(f"{self.name}: {operation} completado con datos: {data}.")
        else:
            print(f"{self.name}: {operation} completado.")

def communication_between_devices(devices):
    """
    Simula la comunicación entre los dispositivos:
    - El Teclado captura un texto.
    - El Disco Duro guarda el texto capturado.
    - La Impresora imprime el archivo guardado.
    """
    print("\n--- Simulación de comunicación entre dispositivos ---\n")

    print("Teclado: Iniciando captura de texto...")
    devices["Teclado"].operate("Capturar entrada", "Hola Mundo")

    print("Disco Duro: Guardando archivo...")
    devices["Disco Duro"].operate("Guardar archivo", "archivo.txt")

    print("Impresora: Imprimiendo archivo...")
    devices["Impresora"].operate("Imprimir documento", "archivo.txt")

def device_manager():
    """
    Administra las operaciones simultáneas de los dispositivos mediante hilos.
    También simula la comunicación entre los dispositivos.
    """
    devices = {
        "Disco Duro": Device("Disco Duro"),
        "Impresora": Device("Impresora"),
        "Teclado": Device("Teclado"),
    }

    threads = [
        threading.Thread(target=devices["Disco Duro"].operate, args=("Leer archivo",)),
        threading.Thread(target=devices["Impresora"].operate, args=("Imprimir documento", "Informe.pdf")),
        threading.Thread(target=devices["Teclado"].operate, args=("Capturar entrada", "Hola Mundo")),
    ]

    print("\n--- Simulación de operaciones independientes ---\n")
    for t in threads:
        t.start()
    for t in threads:
        t.join()

    communication_between_devices(devices)

if _name_ == "_main_":
    print("Sistema de múltiples dispositivos.")
    device_manager()
```

### Avanzados
### 1. Explica cómo los sistemas operativos modernos optimizan las operaciones de entrada/salida con el uso de memoria caché.

El uso de memoria caché en los sistemas operativos modernos es fundamental para optimizar las operaciones de *entrada/salida (E/S), haciendo que las aplicaciones funcionen más rápido y con mayor eficiencia. Al combinar técnicas como **lectura anticipada, **escritura diferida* y *algoritmos de gestión de caché*, los sistemas operativos logran un equilibrio entre el rendimiento y la integridad de los datos.

## Técnicas de Optimización

### 1. *Lectura anticipada (Read-Ahead)*
Los sistemas operativos emplean la lectura anticipada para predecir qué bloques de datos serán requeridos a continuación. Al cargar esos datos en la caché antes de que la aplicación los solicite, se reduce el tiempo de espera y se mejora el rendimiento general.

### 2. *Escritura diferida (Write-Back)*
La escritura diferida es una técnica donde los datos modificados en la caché no se escriben inmediatamente en el almacenamiento principal. En su lugar, los datos se escriben en bloques de forma diferida, lo que reduce las operaciones de E/S de escritura y mejora la eficiencia.

### 3. *Algoritmos de Gestión de Caché*
Los sistemas operativos utilizan algoritmos de reemplazo de caché como *LRU (Least Recently Used)* o *LFU (Least Frequently Used)* para decidir qué datos conservar en la caché y cuáles eliminar cuando se necesita espacio.

- *LRU (Least Recently Used)*: Este algoritmo elimina los datos menos recientemente utilizados, suponiendo que los datos que no se han utilizado en un tiempo no se necesitarán pronto.
  
- *LFU (Least Frequently Used)*: Elimina los datos que se han utilizado con menor frecuencia, lo que puede ser útil cuando los datos son accedidos de forma esporádica.

### 4. *Estrategias de Pre-carga de Datos*
Los sistemas operativos modernos pueden pre-cargar datos de archivos o bloques de disco en la memoria caché cuando se predice que serán necesarios, reduciendo la latencia asociada con las operaciones de E/S.

## Beneficios del Uso de Memoria Caché

### 1. *Reducción de Latencia*
Acceder a datos en caché es mucho más rápido que acceder a un disco duro o SSD, ya que la memoria caché es mucho más rápida que los medios de almacenamiento secundarios. Esto es crítico en aplicaciones que requieren tiempos de respuesta bajos, como bases de datos o servidores web, donde cada milisegundo cuenta.

### 2. *Menor Uso de Recursos de Hardware*
Agrupar y optimizar las operaciones de E/S reduce el desgaste físico en los discos duros (HDDs) o SSDs. Esto contribuye a extender la vida útil del hardware al reducir la cantidad de operaciones de lectura y escritura directamente realizadas en los dispositivos de almacenamiento.

### 3. *Mayor Rendimiento del Sistema*
Al minimizar los cuellos de botella causados por operaciones de E/S lentas, la CPU y otros recursos del sistema pueden operar a plena capacidad. Esto permite que los sistemas manejen tareas más complejas sin ser limitados por las velocidades de acceso al almacenamiento.

## Conclusión
La memoria caché juega un papel crucial en la optimización de las operaciones de entrada/salida en los sistemas operativos modernos. Al reducir la latencia y el uso de recursos de hardware, y al mejorar el rendimiento general, los sistemas operativos son capaces de gestionar eficientemente las operaciones de E/S, lo que se traduce en aplicaciones más rápidas y con mejor rendimiento.

### REFERENCIAS 

ASIR Claret. (sf). Fragmentación interna y externa . Recuperado de https ://asirclaret -com .webnode .es /news /fragmentacion -interna -y -externa/

LinkedIn . ( sf ) ¿ Cómo puedes elegir la mejor política de reemplazo de páginas ? Recuperado de https://www.linkedin.com/advice/0/how-can-you-choose-best-page-replacement-policy-hsare?lang=es & originalSubdomain = es

Gurú99. (sf). Diferencias entre paginación y segmentación . Recuperado de https ://www .guru99 .com /es /paging -vs -segmentation -difference .html

CHSOS. (2012). Imagen sobre paginación y segmentación . Recuperado de https ://chsos20122910022 .wordpress .com /wp -content /uploads /2012 /10 /imagen4 .jpg

Avellano FIS USAL. (sf). Sesión 4: Características de los dispositivos de bloque . Recuperado de http://avellano.fis.usal.es/​​​ssooii /sesion4.htm #::text =Dispositivos %20de %20bloque %3A %20se %20caracterizan ,Ejemplo %3A %20un %20modem.

Microsoft Learn . ( sf ) . Creación de colas de E / S . Recuperado de https://learn.microsoft.com/es-es/windows-hardware/drivers/wdf/creating-i-o-queues 

