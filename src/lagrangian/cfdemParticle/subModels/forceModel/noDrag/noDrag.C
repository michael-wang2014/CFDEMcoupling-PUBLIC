/*---------------------------------------------------------------------------*\
    CFDEMcoupling - Open Source CFD-DEM coupling

    CFDEMcoupling is part of the CFDEMproject
    www.cfdem.com
                                Christoph Goniva, christoph.goniva@cfdem.com
                                Copyright 2009-2012 JKU Linz
                                Copyright 2012-     DCS Computing GmbH, Linz
-------------------------------------------------------------------------------
License
    This file is part of CFDEMcoupling.

    CFDEMcoupling is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 3 of the License, or (at your
    option) any later version.

    CFDEMcoupling is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with CFDEMcoupling; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Description
    This code is designed to realize coupled CFD-DEM simulations using LIGGGHTS
    and OpenFOAM(R). Note: this code is not part of OpenFOAM(R) (see DISCLAIMER).
\*---------------------------------------------------------------------------*/

#include "error.H"

#include "noDrag.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(noDrag, 0);

addToRunTimeSelectionTable
(
    forceModel,
    noDrag,
    dictionary
);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from components
noDrag::noDrag
(
    const dictionary& dict,
    cfdemCloud& sm
)
:
    forceModel(dict,sm),
    propsDict_(dict),
    verbose_(false),
    noDEMForce_(false)
{
    if(dict.found(word(typeName + "Props")))
        propsDict_=dictionary(dict.subDict(typeName + "Props"));

    if (propsDict_.found("noDEMForce")) noDEMForce_=true;

    if (propsDict_.found("keepCFDForce")) keepCFDForce_=true;

    coupleForce_=false;
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

noDrag::~noDrag()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void noDrag::setForce() const
{
    // Do nothing
    Info << "noDrag::setForce" << endl;
    for(int index = 0;index <  particleCloud_.numberOfParticles(); ++index)
    {
        // set force on particle
        if(!keepCFDForce_)
        {
            if(treatExplicit_) for(int j=0;j<3;j++) expForces()[index][j] = 0.;
            else  for(int j=0;j<3;j++) impForces()[index][j] = 0.;
        }
        if(noDEMForce_)for(int j=0;j<3;j++) DEMForces()[index][j] = 0.;
        
    }
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //
