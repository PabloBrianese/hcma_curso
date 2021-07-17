/*--------------------------------*- C++ -*----------------------------------*\
| =========                 |                                                 |
| \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           |
|  \\    /   O peration     | Version:  2.3.1                                 |
|   \\  /    A nd           | Web:      www.OpenFOAM.org                      |
|    \\/     M anipulation  |                                                 |
\*---------------------------------------------------------------------------*/
FoamFile
{
    version     2.0;
    format      ascii;
    class       dictionary;
    object      blockMeshDict;
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

convertToMeters 1.0;

dnl  ----- El sistema es una caja cuyas esquinas son el (0,0,-0.5) y  (Lx,Ly,0.5) ----- 

dnl ----- dimensiones de la caja -----

define(Lx,20.0)
define(Ly,10.0)


dnl  ----- numero de divisiones a lo largo de cada eje ----- 

define(NumDivX,60)
define(NumDivY,30)
define(NumDivZ,1)

vertices
(
    (0 0 -0.5)
    (Lx 0 -0.5)
    (Lx Ly -0.5)
    (0 Ly -0.5)
    (0 0 0.5)
    (Lx 0 0.5)
    (Lx Ly 0.5)
    (0 Ly 0.5)
);

blocks
(
    hex (0 1 2 3 4 5 6 7) (NumDivX NumDivY NumDivZ) simpleGrading (1 1 1)
);

edges
(
);

boundary
(
  
    
    xmin
    {
        type wall;
        faces
        (
            (0 4 7 3)
        );
    }
    
    xmax
    {
        type wall;
        faces
        (
            (2 6 5 1)
        );
    }
    
    ymin
    {
        type wall;
        faces
        (
            (1 5 4 0)
        );
    }

    ymax
    {
        type wall;
        faces
        (
            (3 7 6 2)
        );
    }
    
    zmin
    {
        type empty;
        faces
        (
            (0 3 2 1)
        );
    }
    
    zmax
    {
        type empty;
        faces
        (
            (4 5 6 7)
        );
    }
);

mergePatchPairs
(
);

// ************************************************************************* //
