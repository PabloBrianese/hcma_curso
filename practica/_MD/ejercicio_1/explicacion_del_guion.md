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
# Poner la variable "GenerarMovie" en on/off
# segun se quiera o no generar la movie
variable GenerarMovie string "off"
```

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
```
```
# creamos el directorio DirectorioOut (si es que no existe...)
shell 'mkdir --parents' ${DirectorioOut}
```
Execute a shell command.
A few simple file-based shell commands are supported directly, in Unix-style syntax.
Any command not listed above is passed as-is to the C-library system() call, which invokes the command in a shell.

This is means to invoke other commands from your input script.
For example, you can move files around in preparation for the next section of the input script.
Or you can run a program that pre-processes data for input into LAMMPS.
Or you can run a program that post-processes LAMMPS output data.

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
Set the timestep size for subsequent molecular dynamics simulations.
See the units command for the time units associated with each choice of units that LAMMPS supports.

The default value for the timestep size also depends on the choice of units for the simulation; see the default values below.

real default timestep is 1.0 fs

```
region CAJA_SISTEMA block ${xlo} ${xhi} ${ylo} ${yhi} ${zlo} ${zhi}
```
This command defines a geometric region of space.
Various other commands use regions.
For example, the region can be filled with atoms via the create_atoms command.
Or a bounding box around the region, can be used to define the simulation box via the create_box command.
Or the atoms in the region can be identified as a group via the group command, or deleted via the delete_atoms command.
Or the surface of the region can be used as a boundary wall via the fix wall/region command.

Commands which use regions typically test whether an atom’s position is contained in the region or not.
For this purpose, coordinates exactly on the region boundary are considered to be interior to the region.
This means, for example, for a spherical region, an atom on the sphere surface would be part of the region if the sphere were defined with the side in keyword, but would not be part of the region if it were defined using the side out keyword.
See more details on the side keyword below.

block args = xlo xhi ylo yhi zlo zhi
  xlo,xhi,ylo,yhi,zlo,zhi = bounds of block in all dimensions (distance units)

```
create_box 1 CAJA_SISTEMA 
```
create_box N region-ID

N = # of atom types to use in this simulation

region-ID = ID of region to use as simulation domain

This command creates a simulation box based on the specified region.
Thus a region command must first be used to define a geometric domain.
It also partitions the simulation box into a regular 3d grid of rectangular bricks, one per processor, based on the number of processors being used and the settings of the processors command.
The partitioning can later be changed by the balance or fix balance commands.

The argument N is the number of atom types that will be used in the simulation.

An atom_style and region must have been previously defined to use this command.

```
################################################################################
# SECCCION DE INSERCION DE ATOMOS EN EL SISTEMA
################################################################################

create_atoms 1 single ${x_ini} ${y_ini} ${z_ini}
```
This command creates atoms (or molecules) on a lattice, or a single atom (or molecule), or a random collection of atoms (or molecules), as an alternative to reading in their coordinates explicitly via a read_data or read_restart command.
A simulation box must already exist, which is typically created via the create_box command.
Before using this command, a lattice must also be defined using the lattice command, unless you specify the single style with units = box or the random style.
For the remainder of this doc page, a created atom or molecule is referred to as a “particle”.

If created particles are individual atoms, they are assigned the specified atom type, though this can be altered via the basis keyword as discussed below.
If molecules are being created, the type of each atom in the created molecule is specified in the file read by the molecule command, and those values are added to the specified atom type.
E.g.
if type = 2, and the file specifies atom types 1,2,3, then each created molecule will have atom types 3,4,5.

For the single style, a single particle is added to the system at the specified coordinates.
This can be useful for debugging purposes or to create a tiny system with a handful of particles at specified positions.

An atom_style must be previously defined to use this command.



```
# masa del electrón en gramos/mol
# notar que 1 gramos/mol = 1 gr /N_A, donde N_A es el número de avogadro
variable MasaElectron equal 0.00054854
mass 1 ${MasaElectron}
```
Set the mass for all atoms of one or more atom types.
Per-type mass values can also be set in the read_data data file using the “Masses” keyword.
See the units command for what mass units to use.

Note that the mass command can only be used if the atom style requires per-type atom mass to be set.

This command must come after the simulation box is defined by a read_data, read_restart, or create_box command.

