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
Este comando fija los parámetros que afectan la comunicación entre procesadores, de información sobre los átomos, que ocurre en cada paso mientras coordenadas y otras propiedades son intercambiadas entre procesadores vecinos y almacenadas como propiedades de átomos fantasma (`ghost atoms`).

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
```
sort values = Nfreq binsize
  Nfreq = sort atoms spatially every this many time steps
  binsize = bin size for spatial sorting (distance units)
```

Modify certain attributes of atoms defined and stored within LAMMPS, in addition to what is specified by the atom_style command.
The id and map keywords must be specified before a simulation box is defined; other keywords can be specified any time.

The map keyword determines how atoms with specific IDs are found when required.
An example are the bond (angle, etc) methods which need to find the local index of an atom with a specific global ID which is a bond (angle, etc) partner.
LAMMPS performs this operation efficiently by creating a “map”, which is either an array or hash table, as described below.

When the map keyword is not specified in your input script, LAMMPS only creates a map for atom_styles for molecular systems which have permanent bonds (angles, etc).
No map is created for atomic systems, since it is normally not needed.
However some LAMMPS commands require a map, even for atomic systems, and will generate an error if one does not exist.
The map keyword thus allows you to force the creation of a map.
The yes value will create either an array or hash style map, as explained in the next paragraph.
The array and hash values create an atom-style or hash-style map respectively.

For an array-style map, each processor stores a lookup table of length N, where N is the largest atom ID in the system. This is a fast, simple method for many simulations, but requires too much memory for large simulations. For a hash-style map, a hash table is created on each processor, which finds an atom ID in constant time (independent of the global number of atom IDs). It can be slightly slower than the array map, but its memory cost is proportional to the number of atoms owned by a processor, i.e. N/P when N is the total number of atoms in the system and P is the number of processors.

The sort keyword turns on a spatial sorting or reordering of atoms within each processor’s sub-domain every Nfreq timesteps. If Nfreq is set to 0, then sorting is turned off. Sorting can improve cache performance and thus speed-up a LAMMPS simulation, as discussed in a paper by (Meloni). Its efficacy depends on the problem size (atoms/processor), how quickly the system becomes disordered, and various other factors. As a general rule, sorting is typically more effective at speeding up simulations of liquids as opposed to solids. In tests we have done, the speed-up can range from zero to 3-4x.

Reordering is performed every Nfreq timesteps during a dynamics run or iterations during a minimization. More precisely, reordering occurs at the first reneighboring that occurs after the target timestep. The reordering is performed locally by each processor, using bins of the specified binsize. If binsize is set to 0.0, then a binsize equal to half the neighbor cutoff distance (force cutoff plus skin distance) is used, which is a reasonable value. After the atoms have been binned, they are reordered so that atoms in the same bin are adjacent to each other in the processor’s 1d list of atoms.

The goal of this procedure is for atoms to put atoms close to each other in the processor’s one-dimensional list of atoms that are also near to each other spatially. This can improve cache performance when pairwise interactions and neighbor lists are computed. Note that if bins are too small, there will be few atoms/bin. Likewise if bins are too large, there will be many atoms/bin. In both cases, the goal of cache locality will be undermined.

By default, id is yes. By default, atomic systems (no bond topology info) do not use a map. For molecular systems (with bond topology info), a map is used. The default map style is array if no atom ID is larger than 1 million, otherwise the default is hash. By default, a “first” group is not defined. By default, sorting is enabled with a frequency of 1000 and a binsize of 0.0, which means the neighbor cutoff will be used to set the bin size. If no neighbor cutoff is defined, sorting will be turned off.

```
pair_style none
```
Set the formula(s) LAMMPS uses to compute pairwise interactions.

none - turn off pairwise interactions

Using a pair style of none means pair forces and energies are not computed.

With this choice, the force cutoff is 0.0, which means that only atoms within the neighbor skin distance (see the neighbor command) are communicated between processors. You must insure the skin distance is large enough to acquire atoms needed for computing bonds, angles, etc.

A pair style of none will also prevent pairwise neighbor lists from being built. However if the neighbor style is bin, data structures for binning are still allocated. If the neighbor skin distance is small, then these data structures can consume a large amount of memory. So you should either set the neighbor style to nsq or set the skin distance to a larger value.

See the pair_style zero for a way to trigger the building of a neighbor lists, but compute no pairwise interactions.

```
dimension 3
```
Set the dimensionality of the simulation. By default LAMMPS runs 3d simulations. To run a 2d simulation, this command should be used prior to setting up a simulation box via the create_box or read_data commands. Restart files also store this setting.

```
boundary	s s s
```
Set the style of boundaries for the global simulation box in each dimension. A single letter assigns the same style to both the lower and upper face of the box. Two letters assigns the first style to the lower face and the second style to the upper face. The initial size of the simulation box is set by the read_data, read_restart, or create_box commands.

The style p means the box is periodic, so that particles interact across the boundary, and they can exit one end of the box and re-enter the other end. A periodic dimension can change in size due to constant pressure boundary conditions or box deformation (see the fix npt and fix deform commands). The p style must be applied to both faces of a dimension.

The styles f, s, and m mean the box is non-periodic, so that particles do not interact across the boundary and do not move from one side of the box to the other.

For style f, the position of the face is fixed. If an atom moves outside the face it will be deleted on the next timestep that reneighboring occurs. This will typically generate an error unless you have set the thermo_modify lost option to allow for lost atoms.

For style s, the position of the face is set so as to encompass the atoms in that dimension (shrink-wrapping), no matter how far they move. Note that when the difference between the current box dimensions and the shrink-wrap box dimensions is large, this can lead to lost atoms at the beginning of a run when running in parallel. This is due to the large change in the (global) box dimensions also causing significant changes in the individual sub-domain sizes. If these changes are farther than the communication cutoff, atoms will be lost. This is best addressed by setting initial box dimensions to match the shrink-wrapped dimensions more closely, by using m style boundaries (see below).

For style m, shrink-wrapping occurs, but is bounded by the value specified in the data or restart file or set by the create_box command. For example, if the upper z face has a value of 50.0 in the data file, the face will always be positioned at 50.0 or above, even if the maximum z-extent of all the atoms becomes less than 50.0. This can be useful if you start a simulation with an empty box or if you wish to leave room on one side of the box, e.g. for atoms to evaporate from a surface.

This command cannot be used after the simulation box is defined by a read_data or create_box command or read_restart command.

```
#########################################
# tipos con que se asocian las partículas
variable TipoA1 equal 1
```
This command assigns one or more strings to a variable name for evaluation later in the input script or during a simulation.

Variables can thus be useful in several contexts. A variable can be defined and then referenced elsewhere in an input script to become part of a new input command. Variables of style equal store a formula which when evaluated produces a single numeric value.

The Commands parse doc page explains how occurrences of a variable name in an input script line are replaced by the variable’s string. The variable name can be referenced as $x if the name “x” is a single character, or as ${LoopVar} if the name “LoopVar” is one or more characters.


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
Execute a shell command. A few simple file-based shell commands are supported directly, in Unix-style syntax. Any command not listed above is passed as-is to the C-library system() call, which invokes the command in a shell.

This is means to invoke other commands from your input script. For example, you can move files around in preparation for the next section of the input script. Or you can run a program that pre-processes data for input into LAMMPS. Or you can run a program that post-processes LAMMPS output data.

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
Set the timestep size for subsequent molecular dynamics simulations. See the units command for the time units associated with each choice of units that LAMMPS supports.

The default value for the timestep size also depends on the choice of units for the simulation; see the default values below.

real default timestep is 1.0 fs

```
region CAJA_SISTEMA block ${xlo} ${xhi} ${ylo} ${yhi} ${zlo} ${zhi}
```
This command defines a geometric region of space. Various other commands use regions. For example, the region can be filled with atoms via the create_atoms command. Or a bounding box around the region, can be used to define the simulation box via the create_box command. Or the atoms in the region can be identified as a group via the group command, or deleted via the delete_atoms command. Or the surface of the region can be used as a boundary wall via the fix wall/region command.

Commands which use regions typically test whether an atom’s position is contained in the region or not. For this purpose, coordinates exactly on the region boundary are considered to be interior to the region. This means, for example, for a spherical region, an atom on the sphere surface would be part of the region if the sphere were defined with the side in keyword, but would not be part of the region if it were defined using the side out keyword. See more details on the side keyword below.

