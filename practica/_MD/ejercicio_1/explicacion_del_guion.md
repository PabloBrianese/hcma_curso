```
units real
```
Este comando fija el estilo de las unidades usadas en la simulación.
Determina las unidades de todas las cantidades especificadas en el guionde entrada y archivos de datos, así como las cantidades imprimidas en la pantalla, archivos de registro, y archivos de depósito.
Tipicamente, este comando es usado al principio del guion de entrada.

Para el estilo `real`, estas son las unidades:

  - masa = gramos / mol
  - distancia = Angstroms
  - tiempo = femtosegundos
  - energía = kilocaloría / mol
  - velocidad = Angstroms / femtosegundo
  - fuerza = kilocaloría / (mol * Angstrom)
  - torque = kilocaloría / mol
  - temperatura = Kelvin
  - presión = atmósferas
  - viscosidad dinámica = Poise
  - carga = multiplo de la carga de un electron (1.0 es un protón)
  - dipolo = carga * Angstroms
  - campo eléctrico = voltio / Angstrom
  - densidad = gramo / cm^dim


```
atom_style charge
```
Define que estilo de átomos se usarán en la simulación.
Esto determina qué atributos están asociados con los átomos.
Este comando debe ser usado antes de la configuración de una simulación mediante un comando `read_data`, `read_restart`, `create_box`.

La elección de estilo afecta qué cantidades son almacenadas por cada átomo, qué cantidades son comunicadas entre procesadores para habilitar el cómputo de las fuerzas, y qué cantidades están listadas en el archivo de datos leído por el comando `read_data`.

```
neighbor 0.3 bin
```
Este comando fija parámetros que afectan la construcción de las listas de pares de vecinos.
Todos los pares de átomos que se encuentren a una distancia de corte de vecinos (igual a la distacia de corte de la fuerza más la distancia de piel) son guardados en la lista.
Típicamente, mientras mayor sea la distancia de piel, menos frecuentemente es necesario construir las listas de vecinos, pero más pares deben ser verificados en cada paso temporal por posibles interacciones mediante fuerzas.

Los valores por defecto dependen de la elección de unidades para la simulación, para el estilo `real` son `skin = 2.0` y `style = bin`.

El valor `style` elige que algoritmo es usado para construir la lista.
El estilo `bin` crea la lista usando cajas, una operación que escala linealmente con N/P, el número de átomos por procesador donde N = número total de átomos y P = número de procesadores.

Cuando una ejecución termina, conteos del número de vecinos almacenados en la lista de pares y el número de veces que se construyeron listas de vecinos son impresos a la pantalla y al archivo de registro.

```
comm_modify cutoff 1.0
```
Este comando fija los parámetros que afectan la comunicación, de información sobre los átomos, entre procesadores que ocurre en cada paso mientras coordenadas y otras propiedades son intercambiadas entre procesadores vecinos y almacenadas como propiedades de átomos fantasma (`ghost atoms`).

cutoff value = Rcut (distance units) = communicate atoms from this far away

La palabra clave cutoff permite extender la distancia de corte de fantasmas para el modo de comunicación `single`, que es la distancia a los bordes del subdominio de un procesador a partir de la cual átomos fantasma de otros procesadores son adquiridos.
Por defecto el corte de fantasmas = corte de vecinos = corte de fuerzas entre pares + piel de vecinos.
Si el `Rcut` especificado es mayor que el corte de vecinos, entonces átomos adicionales serán adquiridos.
Si el corte provisto es menor, este valor será ignorado, el corte de fantasmas adquirirá su valor por defecto y se imprimirá una advertencia.
Especificar un valor de corte de `0.0` reseteará cualquier valor previo a valores por defecto.
By default the ghost cutoff = neighbor cutoff = pairwise force cutoff + neighbor skin.

```
atom_modify	sort 0 1.0
atom_modify map array
```

sort values = Nfreq binsize
  Nfreq = sort atoms spatially every this many time steps
  binsize = bin size for spatial sorting (distance units)

Este comando modifica ciertos atributos definidos y almacenados en LAMMPS, además de aquellos que son especificados por el comando `atom_style`.
Las palabras clave `id` y `map` debe especificarse antes de definir una caja de simulación; las demás no tienen restricciones.

La palabra clave `map` determina como átomos con IDs específicas son hallados cuando se lo requiere.
Un ejemplo son los métodos que procesan enlaces químicos (ángulos, etc) entre un par de átomos, estos átomos enlazados (que forman un ángulo, etc) poseen IDs globales específicas y los métodos de procesamiento necesitan encontrar los índices locales (que corresponden a un procesador particular) de estas IDs globales.
LAMMPS ejecuta esta operación eficientemente creando un "mapa", concretamente un arreglo o una tabla hash, como se describe aquí debajo.

Cuando la palabra clave `map` no está especificada en tu guión de entrada, LAMMPS solo crea un mapa para `atom_styles` y sistemas moleculares que tengan enlaces químicos permanentes (ángulos, etc).
Ningún mapa se crea para sistemas atómicos, dado que normalmente no es necesario.
Sin embargo algunos comandos de LAMMPS requieren de un mapa, incluso para sistemas atómicos, y generaran un error si no existe uno.
La palabra clave `map` permite forzar la creación de un mapa en estos casos.
El valor `yes` creará un mapa como arreglo o como tabla hash, del modo que se explica en el siguiente párrafo.
Los valores `array` y `hash` creat un mapa de tipo arreglo o tabla hash respectivamente.

Para un mapa de tipo arreglo, cada procesador almacena una tabla de consulta de longitud N, donde N es la mayor ID de un átomo en el sistema.
Este método es sencillo y rápido para muchas simulaciones, pero requiere mucha memoria en las simulaciones grandes.
Para un mapa de tipo hash, una tabla hash es creada en cada procesador, que encuentra la ID de un átomo en tiempo constante (independiente del número global de IDs de átomos).
Puede ser ligeramente más lento que un mapa de tipo arreglo, pero su costo de memoria es proporcional al número de átomos poseídos por un procesador, i.e. N/P donde N es el número total de átomos en el sistema y P es el número de procesadores.

La palabra clave `sort` enciende el ordenamiento o reordenamiento espacial de los átomos dentro del subdominio de cada procesador, lo cual ocurre cada `Nfreq` pasos.
Si `Nfreq` es 0, entonces el ordenamiento es apagado.
Este ordenamieto puede mejorar el uso del cache y en consecuencia acelerar una simulación de LAMMPS, como se discute en una publicación de (Meloni).
Su eficacia depende del tamaño del problema (átomos / procesadores), que tan rápidamente el sistema se desordene, y otros factores.
Como regla general, el ordenamiento es típicamente más efectivo en la aceleración de simulaciones de materiales fluídos en contraposición a los materiales sólidos.
En las pruebas que se han realizado, la aceleración puede ir de cero a 3-4x. 

El reordenamiento es ejecutado cada `Nfreq` pasos durante una ejecución dinámica o iteraciones durante una minimización.
Con precisión, el reordenamiento ocurre durante el primer cálculo de vecinos que ocurre luego del paso señalado.
Este reordenamiento es ejecutado localmente por cada procesador, usando cajas del tamaño `binsize` especificado.
Si `binsize` es 0.0, entonces se utiliza un tamaño de caja igual a la mitad de la distancia de corte de vecinos (corte de fuerzas más distancia de piel), el cual es un valor razonable.
Después de que los átomos hayan sido agrupados en cajas, son reordenados de modo tal que los átomos en la misma caja sean adyacentes en la lista de átomos (uno-dimensional) del procesador.

El objetivo de este procedimiento es ubicar a los átomos, proximos entre sí espacialmente, cerca los unos de los otros en la lista uno-dimensional de átomos del procesador.
Esto puede mejorar el uso del cache cuando interacciones entre pares y listas de vecinos son calculadas.
Notar que si las cajas son muy pequeñas, habrá pocos átomos por caja.
Lo análogo ocurre si las cajas son muy grandes, habrá demasiados átomos por caja.
En ambos casos, el objetivo de la localidad del cache será perjudicado.

Por defecto, `id` es `yes`.