All masses must be defined before a simulation is run.
They must also all be defined before a velocity or fix shake command is used.

The mass assigned to any type or atom must be > 0.0.

```
# seteamos la carga del electrón, consistentemente con el sistema de 
# unidades de lammps "real"
variable CargaElectron equal -1
set type 1 charge ${CargaElectron}
```
Set one or more properties of one or more atoms.
Since atom properties are initially assigned by the read_data, read_restart or create_atoms commands, this command changes those assignments.
This can be useful for overriding the default values assigned by the create_atoms command (e.g.
charge = 0.0).
It can be useful for altering pairwise and molecular force interactions, since force-field coefficients are defined in terms of types.
It can be used to change the labeling of atoms by atom type or molecule ID when they are output in dump files.
It can also be useful for debugging purposes; i.e.
positioning an atom at a precise location to compute subsequent forces or energy.

Note that the style and ID arguments determine which atoms have their properties reset.
The remaining keywords specify which properties to reset and what the new values are.
Some strings like type or mol can be used as a style and/or a keyword.

Keywords x, y, z, and charge set the coordinates or charge of all selected atoms.
For charge, the atom style being used must support the use of atomic charge.
Keywords vx, vy, and vz set the velocities of all selected atoms.

```
# seteamos la velocidad del electrón
velocity all set ${vx_ini} ${vy_ini} ${vz_ini}
```
Set or change the velocities of a group of atoms in one of several styles.
For each style, there are required arguments and optional keyword/value parameters.
Not all options are used by each style.
Each option has a default as listed below.

The set style sets the velocities of all atoms in the group to the specified values.
If any component is specified as NULL, then it is not set.
Any of the vx,vy,vz velocity components can be specified as an equal-style or atom-style variable.
If the value is a variable, it should be specified as v_name, where name is the variable name.
In this case, the variable will be evaluated, and its value used to determine the velocity component.
Note that if a variable is used, the velocity it calculates must be in box units, not lattice units; see the discussion of the units keyword below.

```
# seteamos el campo eléctrico externo
fix fix_campo_electrico all efield 0.0 ${IntensityElectr} 0.0
```
Set a fix that will be applied to a group of atoms.
In LAMMPS, a “fix” is any operation that is applied to the system during timestepping or minimization.
Examples include updating of atom positions and velocities due to time integration, controlling temperature, applying constraint forces to atoms, enforcing boundary conditions, computing diagnostics, etc.
There are hundreds of fixes defined in LAMMPS and new ones can be added; see the Modify doc page for details.

Fixes perform their operations at different stages of the timestep.
If 2 or more fixes operate at the same stage of the timestep, they are invoked in the order they were specified in the input script.

fix efield command

fix ID group-ID efield ex ey ez

Add a force F = qE to each charged atom in the group due to an external electric field being applied to the system.
If the system contains point-dipoles, also add a torque on the dipoles due to the external electric field.

For charges, any of the 3 quantities defining the E-field components can be specified as an equal-style or atom-style variable, namely ex, ey, ez.
If the value is a variable, it should be specified as v_name, where name is the variable name.
In this case, the variable will be evaluated each timestep, and its value used to determine the E-field component.

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
Add fx,fy,fz to the corresponding component of force for each atom in the group.
This command can be used to give an additional push to atoms in a simulation, such as for a simulation of Poiseuille flow in a channel.

Any of the 3 quantities defining the force components can be specified as an equal-style or atom-style variable, namely fx, fy, fz.
If the value is a variable, it should be specified as v_name, where name is the variable name.
In this case, the variable will be evaluated each timestep, and its value(s) used to determine the force component.

```
# termostato para la integración a energía constante
fix termostato all nve
```
nve: constant number, volume and energy

fix ID group-ID nve

ID, group-ID are documented in fix command

nve = style name of this fix command

Perform constant NVE integration to update position and velocity for atoms in the group each timestep.
V is volume; E is energy.
This creates a system trajectory consistent with the microcanonical ensemble.

```
if "${GenerarMovie}==on" then &
"dump	dump_movie all movie ${PasosGuardarFigurasParaMovie} ${DirectorioOut}${NombreDeBase}.mpg type type size 1200 1200 &
zoom 2.5 axes no 0 0 box no 0"
```
dump ID group-ID style N file color diameter keyword value ...

ID = user-assigned name for the dump