block args = xlo xhi ylo yhi zlo zhi
  xlo,xhi,ylo,yhi,zlo,zhi = bounds of block in all dimensions (distance units)

```
create_box 1 CAJA_SISTEMA 
```
create_box N region-ID

N = # of atom types to use in this simulation

region-ID = ID of region to use as simulation domain

This command creates a simulation box based on the specified region. Thus a region command must first be used to define a geometric domain. It also partitions the simulation box into a regular 3d grid of rectangular bricks, one per processor, based on the number of processors being used and the settings of the processors command. The partitioning can later be changed by the balance or fix balance commands.

The argument N is the number of atom types that will be used in the simulation.

An atom_style and region must have been previously defined to use this command.

```
################################################################################
# SECCCION DE INSERCION DE ATOMOS EN EL SISTEMA
################################################################################

create_atoms 1 single ${x_ini} ${y_ini} ${z_ini}
```
This command creates atoms (or molecules) on a lattice, or a single atom (or molecule), or a random collection of atoms (or molecules), as an alternative to reading in their coordinates explicitly via a read_data or read_restart command. A simulation box must already exist, which is typically created via the create_box command. Before using this command, a lattice must also be defined using the lattice command, unless you specify the single style with units = box or the random style. For the remainder of this doc page, a created atom or molecule is referred to as a “particle”.

If created particles are individual atoms, they are assigned the specified atom type, though this can be altered via the basis keyword as discussed below. If molecules are being created, the type of each atom in the created molecule is specified in the file read by the molecule command, and those values are added to the specified atom type. E.g. if type = 2, and the file specifies atom types 1,2,3, then each created molecule will have atom types 3,4,5.

For the single style, a single particle is added to the system at the specified coordinates. This can be useful for debugging purposes or to create a tiny system with a handful of particles at specified positions.

An atom_style must be previously defined to use this command.



```
# masa del electrón en gramos/mol
# notar que 1 gramos/mol = 1 gr /N_A, donde N_A es el número de avogadro
variable MasaElectron equal 0.00054854
mass 1 ${MasaElectron}
```
Set the mass for all atoms of one or more atom types. Per-type mass values can also be set in the read_data data file using the “Masses” keyword. See the units command for what mass units to use.

Note that the mass command can only be used if the atom style requires per-type atom mass to be set.

This command must come after the simulation box is defined by a read_data, read_restart, or create_box command.

All masses must be defined before a simulation is run. They must also all be defined before a velocity or fix shake command is used.

The mass assigned to any type or atom must be > 0.0.

```
# seteamos la carga del electrón, consistentemente con el sistema de 
# unidades de lammps "real"
variable CargaElectron equal -1
set type 1 charge ${CargaElectron}
```
Set one or more properties of one or more atoms. Since atom properties are initially assigned by the read_data, read_restart or create_atoms commands, this command changes those assignments. This can be useful for overriding the default values assigned by the create_atoms command (e.g. charge = 0.0). It can be useful for altering pairwise and molecular force interactions, since force-field coefficients are defined in terms of types. It can be used to change the labeling of atoms by atom type or molecule ID when they are output in dump files. It can also be useful for debugging purposes; i.e. positioning an atom at a precise location to compute subsequent forces or energy.

Note that the style and ID arguments determine which atoms have their properties reset. The remaining keywords specify which properties to reset and what the new values are. Some strings like type or mol can be used as a style and/or a keyword.

Keywords x, y, z, and charge set the coordinates or charge of all selected atoms. For charge, the atom style being used must support the use of atomic charge. Keywords vx, vy, and vz set the velocities of all selected atoms.

```
# seteamos la velocidad del electrón
velocity all set ${vx_ini} ${vy_ini} ${vz_ini}
```
Set or change the velocities of a group of atoms in one of several styles. For each style, there are required arguments and optional keyword/value parameters. Not all options are used by each style. Each option has a default as listed below.

The set style sets the velocities of all atoms in the group to the specified values. If any component is specified as NULL, then it is not set. Any of the vx,vy,vz velocity components can be specified as an equal-style or atom-style variable. If the value is a variable, it should be specified as v_name, where name is the variable name. In this case, the variable will be evaluated, and its value used to determine the velocity component. Note that if a variable is used, the velocity it calculates must be in box units, not lattice units; see the discussion of the units keyword below.