Por defecto, los sistemas atómicos (sin topología de enlaces) no usan un mapa.
Para sistemas moleculares (con topología de enlaces), un mapa es usado.
El estilo por defecto del mapa es `array` toda ID de los átomos es menor a 1 millón, en caso contrario el valor por defecto es `hash`.
Por defecto, el ordenamiento está activado con una frecuencia de 1000 y un tamaño de caja de 0.0, lo cual implica que el corte de vecinos será usado para fijar el tamaño de las cajas.
Si el corte de vecinos no es definido, el ordenamiento será desactivado.

```
pair_style none
```
Fijar la(s) fórmula(s) que LAMMPS utiliza para computar las interacciones entre pares.

`none` - apaga las interacciones entre pares

Usar un estilo de pares `none` significa que las fuerzas y energías de los pares no son computadas.

Con esta elección, el corte de fuerzas es 0.0, lo cual quiere decir que solo aquellos átomos que se encuentren a distancias menores a la distancia de piel de vecinos son comunicados entre procesadores.
Se debe asegurar que la distancia de piel sea lo suficientemente grande como para adquirir los átomos que son necesarios para calcular enlaces, ángulos, etc.

Un estilo de pares `none` también evitará que se construyan listas de pares de vecinos.
Sin embargo, si el estilo de vecinos es `bin`, las estructuras de datos para llevar adelante el encajonamiento son asignadas.
Si la distancia de piel de vecinos es pequeña, entonces estas estructuras de datos pueden consumir una gran cantidad de memoria.
Por eso se debería fijar el estilo de vecinos como `nsq` o aumentar la distancia de piel de vecinos.

Ver el estilo de pares `zero` para hallar una forma de gatillar la construcción de listas de vecinos, pero sin computar las interacciones entre pares.

```
dimension 3
```
Fijar la dimensionalidad de la simulación.
Por defecto LAMMPS ejecuta simulaciones en tres dimensiones.
Para correr una simulación en dos dimensiones, este comando debe ser usado previamente a la configuración de una caja de simulación mediante los comandos `create_box` o `read_data`.
Los archivos de reinicio también almacenan esta configuración.

```
boundary	s s s
```
Fijar el estilo de los bordes para la caja de simulación global en cada dimensión.
Una única letra asigna el mismo estilo a ambas caras, la superior y la inferior, de la caja.
El tamaño inicial de la caja de simulación es configurado por los comandos `read_data`, `read_restart`, o `create_box`.

El estilo `p` significa que la caja es periódica, de modo que las partículas pueden interactuar a travez del borde, y pueden atravezar una cara de la caja y reingresar por la opuesta.

Los estilos `f`, `s`, y `m` significan que la caja no es periódica, de modo que las partículas no interactúan a través del borde y no se mueven de un lado a otro de la caja.

Para el estilo `f`, la posición de la cara esta fija.
Si un átomo se mueve por fuera de la cara, será eliminado en el siguiente paso en el cual se recalculen los vecinos.
Esto típicamente generará un error a menos que se configure la opción `thermo_modify lost` para permitir la pérdida de átomos.

Para el estilo `s`, la posición de la cara varía para abarcar a todos los átomos en esa dimensión (retractilado), sin importar qué tan lejos estos se muevan.
Notar que, cuando es grande la diferencia entre las dimensiones actuales de la caja y las dimensiones retractiladas de la caja, es posible que se pierdan átomos al inicio de una simulación si esta se ejecuta en paralelo.
Esto se debe al gran cambio en las dimensiones (globales) de la caja, que provocan cambios significativos en el tamaño de los subdominios.
Si estos cambios van más allá del corte de comunicación (`comm_modify cutoff`), se perderán átomos.
La mejor forma de atender este problema es fijar las dimensiones iniciales de la caja de modo tal que aproximen las dimensiones retractiladas con mayor precisión, usando bordes de estilo `m` (ver aquí debajo).
<!-- REVISAR ESTA PARTE -->

Para el estilo `m`, el retractilado ocurre, pero está acotado por el valor especificado en los archivos de datos o de reinicio o fijada por el comando `create_box`.
Por ejemplo, si la cara superior de la dimensión z tiene un valor de 50.0 en el archivo de datos, la cara siempre se posicionará en valores de 50.0 o superiores, incluso si la extensión de los átomos en el eje z se vuelve mucho menor a 50.0.
Esto puede ser útil si se inicia una simulación con una caja vacía o si se desea dejar espacio en un lado de la caja, por ejemplo para que los átomos puedan evaporarse desde una superficie. 
<!-- no entiendo este último comentario -->