group-ID = ID of the group of atoms to be imaged

style = image or movie = style of dump command (other styles atom or cfg or dcd or xtc or xyz or local or custom are discussed on the dump doc page)

N = dump every this many timesteps

file = name of file to write image to

color = atom attribute that determines color of each atom

diameter = atom attribute that determines size of each atom

zero or more keyword/value pairs may be appended

keyword = atom or adiam or bond or line or tri or body or fix or size or view or center or up or zoom or box or axes or subbox or shiny or ssao

Dump a high-quality rendered image of the atom configuration every N timesteps and save the images either as a sequence of JPEG or PNG or PPM files, or as a single movie file.
The options for this command as well as the dump_modify command control what is included in the image or movie and how it appears.
A series of such images can easily be manually converted into an animated movie of your simulation or the process can be automated without writing the intermediate files using the dump movie style; see further details below.
Other dump styles store snapshots of numerical data associated with atoms in various formats, as discussed on the dump doc page.

The color and diameter settings determine the color and size of atoms rendered in the image.
They can be any atom attribute defined for the dump custom command, including type and element.
This includes per-atom quantities calculated by a compute, fix, or variable, which are prefixed by “c_”, “f_”, or “v_” respectively.
Note that the diameter setting can be overridden with a numeric value applied to all atoms by the optional adiam keyword.

If type is specified for the color setting, then the color of each atom is determined by its atom type.
By default the mapping of types to colors is as follows:

type 1 = red

type 2 = green

type 3 = blue

type 4 = yellow

type 5 = aqua

type 6 = cyan

and repeats itself for types > 6.
This mapping can be changed by the dump_modify acolor command.

If type is specified for the diameter setting then the diameter of each atom is determined by its atom type.
By default all types have diameter 1.0.
This mapping can be changed by the dump_modify adiam command.

size values = width height = size of images

  width = width of image in # of pixels

  height = height of image in # of pixels

zoom value = zfactor = size that simulation box appears in image
  
  zfactor = scale image size by factor > 1 to enlarge, factor < 1 to shrink
  
  zfactor can be a variable (see below)

box values = yes/no diam = draw outline of simulation box

  yes/no = do or do not draw simulation box lines

  diam = diameter of box lines as fraction of shortest box length

box values = yes/no diam = draw outline of simulation box

  yes/no = do or do not draw simulation box lines

  diam = diameter of box lines as fraction of shortest box length

axes values = yes/no length diam = draw xyz axes

  yes/no = do or do not draw xyz axes lines next to simulation box

  length = length of axes lines as fraction of respective box lengths

  diam = diameter of axes lines as fraction of shortest box length

```
variable TrazaX equal x[1]
variable TrazaY equal y[1]
variable TrazaZ equal z[1]

fix printTraza all print ${PasosDatos} &
"${tiempo} ${TrazaX} ${TrazaY} ${TrazaZ}" &
file ${DirectorioOut}${NombreDeBase}__traza screen no &
title "#tiempo [fms]   X [Ang]    Y [Ang]       Z [Ang]"

# Definimos algunas variables utiles para el output de la info termodinamica
variable tiempo equal time
variable EnergiaCinetica equal 0.5*${MasaElectron}*(vx[1]^2+vy[1]^2+vz[1]^2)

fix printEnergia all print ${PasosDatos} &
"${tiempo} ${EnergiaCinetica}" &
file ${DirectorioOut}${NombreDeBase}__energia_cinetica screen no &
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

Print a text string every N steps during a simulation run.
This can be used for diagnostic purposes or as a debugging tool to monitor some quantity during a run.
The text string must be a single argument, so it should be enclosed in double quotes if it is more than one word.
If it contains variables it must be enclosed in double quotes to insure they are not evaluated when the input script line is read, but will instead be evaluated each time the string is printed.

If the file or append keyword is used, a filename is specified to which the output generated by this fix will be written.
If file is used, then the filename is overwritten if it already exists.
If append is used, then the filename is appended to if it already exists, or created if it does not exist.

If the screen keyword is used, output by this fix to the screen and logfile can be turned on or off as desired.

The title keyword allow specification of the string that will be printed as the first line of the output file, assuming the file keyword was used.

The option defaults are no file output, screen = yes, and title string as described above.

```
run ${NumPasosIntegracion}
```

Run or continue dynamics for a specified number of timesteps.