```
# seteamos el campo eléctrico externo
fix fix_campo_electrico all efield 0.0 ${IntensityElectr} 0.0
```
Set a fix that will be applied to a group of atoms. In LAMMPS, a “fix” is any operation that is applied to the system during timestepping or minimization. Examples include updating of atom positions and velocities due to time integration, controlling temperature, applying constraint forces to atoms, enforcing boundary conditions, computing diagnostics, etc. There are hundreds of fixes defined in LAMMPS and new ones can be added; see the Modify doc page for details.

Fixes perform their operations at different stages of the timestep. If 2 or more fixes operate at the same stage of the timestep, they are invoked in the order they were specified in the input script.

fix efield command

fix ID group-ID efield ex ey ez

Add a force F = qE to each charged atom in the group due to an external electric field being applied to the system. If the system contains point-dipoles, also add a torque on the dipoles due to the external electric field.

For charges, any of the 3 quantities defining the E-field components can be specified as an equal-style or atom-style variable, namely ex, ey, ez. If the value is a variable, it should be specified as v_name, where name is the variable name. In this case, the variable will be evaluated each timestep, and its value used to determine the E-field component.

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
Add fx,fy,fz to the corresponding component of force for each atom in the group. This command can be used to give an additional push to atoms in a simulation, such as for a simulation of Poiseuille flow in a channel.

Any of the 3 quantities defining the force components can be specified as an equal-style or atom-style variable, namely fx, fy, fz. If the value is a variable, it should be specified as v_name, where name is the variable name. In this case, the variable will be evaluated each timestep, and its value(s) used to determine the force component.

```
# termostato para la integración a energía constante
fix termostato all nve
```
nve: constant number, volume and energy

fix ID group-ID nve

ID, group-ID are documented in fix command

nve = style name of this fix command

Perform constant NVE integration to update position and velocity for atoms in the group each timestep. V is volume; E is energy. This creates a system trajectory consistent with the microcanonical ensemble.

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

Dump a high-quality rendered image of the atom configuration every N timesteps and save the images either as a sequence of JPEG or PNG or PPM files, or as a single movie file. The options for this command as well as the dump_modify command control what is included in the image or movie and how it appears. A series of such images can easily be manually converted into an animated movie of your simulation or the process can be automated without writing the intermediate files using the dump movie style; see further details below. Other dump styles store snapshots of numerical data associated with atoms in various formats, as discussed on the dump doc page.

The color and diameter settings determine the color and size of atoms rendered in the image. They can be any atom attribute defined for the dump custom command, including type and element. This includes per-atom quantities calculated by a compute, fix, or variable, which are prefixed by “c_”, “f_”, or “v_” respectively. Note that the diameter setting can be overridden with a numeric value applied to all atoms by the optional adiam keyword.

If type is specified for the color setting, then the color of each atom is determined by its atom type. By default the mapping of types to colors is as follows:

type 1 = red

type 2 = green

type 3 = blue

type 4 = yellow

type 5 = aqua

type 6 = cyan

and repeats itself for types > 6. This mapping can be changed by the dump_modify acolor command.

If type is specified for the diameter setting then the diameter of each atom is determined by its atom type. By default all types have diameter 1.0. This mapping can be changed by the dump_modify adiam command.

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

Print a text string every N steps during a simulation run. This can be used for diagnostic purposes or as a debugging tool to monitor some quantity during a run. The text string must be a single argument, so it should be enclosed in double quotes if it is more than one word. If it contains variables it must be enclosed in double quotes to insure they are not evaluated when the input script line is read, but will instead be evaluated each time the string is printed.

If the file or append keyword is used, a filename is specified to which the output generated by this fix will be written. If file is used, then the filename is overwritten if it already exists. If append is used, then the filename is appended to if it already exists, or created if it does not exist.

If the screen keyword is used, output by this fix to the screen and logfile can be turned on or off as desired.

The title keyword allow specification of the string that will be printed as the first line of the output file, assuming the file keyword was used.

The option defaults are no file output, screen = yes, and title string as described above.

```
run ${NumPasosIntegracion}
```

Run or continue dynamics for a specified number of timesteps.