Este comando no puede ser utilizado luego de que la caja de simulación sea definida por un comando `read_data` o `create_box` o `read_restart`.

```
#########################################
# tipos con que se asocian las partículas
variable TipoA1 equal 1
```
Este comando asigna una o más cadenas al nombre de una variable para ser evaluada más adelante en el guión o durante una simulación.
Una variable puede ser definina y luego referenciada en un guion para convertirse en parte de un nuevo comando.
La referencia puede ser `$x` si el nombre `x` es un único caracter, o como `${LoopVar}` si el nombre `LoopVar` consta de uno o más caracteres.
Estas pueden ser útiles en varios contextos.

Para el estilo `string`, una única cadena es asignada a la variable.
Si esta cadena debe contener espacios en blanco pueden utilizarse comillas, por ejemplo ingresando `'con espacios'`.
Este comando ejecuta substitución de variables incluso si ingresamos una cadena entre comillas, de modo que la cadena `'una ${variable}'` se procesa como `'una cadena'` si `variable` es previamente declarada igual a `cadena`.

Las variables de estilo `equal` almacenan una fórmula que cuando es evaluada produce un (único) valor numérico.

```
####################################################
# SECCCION DE PARAMETROS DE CONTROL DE LA SIMULACION
####################################################

# caja inicial del sistema
variable xlo equal 0.0
variable xhi equal 300.0
variable ylo equal 0.0
variable yhi equal 300.0
variable zlo equal 0.0
variable zhi equal 300.0


variable NumPasosIntegracion equal 1e6

variable DTime equal 0.00001

# posición inicial
variable x_ini equal 0.0
variable y_ini equal 0.0
variable z_ini equal 100.0

# velocidad inicial
variable vx_ini equal 10.0
variable vy_ini equal 0.0
variable vz_ini equal 0.0


# IntensityMagn=0 lo usamos para "apagar" el campo magnético
# medida en unidades de (Kcal/mole)*fms/(qp*Angstrom^2)
# recordar que 1 Kcal/mole = ~ 4184 J/N_A 
# donde N_A es el número de avogadro
variable IntensityMagn equal 10.0

# IntensityElectr=0 lo usamos para "apagar" el campo electrico 
# medida en unidades de volts/Angstrom
variable IntensityElectr equal 0.1
```
```
# Directorio en el que se van a guardar los archivos de salida
variable DirectorioOut string ./DatosElectronEnCampoElectromagnetico/
# creamos el directorio DirectorioOut (si es que no existe...)
shell 'mkdir --parents' ${DirectorioOut}
```
El comando `shell` de LAMMPS permite ejecutar un comando en la shell del sistema operativo.
Por ejemplo, permite mover archivos de aquí a allá en preparación para la siguiente sección del guion.
O puede ejecutar un programa que pre-procese datos para ingresar en LAMMPS.
O puede ejecutar un programa que post-procese datos de salida de LAMMPS.
Unos pocos comandos sencillos de manipulación de archivos están soportados directamente, usando una sintaxis similar a la de Unix (pueden hallarse en la documentación oficial).
Cualquier otro comando es pasado, tal como se recibe, a una llamada de la función `system` de la librería estandar de C, que a su vez invoca el comando en la shell.

```
variable Prefix string Z_

variable NombreDeBase string ${Prefix}ElectronEnCampo_PasInt_IntensityMagn${IntensityMagn}_IntensityElectr${IntensityElectr}NumPasosIntegracion${NumPasosIntegracion}Dt${DTime}
#variable NombreDeBase string ${Prefix}prueba


variable NumFigurasParaMovie equal 200
variable NumFigurasPNG equal 1
variable NumFigurasXYZ equal 1
variable NumDatos equal 1000
variable NumEstado equal 1


## No modificar esto que sigue
variable NumTotalPasos equal ${NumPasosIntegracion}
variable PasosGuardarFigurasParaMovie equal ${NumPasosIntegracion}/${NumFigurasParaMovie}
variable PasosGuardarFigurasPNG equal ${NumPasosIntegracion}/${NumFigurasPNG}
variable PasosGuardarFigurasXYZ equal ${NumPasosIntegracion}/${NumFigurasXYZ}
variable PasosDatos equal ${NumPasosIntegracion}/${NumDatos}
variable PasosEstado equal ${NumPasosIntegracion}/${NumEstado}
##
```

