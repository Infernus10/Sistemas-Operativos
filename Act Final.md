## Ejercicio 1: Concepto y noción de archivo real y virtual
![Diagrama de un sistema operativo](https://i0.wp.com/codigoespagueti.com/wp-content/uploads/2021/03/sistema-operativo.jpg)

### Definición de conceptos

#### **Archivo Real**
Un archivo real es una unidad de datos almacenada físicamente en un dispositivo de almacenamiento, como un disco duro, SSD, memoria USB, etc. Su contenido está representado por bits y se organiza en bloques que el sistema operativo gestiona directamente para el acceso, lectura y escritura.

- **Características principales:**
  - Existe físicamente en un medio de almacenamiento.
  - Requiere espacio real en el dispositivo.
  - Es gestionado por el sistema de archivos (FAT32, NTFS, ext4, etc.).

#### **Archivo Virtual**
Un archivo virtual no existe físicamente como una entidad única en un dispositivo de almacenamiento. Se genera dinámicamente a partir de fuentes como memoria, datos combinados, o incluso información generada en tiempo real. Su contenido suele residir en la memoria RAM o ser el resultado de operaciones en tiempo real realizadas por el sistema operativo o una aplicación.

- **Características principales:**
  - No ocupa espacio físico en un dispositivo como archivo único.
  - Suele ser temporal y reside en la memoria.
  - Su contenido puede cambiar dinámicamente.

---

### Ejemplos prácticos en sistemas operativos actuales

#### **Ejemplos de archivos reales:**
1. Un documento de texto (`documento.txt`) guardado en el escritorio de tu computadora.
2. Una foto en formato JPEG almacenada en el disco duro de tu teléfono.
3. Un archivo ejecutable (`app.exe`) en el sistema operativo Windows.

#### **Ejemplos de archivos virtuales:**
1. **Archivos en `/proc` (Linux):** En sistemas basados en Linux, la carpeta `/proc` contiene archivos virtuales que representan datos del sistema, como el estado de procesos o estadísticas de memoria. Por ejemplo, `/proc/cpuinfo` no existe físicamente, pero proporciona información sobre el procesador en tiempo real.
2. **Pipes en sistemas UNIX:** Los *named pipes* (`fifo`) son archivos virtuales que permiten comunicación entre procesos.
3. **Archivos temporales de aplicaciones:** Por ejemplo, en Windows, el archivo de paginación (pagefile) actúa como memoria virtual para expandir la RAM de forma dinámica.

---

### Caso práctico: Ventaja de un archivo virtual frente a uno real

**Monitoreo del sistema en tiempo real:**

Un archivo virtual es más útil cuando se requiere información dinámica y en tiempo real que cambia constantemente, como estadísticas del sistema o datos de diagnóstico. Por ejemplo:

- **Archivo virtual en `/proc/meminfo`:** Permite acceder a detalles sobre el uso de la memoria del sistema en Linux sin necesidad de guardar estos datos en un archivo físico. Esto es más eficiente que escribir continuamente estos datos en un archivo real, ya que evita el consumo de espacio de almacenamiento y mejora el rendimiento.

Por el contrario, un archivo real sería menos práctico en este escenario, ya que implicaría escrituras constantes en el disco, lo que podría reducir su vida útil y generar una carga innecesaria en el sistema.

--- 
# Ejercicio 2: Componentes de un sistema de archivos

## Descripción:
Investiga los componentes principales de un sistema de archivos y compáralos entre dos sistemas operativos, como Linux y Windows.

## Tareas:
- Identifica los componentes clave de un sistema de archivos (por ejemplo, metadatos, tablas de asignación, etc.).
- Crea un cuadro comparativo de cómo estos componentes funcionan en sistemas como EXT4 y NTFS.
- Describe las ventajas y desventajas de cada sistema basado en sus componentes.

## Componentes clave de un sistema de archivos:
1. *Metadatos*: Información sobre los archivos, como permisos, fechas de creación y modificación, y propietarios.
2. *Tablas de asignación*: Estructuras que llevan el seguimiento de dónde se almacenan los datos de los archivos en el disco.
3. *Directorios*: Estructuras que organizan los archivos en una jerarquía.
4. *Bloques de datos*: Unidades de almacenamiento que contienen los datos reales del archivo.
5. *Inodos (EXT4)* / *MFT (NTFS)*: Estructuras que almacenan información sobre archivos y directorios.
6. *Journaling*: Funcionalidad que ayuda a recuperar el sistema de archivos después de un fallo.

## Cuadro comparativo: EXT4 vs NTFS

| Componente            | EXT4                                      | NTFS                                      |
|-----------------------|-------------------------------------------|-------------------------------------------|
| *Metadatos*           | Inodos almacenan metadatos de archivos    | MFT (Master File Table) almacena metadatos|
| *Tablas de asignación*| Grupos de bloques gestionan la asignación de espacio | Bitmap y listas de clústeres libres
| *Directorios*         | Estructura de árbol de directorios        | Directorios organizados en B-tree         |
| *Bloques de datos*    | Tamaño de bloque configurable             | Tamaño de clúster configurable            |
| *Inodos/MFT*          | Inodos almacenan información detallada de archivos | MFT almacena información detallada de archivos |
| *Journaling*          | Utiliza journaling para integridad        | Utiliza journaling para integridad        |

## Ventajas y desventajas:

### EXT4
*Ventajas*:
- Mejor rendimiento en operaciones de lectura/escritura pequeñas.
- Sistema de journaling eficiente que mejora la recuperación de datos.
- Manejo flexible de tamaños de bloques.

**Desventajas**:
- No tiene características avanzadas como compresión y cifrado nativo.
- Soporte limitado en sistemas operativos no basados en Linux.

### NTFS
*Ventajas*:
- Soporte nativo para características avanzadas como compresión, cifrado, y cuotas de disco.
- Compatible con la mayoría de versiones de Windows, y soporte en macOS y Linux (con herramientas adicionales).
- Eficiente manejo de grandes volúmenes y archivos.

**Desventajas**:
- Puede ser más lento en operaciones de lectura/escritura pequeñas comparado con EXT4.
- Mayor complejidad en la estructura del sistema de archivos.


# Ejercicio 3: Organización lógica y física de archivos

## Descripción:
Crea un esquema que muestre la organización lógica y física de un sistema de archivos. Explica cómo se relacionan las estructuras lógicas con las físicas en el disco.

## Tareas:
- Diseña un árbol jerárquico que represente la organización lógica de directorios y subdirectorios.
- Explica cómo se traduce la dirección lógica a la dirección física en el disco.
- Proporciona un ejemplo práctico de cómo un archivo se almacena físicamente.

## Esquema de organización lógica

### Organización lógica (Árbol jerárquico)
plaintext
/
├── home
│   ├── user
│   │   ├── documents
│   │   │   ├── file1.txt
│   │   │   └── file2.txt
│   │   ├── pictures
│   │   │   ├── image1.jpg
│   │   │   └── image2.jpg
│   │   └── music
│   │       ├── song1.mp3
│   │       └── song2.mp3
└── var
    ├── log
    │   ├── syslog
    │   └── auth.log
    └── www
        └── index.html


## Traducción de dirección lógica a dirección física

### Explicación
1. *Inodos (en EXT4) / MFT (en NTFS)*: Cuando un archivo se crea, se le asigna un inodo (EXT4) o una entrada en la MFT (NTFS). Esta estructura contiene metadatos sobre el archivo y las direcciones de los bloques de datos en el disco.
2. *Bloques de datos*: Los datos del archivo se dividen en bloques y se almacenan en el disco. La ubicación física de estos bloques se registra en los inodos o en la MFT.
3. *Tablas de asignación*: Utilizan bitmaps o listas de bloques libres para rastrear qué bloques en el disco están disponibles o en uso.

### Ejemplo práctico
Supongamos que estamos guardando el archivo file1.txt en un sistema de archivos EXT4.

1. *Crear el archivo*: Se asigna un inodo al archivo file1.txt en el directorio /home/user/documents.
2. *Asignación de bloques*: El sistema de archivos busca bloques libres en el disco para almacenar los datos de file1.txt. Supongamos que file1.txt necesita 3 bloques y se le asignan los bloques 101, 102, y 103.
3. *Registrar metadatos*: El inodo de file1.txt se actualiza con los números de los bloques asignados (101, 102, 103), así como otros metadatos (tamaño del archivo, permisos, fechas, etc.).

### Ejemplo gráfico
plaintext
Inodo de file1.txt:
----------------------------------
| Inodo: 1234                    |
| Tamaño: 3 bloques (12 KB)      |
| Bloques: 101, 102, 103         |
| Permisos: rw-r--r--            |
| Fecha de creación: 2024-12-16  |
----------------------------------

Bloques de datos en el disco:
----------------------------------
| Bloque 100 | Datos de otro archivo  |
| Bloque 101 | Datos de file1.txt      |
| Bloque 102 | Datos de file1.txt      |
| Bloque 103 | Datos de file1.txt      |
| Bloque 104 | Datos de otro archivo  |
----------------------------------


En este esquema, la dirección lógica del archivo file1.txt en el directorio /home/user/documents se traduce en direcciones físicas en el disco (bloques 101, 102 y 103). La relación entre la estructura lógica (inodos) y la estructura física (bloques de datos) es gestionada por el sistema de archivos, que garantiza que los datos se pueden localizar y acceder correctamente.

# Ejercicio 4: Mecanismos de acceso a los archivos

## Descripción:
Simula diferentes mecanismos de acceso a archivos (secuencial, directo e indexado) en un entorno práctico.

## Tareas:
1. Define los diferentes mecanismos de acceso.
2. Escribe un pseudocódigo que muestre cómo acceder a:
   - Un archivo secuencialmente.
   - Un archivo directamente mediante su posición.
   - Un archivo utilizando un índice.
3. Compara las ventajas de cada mecanismo dependiendo del caso de uso.

## Definición de los diferentes mecanismos de acceso

1. *Acceso secuencial*:
   - Los datos se leen o escriben en un orden específico, comenzando desde el inicio del archivo y avanzando secuencialmente hasta el final.
   - Usado comúnmente en archivos de registro y transmisión de datos.

2. *Acceso directo*:
   - Permite acceder a cualquier parte del archivo directamente, sin tener que leer los datos anteriores.
   - Ideal para bases de datos y sistemas que requieren acceso rápido a registros específicos.

3. *Acceso indexado*:
   - Utiliza una estructura de índice que mantiene referencias a las ubicaciones de los datos en el archivo.
   - Combina la velocidad del acceso directo con la eficiencia del acceso secuencial.

## Pseudocódigo

### Acceso secuencialmente
plaintext
Abrir archivo para lectura
Mientras no sea el final del archivo
    Leer un registro
    Procesar el registro
Fin mientras
Cerrar archivo


### Acceso directo mediante su posición
plaintext
Abrir archivo para lectura
Definir posición (por ejemplo, registro 5)
Calcular la posición en bytes (posición * tamaño del registro)
Mover el puntero del archivo a la posición calculada
Leer el registro
Procesar el registro
Cerrar archivo


### Acceso utilizando un índice
plaintext
Abrir archivo de datos para lectura
Abrir archivo de índice para lectura
Leer el índice en memoria
Buscar la posición del registro deseado en el índice
Calcular la posición en bytes (posición * tamaño del registro)
Mover el puntero del archivo de datos a la posición calculada
Leer el registro
Procesar el registro
Cerrar archivo de datos
Cerrar archivo de índice


## Comparación de las ventajas de cada mecanismo dependiendo del caso de uso

### Acceso secuencial
*Ventajas*:
- Simplicidad en la implementación y uso.
- Eficiente para procesar grandes volúmenes de datos en orden.
- Útil para operaciones de lectura/escritura continuas, como registros de eventos.

*Desventajas*:
- Poco eficiente para buscar datos específicos.
- Lento si se necesita acceder a registros ubicados hacia el final del archivo.

### Acceso directo
*Ventajas*:
- Acceso rápido y eficiente a cualquier registro en el archivo.
- Ideal para aplicaciones que requieren acceso aleatorio a datos, como bases de datos.

*Desventajas*:
- Más complejo de implementar que el acceso secuencial.
- Requiere conocimiento previo de la posición de los registros.

### Acceso indexado
*Ventajas*:
- Combina la velocidad del acceso directo con la eficiencia del acceso secuencial.
- Muy eficiente para búsquedas y acceso rápido a registros específicos.
- Ideal para grandes conjuntos de datos donde se necesitan búsquedas rápidas.

*Desventajas*:
- Requiere mantenimiento adicional del archivo de índice.
- Puede consumir más espacio de almacenamiento debido a los índices.

Cada mecanismo de acceso tiene sus ventajas y desventajas, y la elección del mecanismo adecuado depende del caso de uso específico y de los requisitos de rendimiento y eficiencia.



# Ejercicio 5: Modelo jerárquico y mecanismos de recuperación en caso de falla

## Descripción:
Diseña una estructura jerárquica para un sistema de archivos y simula un escenario de falla en el sistema. Describe cómo recuperar los datos utilizando mecanismos de recuperación.

## Tareas:

- Diseña un modelo jerárquico para un sistema de archivos con al menos tres niveles de directorios.
- Simula una falla en un directorio específico y describe los pasos necesarios para recuperarlo.
- Explica qué herramientas o técnicas de respaldo (backup) utilizarías para evitar pérdida de datos.

## Modelo jerárquico para un sistema de archivos

### Estructura jerárquica
plaintext
/
├── home
│   ├── user
│   │   ├── documents
│   │   │   ├── report1.docx
│   │   │   └── report2.docx
│   │   ├── pictures
│   │   │   ├── vacation.jpg
│   │   │   └── family.jpg
│   │   └── music
│   │       ├── song1.mp3
│   │       └── song2.mp3
└── var
    ├── log
    │   ├── syslog
    │   └── auth.log
    └── www
        └── index.html


## Simulación de una falla y recuperación

### Falla simulada
Supongamos que ocurre una falla en el directorio /home/user/documents y se pierden los archivos report1.docx y report2.docx.

### Pasos para la recuperación

1. *Identificar la falla*:
   - Determinar que el directorio /home/user/documents ha sufrido una falla y los archivos se han perdido.

2. *Recuperación desde un respaldo*:
   - *Herramienta de respaldo*: Usar una herramienta como rsync, tar, o Timeshift (en Linux) para restaurar los archivos perdidos.
   - *Ubicar el respaldo*: Acceder a la ubicación donde se almacenan los respaldos periódicos.

3. *Restaurar los datos*:
   - *Comando de restauración*:
     bash
     rsync -av /backup/home/user/documents /home/user/
     
     - Este comando copia los archivos respaldados del directorio /backup/home/user/documents al directorio /home/user/.

4. *Verificación*:
   - Verificar que los archivos report1.docx y report2.docx han sido restaurados correctamente en el directorio /home/user/documents.

## Herramientas y técnicas de respaldo

### Herramientas de respaldo
1. *rsync*:
   - Herramienta de sincronización de archivos y directorios que permite realizar copias de seguridad incrementales.
   - Ventajas: Eficiente, soporta copias remotas, y permite la automatización mediante scripts.

2. *tar*:
   - Utilidad de archivado que se utiliza para agrupar varios archivos en un solo archivo comprimido.
   - Ventajas: Fácil de usar y ampliamente disponible en sistemas Unix y Linux.

3. *Timeshift*:
   - Herramienta de respaldo y restauración para sistemas Linux, similar a System Restore en Windows.
   - Ventajas: Fácil de configurar y utilizar, permite restaurar el sistema a un estado anterior con un solo clic.

### Técnicas de respaldo
1. *Respaldo completo*:
   - Copia todos los datos del sistema en cada respaldo.
   - Ventajas: Recuperación fácil y completa.
   - Desventajas: Requiere mucho espacio de almacenamiento y tiempo.

2. *Respaldo incremental*:
   - Solo copia los datos que han cambiado desde el último respaldo.
   - Ventajas: Ahorra espacio y tiempo.
   - Desventajas: La recuperación puede ser más compleja, ya que requiere restaurar la última copia completa y todas las copias incrementales subsecuentes.

3. *Respaldo diferencial*:
   - Copia todos los datos que han cambiado desde el último respaldo completo.
   - Ventajas: Ahorra tiempo en comparación con el respaldo completo y es más sencillo de recuperar que el respaldo incremental.
   - Desventajas: Requiere más espacio que el respaldo incremental.

### Prevención de pérdida de datos

- *Programar respaldos periódicos*: Configurar respaldos diarios, semanales o mensuales según la criticidad de los datos.
- *Almacenar respaldos en múltiples ubicaciones*: Utilizar almacenamiento externo o servicios de nube para guardar copias de respaldo.
- *Verificar regularmente los respaldos*: Asegurarse de que los respaldos se están realizando correctamente y que los datos pueden ser restaurados sin problemas.

Utilizando estas herramientas y técnicas, se puede minimizar el riesgo de pérdida de datos y asegurar una recuperación rápida y eficiente en caso de fallas.



# Protección y Seguridad

## Ejercicio 1: Concepto y objetivos de protección y seguridad

### Descripción:
Investiga los conceptos de protección y seguridad en sistemas operativos. Analiza los objetivos principales que deben cumplir estos mecanismos.

### Tareas:
- Define los conceptos de protección y seguridad en el contexto de sistemas operativos.
- Identifica los objetivos principales de un sistema de protección y seguridad, como confidencialidad, integridad y disponibilidad.
- Da un ejemplo práctico de cómo se aplican estos objetivos en un sistema operativo.

### Conceptos de protección y seguridad en sistemas operativos

*Protección*:
La protección en sistemas operativos se refiere al mecanismo que controla el acceso de los procesos y usuarios a los recursos del sistema, como memoria, archivos, dispositivos y otros recursos. Su principal objetivo es prevenir el acceso no autorizado y asegurar que cada recurso se utilice de manera segura y adecuada.

*Seguridad*:
La seguridad en sistemas operativos es un conjunto de políticas, procedimientos y mecanismos diseñados para proteger el sistema de amenazas internas y externas. Esto incluye proteger los datos, preservar la privacidad del usuario, y asegurar la correcta operación del sistema frente a ataques, fallas y mal uso.

### Objetivos principales de un sistema de protección y seguridad

1. *Confidencialidad*:
   - Asegurar que la información y los recursos solo sean accesibles por aquellos usuarios y procesos que tienen permiso para ello.
   - Ejemplo: Cifrado de archivos y comunicaciones para que solo los usuarios autorizados puedan acceder a la información.

2. *Integridad*:
   - Garantizar que la información y los recursos del sistema no sean alterados o modificados de manera no autorizada.
   - Ejemplo: Mecanismos de control de versiones y checksums para verificar que los archivos no han sido manipulados.

3. *Disponibilidad*:
   - Asegurar que los recursos y la información estén disponibles para los usuarios y procesos autorizados cuando se necesiten.
   - Ejemplo: Implementación de sistemas de respaldo y recuperación, y medidas contra ataques de denegación de servicio (DoS).

### Ejemplo práctico de aplicación de los objetivos en un sistema operativo

*Sistema Operativo: Windows*

1. *Confidencialidad*:
   - *BitLocker*: Una herramienta de cifrado que protege los datos almacenados en el disco duro mediante cifrado completo del disco. Solo los usuarios con la clave correcta pueden acceder a los datos.
   - *Control de Acceso Basado en Roles (RBAC)*: Permite asignar permisos específicos a grupos de usuarios, asegurando que solo aquellos con los roles adecuados puedan acceder a ciertos recursos.

2. *Integridad*:
   - *Windows File Integrity Check (SFC)*: Una herramienta que verifica y repara los archivos del sistema operativo para asegurar que no hayan sido alterados o corrompidos.
   - *Control de Cuentas de Usuario (UAC)*: Previene que los programas realicen cambios no autorizados en el sistema, solicitando confirmación del usuario antes de permitir acciones que requieran privilegios administrativos.

3. *Disponibilidad*:
   - *Respaldo y Restauración de Windows*: Funcionalidades que permiten realizar copias de seguridad automáticas de los datos y del sistema, y restaurar el sistema en caso de fallas o pérdida de datos.
   - *Windows Defender y Firewall*: Protegen el sistema contra malware y accesos no autorizados, asegurando que los recursos del sistema estén disponibles y protegidos contra amenazas.

Estos mecanismos y herramientas integrados en el sistema operativo Windows ayudan a cumplir los objetivos de confidencialidad, integridad y disponibilidad, proporcionando un entorno seguro y protegido para los usuarios y procesos.
# Ejercicio 2: Clasificación aplicada a la seguridad

## Descripción:
Clasifica los mecanismos de seguridad en un sistema operativo y explica cómo cada tipo contribuye a la protección del sistema.

## Tareas:
- Investiga las clasificaciones comunes de la seguridad, como física, lógica y de red.
- Explica el papel de cada clasificación en la protección de un sistema operativo.
- Proporciona ejemplos prácticos de herramientas o técnicas utilizadas en cada clasificación.

### Clasificaciones comunes de la seguridad

1. *Seguridad Física*
2. *Seguridad Lógica*
3. *Seguridad de Red*

### Explicación del papel de cada clasificación en la protección de un sistema operativo

1. *Seguridad Física*:
   - *Papel*: La seguridad física se encarga de proteger el hardware del sistema operativo de daños físicos, robos o accesos no autorizados. Sin una seguridad física adecuada, las demás medidas de seguridad pueden ser fácilmente eludidas.
   - *Ejemplos*:
     - *Controles de acceso físico*: Uso de cerraduras, tarjetas de acceso y vigilancia para restringir el acceso físico a los servidores y dispositivos críticos.
     - *Protección contra desastres*: Implementación de sistemas de protección contra incendios, control de temperatura y humedad, y planes de recuperación ante desastres.

2. *Seguridad Lógica*:
   - *Papel*: La seguridad lógica se centra en proteger el sistema operativo y los datos contra accesos no autorizados, errores y ataques de software. Esto incluye la protección de la integridad y confidencialidad de los datos y la gestión de los permisos de acceso.
   - *Ejemplos*:
     - *Control de acceso*: Utilización de sistemas de autenticación y autorización, como contraseñas, autenticación multifactor y permisos de usuario para asegurar que solo los usuarios autorizados accedan al sistema.
     - *Cifrado*: Uso de tecnologías de cifrado para proteger los datos almacenados y transmitidos, asegurando que solo las partes autorizadas puedan leer la información.
     - *Sistemas de detección y prevención de intrusiones (IDS/IPS)*: Monitoreo continuo del sistema para detectar y prevenir actividades sospechosas o maliciosas.

3. *Seguridad de Red*:
   - *Papel*: La seguridad de red protege la infraestructura de red que conecta el sistema operativo a otros sistemas y dispositivos. Su objetivo es evitar accesos no autorizados, ataques y garantizar la integridad y disponibilidad de los datos en tránsito.
   - *Ejemplos*:
     - *Firewalls*: Barreras de protección que controlan el tráfico de red entrante y saliente, permitiendo solo las comunicaciones autorizadas.
     - *VPN (Redes Privadas Virtuales)*: Tecnologías que permiten conexiones seguras y cifradas a través de redes públicas, protegiendo los datos en tránsito.
     - *Segmentación de red*: División de la red en segmentos más pequeños y controlados para limitar la propagación de ataques y mejorar la seguridad general.

### Ejemplos prácticos de herramientas o técnicas utilizadas en cada clasificación

1. *Seguridad Física*:
   - *Cámaras de vigilancia*: Monitoreo visual de las instalaciones para detectar y responder a actividades sospechosas.
   - *Sensores de movimiento*: Detectan la presencia de personas no autorizadas en áreas restringidas.
   - *Control de acceso biométrico*: Uso de huellas digitales, reconocimiento facial o escaneo de retina para autenticar y permitir el acceso físico.

2. *Seguridad Lógica*:
   - *Microsoft BitLocker*: Herramienta de cifrado de disco completo para proteger los datos almacenados en discos duros.
   - *SELinux (Security-Enhanced Linux)*: Módulo de seguridad para Linux que proporciona control de acceso obligatorio para mejorar la seguridad del sistema.
   - *Antivirus y antimalware*: Software como Windows Defender o Norton que protege el sistema operativo contra virus, malware y otras amenazas de software.

3. *Seguridad de Red*:
   - *Cisco ASA (Adaptive Security Appliance)*: Dispositivo de firewall que proporciona seguridad avanzada de red.
   - *OpenVPN*: Software de código abierto que permite crear conexiones VPN seguras.
   - *Wireshark*: Herramienta de análisis de tráfico de red que permite capturar y examinar datos en tránsito para detectar y analizar problemas de seguridad.

Estos mecanismos de seguridad, cuando se implementan y gestionan correctamente, proporcionan una protección integral para los sistemas operativos contra una amplia gama de amenazas físicas, lógicas y de red.


# Ejercicio 3: Funciones del sistema de protección

## Descripción:
Analiza las funciones que cumple un sistema de protección en un entorno multiusuario.

## Tareas:
- Describe cómo un sistema de protección controla el acceso a los recursos.
- Explica las funciones principales como autenticación, autorización y auditoría.
- Diseña un caso práctico donde se muestren las funciones de un sistema de protección en acción.

### Control del acceso a los recursos
Un sistema de protección en un entorno multiusuario controla el acceso a los recursos mediante la implementación de políticas de seguridad y mecanismos que aseguran que solo los usuarios autorizados puedan acceder a los recursos específicos. Esto se logra a través de varias funciones principales, como la autenticación, autorización y auditoría.

### Funciones principales

1. *Autenticación*:
   - *Descripción*: La autenticación es el proceso de verificar la identidad de un usuario. Esto se realiza generalmente mediante credenciales como nombres de usuario y contraseñas, tarjetas inteligentes, autenticación biométrica o autenticación multifactor.
   - *Ejemplo*: Cuando un usuario intenta iniciar sesión en el sistema, se le solicita que ingrese su nombre de usuario y contraseña. El sistema verifica estas credenciales contra una base de datos de usuarios autorizados.

2. *Autorización*:
   - *Descripción*: La autorización determina los permisos y privilegios que un usuario autenticado tiene dentro del sistema. Esto implica definir qué recursos puede acceder el usuario y qué acciones puede realizar.
   - *Ejemplo*: Una vez que el usuario se autentica, el sistema verifica sus permisos. Por ejemplo, un empleado de nivel básico puede tener acceso solo a ciertos archivos y aplicaciones, mientras que un administrador tiene acceso completo al sistema.

3. *Auditoría*:
   - *Descripción*: La auditoría es el proceso de registrar y monitorear las actividades de los usuarios y el acceso a los recursos del sistema. Esto ayuda a detectar y responder a comportamientos sospechosos o no autorizados.
   - *Ejemplo*: El sistema registra todos los intentos de inicio de sesión, accesos a archivos, y modificaciones de configuración. Estos registros pueden revisarse para asegurar que no haya habido accesos no autorizados o actividades maliciosas.

### Caso práctico: Sistema de protección en acción

*Escenario*: Empresa XYZ con un sistema multiusuario para gestionar información sensible.

1. *Autenticación*:
   - *Proceso*: 
     - Un empleado, Ana, intenta acceder al sistema de la empresa.
     - Se le solicita que ingrese su nombre de usuario y contraseña.
     - El sistema utiliza autenticación multifactor (MFA), enviando un código de verificación a su teléfono móvil.
     - Ana ingresa el código y el sistema verifica su identidad.
   
2. *Autorización*:
   - *Proceso*:
     - Una vez autenticada, el sistema consulta la base de datos de permisos.
     - Ana es una analista financiera y tiene acceso solo a los recursos financieros.
     - Intenta acceder a los documentos de recursos humanos, pero el sistema le niega el acceso debido a sus permisos limitados.
   
3. *Auditoría*:
   - *Proceso*:
     - Todas las actividades de Ana son registradas por el sistema de auditoría.
     - Esto incluye su inicio de sesión, accesos a archivos financieros, y el intento de acceder a documentos de recursos humanos.
     - Los registros de auditoría son revisados periódicamente por el equipo de seguridad de la empresa para asegurar que no haya habido accesos no autorizados.
     - Un informe mensual de auditoría es generado y revisado por el departamento de TI.



# Ejercicio 4: Implantación de matrices de acceso

## Descripción:
Crea e implementa una matriz de acceso para un sistema que contiene usuarios y recursos con diferentes niveles de permisos.

## Tareas:
- Diseña una matriz de acceso para un sistema con al menos 3 usuarios y 4 recursos.
- Explica cómo esta matriz se utiliza para controlar el acceso en un sistema operativo.
- Simula un escenario donde un usuario intenta acceder a un recurso no permitido y cómo la matriz lo bloquea.

### Diseño de la matriz de acceso

#### Usuarios:
1. *Alice*
2. *Bob*
3. *BRUNO*

#### Recursos:
1. *Archivo A*
2. *Archivo B*
3. *Directorio C*
4. *Aplicación D*

#### Niveles de permisos:
- *R*: Lectura (Read)
- *W*: Escritura (Write)
- *X*: Ejecución (Execute)
- *-*: Sin permiso

#### Matriz de acceso:

|              | Archivo A | Archivo B | Directorio C | Aplicación D |
|--------------|-----------|-----------|--------------|--------------|
| *Alice*    | R/W       | R         | R/X          | -            |
| *Bob*      | R         | R/W       | -            | R/X          |
| *BRUNO*  | -         | R         | R            | -            |

### Explicación de la matriz de acceso

La matriz de acceso se utiliza para controlar el acceso en un sistema operativo de la siguiente manera:

1. *Control de Acceso*: La matriz de acceso define los permisos que cada usuario tiene sobre cada recurso. El sistema operativo consulta esta matriz antes de permitir cualquier operación de acceso a un recurso.
2. *Verificación de Permisos*: Cuando un usuario intenta acceder a un recurso, el sistema verifica los permisos en la matriz de acceso. Si el permiso necesario no está otorgado en la matriz, el acceso es denegado.
3. *Gestión de Permisos*: Los administradores del sistema pueden actualizar la matriz de acceso para cambiar los permisos según sea necesario, asegurando que los usuarios solo tengan acceso a los recursos que necesitan.

### Simulación de un escenario

*Escenario*: BRUNO intenta modificar (escribir en) el Archivo A.

1. *Solicitud de Acceso*: BRUNO intenta escribir en el Archivo A.
2. *Verificación en la Matriz de Acceso*: El sistema operativo consulta la matriz de acceso para verificar los permisos de BRUNO sobre el Archivo A.

   Matriz de acceso para BRUNO:
   - *Archivo A*: -
   - *Archivo B*: R
   - *Directorio C*: R
   - *Aplicación D*: -

3. *Determinación del Acceso*: La matriz de acceso muestra que BRUNO no tiene permisos de escritura (W) en el Archivo A (indicado por "-").
4. *Bloqueo de Acceso*: Dado que BRUNO no tiene los permisos necesarios, el sistema operativo bloquea la solicitud de escritura.

*Resultado*:
- *Acceso Denegado*: BRUNO recibe un mensaje de error indicando que no tiene permisos suficientes para modificar el Archivo A.

# Ejercicio 5: Protección basada en el lenguaje

## Descripción:
Investiga cómo los lenguajes de programación pueden implementar mecanismos de protección.

## Tareas:
- Explica el concepto de protección basada en el lenguaje.
- Proporciona un ejemplo de cómo un lenguaje como Java o Rust asegura la memoria y evita accesos no autorizados.
- Compara este enfoque con otros mecanismos de protección en sistemas operativos.

### Concepto de protección basada en el lenguaje

La protección basada en el lenguaje se refiere a los mecanismos de seguridad implementados directamente en el diseño y características de un lenguaje de programación para prevenir errores comunes y asegurar que el código se ejecute de manera segura. Estos lenguajes incluyen características que protegen contra errores de programación que podrían llevar a vulnerabilidades de seguridad, como desbordamientos de búfer, accesos no autorizados a la memoria y condiciones de carrera.

### Ejemplo de protección en Java y Rust

#### Java:
- *Gestión Automática de Memoria*: Java utiliza un recolector de basura (Garbage Collector) para gestionar la memoria automáticamente. Esto evita problemas como los desbordamientos de búfer y la corrupción de memoria, ya que los desarrolladores no tienen que manejar manualmente la asignación y liberación de memoria.
- *Control de Acceso*: Java implementa un sistema de control de acceso basado en modificadores como private, protected, public, y default. Estos modificadores restringen el acceso a los métodos y variables, asegurando que solo las partes autorizadas del código puedan interactuar con ellos.

*Ejemplo en Java*:
java
public class SafeClass {
    private int sensitiveData;

    public int getSensitiveData() {
        return sensitiveData;
    }

    public void setSensitiveData(int data) {
        if (data >= 0) { // simple validation
            sensitiveData = data;
        }
    }
}


#### Rust:
- *Seguridad de Memoria*: Rust asegura la memoria a través de su sistema de propiedad (ownership), referencias (references) y préstamos (borrowing). Este sistema previene accesos no autorizados y garantiza que no haya condiciones de carrera, desreferenciación de punteros nulos, ni acceso a memoria después de liberarla.
- *Verificación en Tiempo de Compilación*: Muchas de las comprobaciones de seguridad en Rust se realizan en tiempo de compilación, eliminando una clase entera de errores en tiempo de ejecución.

*Ejemplo en Rust*:
rust
fn main() {
    let mut data = vec![1, 2, 3];
    
    {
        let borrow = &data; // préstamo inmutable
        println!("{:?}", borrow);
    } // el préstamo inmutable finaliza aquí

    {
        let borrow_mut = &mut data; // préstamo mutable
        borrow_mut.push(4);
        println!("{:?}", borrow_mut);
    } // el préstamo mutable finaliza aquí
}


### Comparación con otros mecanismos de protección en sistemas operativos

1. *Protección a Nivel de Hardware*:
   - *Descripción*: Los sistemas operativos utilizan protección basada en hardware, como la gestión de la memoria y la separación de espacio de usuario y espacio de kernel, para evitar que los programas de usuario interfieran con el sistema operativo o con otros programas.
   - *Comparación*: Mientras que la protección a nivel de hardware se centra en asegurar el entorno en el que se ejecutan los programas, la protección basada en el lenguaje se enfoca en prevenir errores dentro del propio código del programa.

2. *Protección a Nivel de Sistema Operativo*:
   - *Descripción*: Los sistemas operativos implementan mecanismos como permisos de archivos, autenticación de usuarios y auditoría para controlar el acceso a recursos y mantener la integridad del sistema.
   - *Comparación*: La protección basada en el lenguaje es complementaria a estos mecanismos, proporcionando una capa adicional de seguridad al prevenir que los programas se comporten de manera insegura o accedan a recursos de manera inapropiada desde dentro del código mismo.

# Ejercicio 6: Validación y amenazas al sistema

## Descripción:
Analiza las principales amenazas a un sistema operativo y los mecanismos de validación utilizados para prevenirlas.

## Tareas:
- Investiga y describe al menos tres tipos de amenazas comunes (por ejemplo, malware, ataques de fuerza bruta, inyección de código).
- Explica los mecanismos de validación como autenticación multifactor y control de integridad.
- Diseña un esquema de validación para un sistema operativo con múltiples usuarios.

### Amenazas Comunes a un Sistema Operativo

#### 1. Malware
- *Descripción*: El malware (software malicioso) incluye virus, gusanos, troyanos y ransomware. Estas amenazas pueden dañar o robar datos, interrumpir operaciones del sistema y comprometer la seguridad del sistema operativo.
- *Prevención*: Utilización de software antivirus y antimalware, mantener el sistema y aplicaciones actualizados, y educación del usuario sobre prácticas seguras.

#### 2. Ataques de Fuerza Bruta
- *Descripción*: Los ataques de fuerza bruta intentan adivinar contraseñas probando todas las combinaciones posibles hasta encontrar la correcta. Este tipo de ataque puede comprometer cuentas de usuario y acceder a información sensible.
- *Prevención*: Implementación de políticas de contraseñas fuertes, bloqueo de cuentas después de múltiples intentos fallidos, y uso de autenticación multifactor.

#### 3. Inyección de Código
- *Descripción*: La inyección de código, como la inyección SQL, permite a un atacante insertar código malicioso en una aplicación para manipular bases de datos o ejecutar comandos no autorizados.
- *Prevención*: Validación y saneamiento de entradas de usuario, uso de consultas parametrizadas y marcos de seguridad que prevengan inyecciones.

### Mecanismos de Validación

#### Autenticación Multifactor (MFA)
- *Descripción*: MFA requiere que los usuarios proporcionen dos o más formas de verificación antes de acceder a un sistema. Esto puede incluir algo que el usuario sabe (contraseña), algo que el usuario tiene (token o dispositivo móvil), y algo que el usuario es (huella dactilar o reconocimiento facial).
- *Ventajas*: Aumenta significativamente la seguridad al requerir múltiples factores de autenticación, lo que dificulta el acceso no autorizado incluso si una de las credenciales es comprometida.

#### Control de Integridad
- *Descripción*: Los controles de integridad verifican que los archivos y datos no hayan sido alterados. Esto se puede lograr mediante el uso de sumas de verificación, firmas digitales y herramientas de monitoreo de integridad de archivos.
- *Ventajas*: Permite detectar cambios no autorizados en el sistema, lo que ayuda a identificar posibles ataques o fallos en la seguridad.

### Esquema de Validación para un Sistema Operativo con Múltiples Usuarios

#### Esquema Propuesto:

1. *Autenticación de Usuario*:
    - *MFA*: Requerir a los usuarios ingresar su contraseña y proporcionar un código de autenticación enviado a su dispositivo móvil o generado por una aplicación de autenticación.
    - *Biométrica*: Implementar autenticación biométrica (huella dactilar o reconocimiento facial) para una capa adicional de seguridad.

2. *Control de Acceso*:
    - *Roles y Permisos*: Asignar roles y permisos específicos a cada usuario basado en sus responsabilidades y necesidades. Utilizar listas de control de acceso (ACL) para gestionar los permisos de archivos y recursos.
    - *Políticas de Contraseñas*: Implementar políticas que requieran contraseñas complejas, cambio regular de contraseñas y prohibición de contraseñas reutilizadas.

3. *Monitoreo y Auditoría*:
    - *Registros de Auditoría*: Mantener registros detallados de todas las actividades del sistema, incluidos intentos de acceso, cambios en la configuración y operaciones críticas. Analizar regularmente estos registros para detectar actividades sospechosas.
    - *Control de Integridad*: Utilizar herramientas de monitoreo de integridad para verificar regularmente la integridad de archivos críticos del sistema y aplicaciones.

4. *Educación y Concienciación del Usuario*:
    - *Capacitación*: Proporcionar capacitación regular a los usuarios sobre seguridad informática, mejores prácticas para la creación de contraseñas, y cómo reconocer intentos de phishing y otras amenazas.

### Ejemplo de Escenario

*Escenario*: Un usuario intenta acceder a un archivo protegido.

1. *Solicitud de Acceso*: El usuario introduce su nombre de usuario y contraseña.
2. *MFA*: El sistema solicita un código de autenticación enviado al dispositivo móvil del usuario.
3. *Verificación Biométrica*: El sistema solicita una verificación de huella dactilar.
4. *Control de Permisos*: El sistema verifica los permisos del usuario para acceder al archivo solicitado.
5. *Acceso Permitido*: Si todas las validaciones son exitosas, el acceso es concedido. Si alguna falla, el acceso es denegado y se registra el intento en los registros de auditoría.

# Ejercicio 7: Cifrado

## Descripción:
Explora cómo los mecanismos de cifrado protegen la información en un sistema operativo.

## Tareas:
- Define los conceptos de cifrado simétrico y asimétrico.
- Proporciona un ejemplo práctico de cada tipo de cifrado aplicado en sistemas operativos.
- Simula el proceso de cifrado y descifrado de un archivo con una clave dada.

### Cifrado Simétrico

#### Definición:
El *cifrado simétrico* es un tipo de cifrado en el que se utiliza la misma clave tanto para cifrar como para descifrar la información. Esto significa que tanto el emisor como el receptor deben compartir y mantener en secreto la clave utilizada para realizar el cifrado.

- *Ejemplos de algoritmos*: AES (Advanced Encryption Standard), DES (Data Encryption Standard), 3DES (Triple DES).
- *Ventajas*: El cifrado y descifrado son rápidos, lo que lo hace adecuado para grandes volúmenes de datos.
- *Desventajas*: La distribución segura de la clave es un reto, ya que si alguien obtiene la clave, puede descifrar la información.

#### Ejemplo práctico en sistemas operativos:
En sistemas operativos como Linux o Windows, el *cifrado de disco completo* como *BitLocker* (Windows) o *LUKS* (Linux) usa cifrado simétrico para proteger los datos del disco. La clave utilizada para cifrar y descifrar el disco completo es almacenada de manera segura en el sistema.

### Cifrado Asimétrico

#### Definición:
El *cifrado asimétrico* utiliza dos claves diferentes: una *clave pública* para cifrar la información y una *clave privada* para descifrarla. La clave pública se puede compartir libremente, mientras que la clave privada debe mantenerse en secreto.

- *Ejemplos de algoritmos*: RSA, ECC (Elliptic Curve Cryptography).
- *Ventajas*: No es necesario compartir la clave privada, lo que hace más seguro su uso en la comunicación.
- *Desventajas*: El proceso de cifrado y descifrado es más lento en comparación con el cifrado simétrico.

#### Ejemplo práctico en sistemas operativos:
En sistemas operativos como *Linux, se utilizan **certificados SSL/TLS* para establecer conexiones seguras (por ejemplo, en servidores web). El servidor utiliza una clave pública para recibir datos cifrados, y el cliente utiliza la clave privada para descifrarlos.

### Simulación del proceso de cifrado y descifrado

#### Cifrado Simétrico: Ejemplo en Python con AES
*Cifrado y descifrado de un archivo usando una clave compartida con AES*

python
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes

# Generar una clave aleatoria de 256 bits
clave = get_random_bytes(32)

# Cifrado
def cifrar_archivo(input_file, output_file, clave):
    cipher = AES.new(clave, AES.MODE_CBC)
    
    with open(input_file, 'rb') as f:
        data = f.read()
    
    # Rellenar y cifrar
    encrypted_data = cipher.encrypt(pad(data, AES.block_size))
    
    # Guardar el archivo cifrado
    with open(output_file, 'wb') as f:
        f.write(cipher.iv)  # Escribir el vector de inicialización
        f.write(encrypted_data)

# Descifrado
def descifrar_archivo(input_file, output_file, clave):
    with open(input_file, 'rb') as f:
        iv = f.read(16)  # Leer el vector de inicialización
        encrypted_data = f.read()
    
    cipher = AES.new(clave, AES.MODE_CBC, iv)
    
    # Descifrar y descomprimir
    decrypted_data = unpad(cipher.decrypt(encrypted_data), AES.block_size)
    
    with open(output_file, 'wb') as f:
        f.write(decrypted_data)

# Cifrar y descifrar un archivo de ejemplo
cifrar_archivo('ejemplo.txt', 'ejemplo_cifrado.bin', clave)
descifrar_archivo('ejemplo_cifrado.bin', 'ejemplo_descifrado.txt', clave)


#### Cifrado Asimétrico: Ejemplo en Python con RSA

python
from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP
from Crypto.Random import get_random_bytes

# Generar un par de claves RSA
key = RSA.generate(2048)
private_key = key.export_key()
public_key = key.publickey().export_key()

# Cifrado
def cifrar_con_rsa(mensaje, public_key):
    public_key = RSA.import_key(public_key)
    cipher = PKCS1_OAEP.new(public_key)
    encrypted_message = cipher.encrypt(mensaje.encode())
    return encrypted_message

# Descifrado
def descifrar_con_rsa(encrypted_message, private_key):
    private_key = RSA.import_key(private_key)
    cipher = PKCS1_OAEP.new(private_key)
    decrypted_message = cipher.decrypt(encrypted_message)
    return decrypted_message.decode()

# Mensaje original
mensaje_original = "Este es un mensaje secreto"

# Cifrar y descifrar con RSA
encrypted_message = cifrar_con_rsa(mensaje_original, public_key)
decrypted_message = descifrar_con_rsa(encrypted_message, private_key)

print("Mensaje original:", mensaje_original)
print("Mensaje descifrado:", decrypted_message)