```
timestep ${DTime}
```
Fijar el tamaño del paso temporal para subsiguientes simulaciones de dinámica molecular.
Las unidades que se utilizan para interpretar el número ingresado son controladas por el comando `units`.

El valor por defecto del tamaño del paso también depende de la elección de unidades, para el estilo `real` este valor es de 1.0 femtosegundos.

```
region CAJA_SISTEMA block ${xlo} ${xhi} ${ylo} ${yhi} ${zlo} ${zhi}
```
Este comando define una región geométrica del espacio.
Varios otros comandos utilizan regiones.
Por ejemplo, la región puede ser poblada de átomos por medio del comando `create_atoms`.
O puede ser usada para definir la caja de simulación por medio de comando `create_box`.
O puede señalar a los átomos que contiene e identificarlos como un grupo por medio del comando `group`, o eliminarlos por medio del comando `delete_atoms`.
O puede usarse la superficie de la región como borde por medio del comando `fix wall/region`.

Los comandos que usan regiones típicamente evalúan si la posición de un átomo está contenida en la región o no.
Con este propósito, las coordenadas que se ubican exactamente en el borde de la región se consideran parte del interior de la región.
Esto quiere decir, por ejemplo, para una región esférica, que un átomo en la superficie de la esfera sería parte de la región si la esfera fuera definida con la palabra clave `side in`, pero no formaría parte de la región si fuera definida usando la palabra clave `side out`.

    block args = xlo xhi ylo yhi zlo zhi
      xlo,xhi,ylo,yhi,zlo,zhi = bounds of block in all dimensions (distance units)

```
create_box 1 CAJA_SISTEMA 
```
Este comando crea una caja de simulación basada en la región especificada.
El argumento `N = 1` determina el número de tipos de átomos que se usarán en esta simulación.
Y el argumento `region-ID = CAJA_SISTEMA` especifica la ID de la región que será utilizada como dominio de simulación.
Por lo tanto, el comando `region` debe usarse antes de este.
También particiona la caja de simulación en una grilla regular tridimensional de ladrillos rectangulares, uno por procesador, basado en el número de procesadores usados y en la configuración del comando `processors`.
Esta partición puede ser modificada con posterioridad por los comandos `balance` o `fix`.

Para usar este comando, un estilo de átomos debe haber sido previamente definido con el comando `atom_style` y también una región con el comando `region`.

```
################################################################################
# SECCCION DE INSERCION DE ATOMOS EN EL SISTEMA
################################################################################

create_atoms 1 single ${x_ini} ${y_ini} ${z_ini}
```
Este comando crea átomos (o moléculas) en un retículo, o un único átomo (o molécula), o una colección aleatoria de átomos (o moléculas), como alternativa a leer sus coordenadas explícitamente a través de los comandos `read_data` o `read_restart`.

Una caja de simulación, típicamente creada por medio del comando `create_box`, debe existir antes de usar este comando.
También debe existir un retículo, definido usando el comando `lattice`, a menos que se especifique el estilo `single` con la palabra clave `units box` o el estilo `random`.
De aquí en más, nos referiremos a un átomo o una molécula creada como "partícula".

Si las partículas creadas son átomos individuales, se les asigna el tipo de átomo especificado, sin embargo esto puede ser alterado por la palabra clave `basis` como se discute abajo.
Si se están creando moléculas, el tipo de cada átomo en la molécula creada es especificado en el archivo leído por el comando `molecule`, y cuyos valores son sumados al tipo de átomo especificado.
Por ejemplo, si `type = 2`, y el archivo especifica tipos de átomos 1,2,3, entonces cada molécula creada tendrá tipos de átomos 3,4,5.

Para el estilo `single`, una única partícula es añadida al sistema en las coordenadas especificadas.
Esto puede ser útil para propositos de depuración o para crear un sistema minúsculo en pocisiones especificadas.

Un `atom_style` debe ser previamente definido para usar este comando.

```
# masa del electrón en gramos/mol
# notar que 1 gramos/mol = 1 gr /N_A, donde N_A es el número de avogadro
variable MasaElectron equal 0.00054854
mass 1 ${MasaElectron}
```
Fijar la masa para todos los átomos de uno o más tipos de átomos.
Estos valores también pueden ser fijados en el archivo de datos `read_data` usando la palabra clave `Masses`.
Las unidades de masa utilizadas estan determinadas por el comando `units`.

Notar que el comando `mass` solo puede usarse si el estilo del átomo requiere que la masa de de cada tipo de átomo sea determinada.

Este comando debe usarse luego de la definición de la caja de simulación sea definida por un comando `read_data`, `read_restart`, o `create_box`.

Todas las masas deben ser definidas antes de ejecutar la simulación.
También deben ser definidas antes de usar un comando `velocity` o `fix shake`.

La masa asignada a cualquier tipo de átomo debe ser mayor a `0.0`.

```
# seteamos la carga del electrón, consistentemente con el sistema de 
# unidades de lammps "real"
variable CargaElectron equal -1
set type 1 charge ${CargaElectron}
```
Fijar una o más propiedades de uno o más átomos.
Dado que las propiedades de los átomos son inicialmente asignadas por los comandos `read_data`, `read_restart` o `create_atoms`, este comando cambia esas asignaciones.
Esto puede ser útil para sobreescribir los valores por defecto asignados por el comando `create_atoms` (por ejemplo `charge = 0.0`).
Puede ser útil para alterar las interacciones entre pares y las fuerzas moleculares, dado que los coeficientes de los campos de fuerza son definidos en terminos de tipos.
También puede ser usado para cambiar el rotulado de los átomos según el tipo de átomo o ID molecular cuando se imprimen a archivos de depósito.
También puede ser útil para la depuración de un guion; por ejemplo para posicionar un átomo en una ubicación precisa para calcular las subsiguientes fuerzas o energía.

Notar que los argumentos `style` e `ID` determinan cuales átomos veran sus propiedades modificadas.
Las demás palabras claves especifican cuales propiedades son modificadas y cuales son sus nuevos valores.

Las palabras clave `x`, `y`, `z`, y `charge` fijan las coordenadas o la carga de todos los átomos seleccionados.
Para la carga, el estilo de átomo siendo usado debe soportar el uso de carga atómica.
Las palabras clave `vx`, `vy` y `vz` fijan las velocidades de todos los átomos seleccionados.

```
# seteamos la velocidad del electrón
velocity all set ${vx_ini} ${vy_ini} ${vz_ini}
```
Fijar o cambiar las velocidades de un grupo de átomos en uno o varios estilos.
Para cada estilo, existen argumentos obligatorios y palabras clave opcionales.
No todas las opciones son usadas por cada estilo.
Cada opción tiene un valor por defecto.

El estilo `set` fija las velocidades de todos los átomos en el grupo iguales a los valores especificados.
Si alguna componente es especificada `NULL`, entonces no se configura su valor.
Cualquiera de los componentes de la velocidad `vx`, `vy`, `vz` puede ser especificada como una variable de estilo `equal` o `atom`.
Si el valor es una variable, debe ser especificada como `v_name`, donde `name` es el nombre de la variable.
En este caso las variables serán evaluadas, y su valor usado para determinar la componente de la velocidad.
Notar que de usar una variable, la velocidad que calcula debe estar en unidades `box` y no en unidades `lattice`.

```
# seteamos el campo eléctrico externo
fix fix_campo_electrico all efield 0.0 ${IntensityElectr} 0.0
```

Configurar un arreglo (`fix`) que será aplicado a un grupo de átomos.
En LAMMPS, un "arreglo" ("fix") es cualquier operación que se aplica al sistema durante la simulación o la minimización.
Ejemplos de esto incluyen actualizar la posición y velocidades de átomos debido a la integración temporal, controlar la temperatura del sistema, aplicar fuerzas restrictivas a los átomos, hacer cumplir las condiciones de borde, calcular diagnósticos, etc.
Hay cientos de arreglos definidos en LAMMPS y pueden agragarse otros nuevos.

Los arreglos ejecutan sus operaciones en diferentes etapas del paso de la simulación (o minimización).
Si dos o más arreglos operan en la misma etapa del paso, son invocados en el orden en el que fueron especificados en el guion de entrada.

fix efield command

fix ID group-ID efield ex ey ez

Añade una fuerza F = qE a cada átomo cargado en el grupo debida la aplicación de un campo eléctrico externo aplicado sobre el sistema.
Si el sistema contiene dipolos puntuales, el campo eléctrico también añade un torque sobre los dipolos.

Para cargas, cualquiera de las tres cantidades que definen los componentes del campo eléctrico E, es decir `ex`, `ey`, `ez`, puede ser especificada como una variable de estilo `equal` o `atom`.
Si el valor es una variable, debe ser especificada como `v_name`, donde `name` es el nombre de la variable.
En este caso, la variable será evaluada a cada paso, y su valor utilizado para determinar la componente del campo eléctrico.

```
################################################################################
# comienzo seccion de configuración el campo magnetico externo
################################################################################
# calculamos las componentes de la fuerza de Lorentz q(v x B), asumimos
# B=(0,1,0)
variable FLx equal -${CargaElectron}*${IntensityMagn}*vz[1]
variable FLy equal 0
variable FLz equal ${CargaElectron}*${IntensityMagn}*vx[1]
fix fix_campo_magnetico all addforce v_FLx v_FLy v_FLz

# fin seccion de configuración el campo magnetico externo
```
Añadir `fx`, `fy`, `fz` a las correspondientes componentes de la fuerza para cada átomo en el grupo.
Este comando puede ser usado para dar un impulso adicional a los átomos en una simulación, tal como para la simulación de un flujo de Poiseuille en un canal.

Cualquiera de las tres cantidades que define los componentes de la fuerza pueden ser especificadas como variables de estilo `equal` o `atom`.
Si el valor es una variable, debe ser especificada como `v_name`, donde `name` es el nombre de la variable.

En este caso, la variable será evaluada a cada paso, y su valor utilizado para determinar la componente de la fuerza.

```
# termostato para la integración a energía constante
fix termostato all nve
```
nve: constant number, volume and energy

fix ID group-ID nve

ID, group-ID are documented in fix command

nve = style name of this fix command

Ejecutar una integración con NVE constante para actualizar, a cada paso, la posición y velocidad de los átomos en el grupo.
La sigla NVE quiere decir: Número constante de partículas, Volúmen constante, y Energía constante.
Esto resulta en que la trayectoria del sistema es consistente con la colectividad microcanónica.

```
# Poner la variable "GenerarMovie" en on/off
# segun se quiera o no generar la movie
variable GenerarMovie string off

variable N equal ${PasosGuardarFigurasParaMovie}
variable file string ${DirectorioOut}${NombreDeBase}.mpg
variable color string type
variable diameter string type

if "${GenerarMovie}==on" then &
"dump	dump_movie all movie $N ${file} ${color} ${diameter} &
  size 1200 1200 &
  zoom 2.5 &
  axes no 0 0 &
  box no 0"
```
El comando `dump` es complejo. Su **estructura** es

    dump ID group-ID style N file color diameter keyword value ...

**Parámetros**

    ID = nombre asignado, por el usuario, a este depósito

    group-ID = ID del grupo de átomos que se imprimirá sobre la imagen

    style = image o movie (son los que nos ocupan ahora) = estilo del comando `dump`

    N = depositar cada este número de pasos

    file = nombre del archivo de imagen

    color = atributo del átomo que determina su color

    diameter = atributo del átomo que determina su tamaño

**Palabras clave**

    size values = width height = tamaño de las imágenes
      width = ancho de la imagen en pixeles
      height = altura de la imagen en pixeles

    zoom value = zfactor = tamaño de la caja de simulación en la imagen
      zfactor = escala el tamaño de la imagen por un factor > 1 para agrandar, 
                un factor < 1 para encojer

    box values = yes/no diam = dibujar el contorno de la caja de simulación
      yes/no = dibujar o no las líneas de la caja
      diam = diámetro de las líneas de la caja 
             como fracción de la dimensión más pequeña de la caja

    axes values = yes/no length diam = dibujar los ejes xyz
      yes/no = dibujar los ejes xyz o no junto a la caja de simulación
      length = longitud de las líneas de los ejes 
               como fracción de la respectiva dimensión de la caja
      diam = diámetro de las líneas de los ejes 
             como fracción de la dimensión más pequeña de la caja

Depositar una imagen de la configuración de los átomos cada N pasos y guardarlas o bien como una secuencia de archivos JPEG o PNG o PPM, o como un único archivo de video.
El estilo `style = movie` hace esto último.

Los parámetros `color` y `diameter` determinan el color y el tamaño de los átomos impresos en la imagen.
Estos pueden venir dados por cualquier atributo de los átomos que pueda pasarse como valor al comando `dump custom`, incluyendo `type` y `element`.
Esto incluye cantidades que varíen átomo por átomo, calculadas por un comando `compute`, `fix` o `variable`, que reciben los prefijos `c_`, `f_` o `v_` respectivamente.

Si `type` es el valor de `color`, entonces el color de cada átomo es determinado por su tipo de átomo.
Los colores por defecto que produce esta configuración para cada tipo de átomo pueden consultarse en la [documentación](https://docs.lammps.org/dump_image.html).

Si `type` es el valor de `diameter` entonces el diametro de cada átomo es determinado por su tipo de átomo.
Por defecto, todos los tipos tienen diametro `1.0`.

```
variable archivoTraza string ${DirectorioOut}${NombreDeBase}__traza
fix printTraza all print ${PasosDatos} "time x[1] y[1] z[1]" &
  file ${archivoTraza} &
  screen no &
  title "#tiempo [fms]   X [Ang]    Y [Ang]       Z [Ang]"

variable EnergiaCinetica equal 0.5*${MasaElectron}*(vx[1]^2+vy[1]^2+vz[1]^2)
variable archivoEnergiaCinetica string ${DirectorioOut}${NombreDeBase}__energia_cinetica
fix printEnergia all print ${PasosDatos} "time ${EnergiaCinetica}" &
  file ${archivoEnergiaCinetica} &
  screen no &
  title "#tiempo [fms] EnergiaCineticaTotal [grams.angs^2/(mole.fms^2)]"
```

    fix ID group-ID print N string keyword value ...
    ID, group-ID are documented in fix command

    print = style name of this fix command

    N = print every N steps; N can be a variable (see below)

    string = text string to print with optional variable names

    zero or more keyword/value pairs may be appended

    keyword = file or append or screen or title

    file value = filename
    append value = filename
    screen value = yes or no
    title value = string
      string =  text to print as 1st line of output file

Imprimir una cadena de texto cada `N` pasos durante una simulación.
Esto puede ser usado con motivo de diagnóstico o como una herramienta de depuración para monitorear alguna cantidad durante una ejecución.
La cadena de texto debe ser un único argumento, por lo que debe ser encerrada en comillas dobles `"..."` si está formado por más de una palabra.
Si contiene variables debe ser encerrado en comillas dobles para asegurar que no sean evaluadas cuando la línea del guion es leída, si no que esta evaluación ocurra cada vez que la cadena es impresa.

Si las palabras clave `file` o `append` son usadas, se especifica el nombre de un archivo en el cual se escribe la salida generada por este `fix`.
Si se usa `file`, entonces el archivo es sobreescribido si es que ya existe.
Si se usa `append`, entonces se adjunta a este archivo si es que ya existe, o creado si es que no existe.

Si la palabra clave `keyword` es usada, la salida de este `fix` a la pantalla y al archivo de registro puede ser activada o desactivada según se lo desee.

La palabra clave `title` permite especificar la cadena que será impresa como la primera línea del archivo de salida, asumiendo que la palabra clave `file` haya sido usada.

Por defecto no se produce salida a un archivo, la palabra cave `screen` es `yes`, y la cadena `title` es `# Fix print output for fix ID`.

```
run ${NumPasosIntegracion}
```
Ejecutar la simulación o continuar con la evolución por un número de pasos determinados.


    WARNING: Communication cutoff is 0.0. No ghost atoms will be generated. Atoms may get lost
The communication cutoff defaults to the maximum of what is inferred from pair and bond styles (will be zero, if none are defined) and what is specified via comm_modify cutoff (defaults to 0.0). If this results to 0.0, no ghost atoms will be generated and LAMMPS may lose atoms or use incorrect periodic images of atoms in interaction lists. To avoid, either use pair style zero with a suitable cutoff or use comm_modify cutoff.