/** \file IM_module.c
  * \brief Functions to compute the inner map \f$ (I', \phi') = \tau(I,\phi) \f$.
  *
  * CALLED BY: IM	
  *
  */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>       // M_PI
#include "T_module.h"   // constrainAngle

/**
  * \brief Compute the inner map \f$ (I', \phi') = \tau(I,\phi) \f$.
  *
  * NOTE:
  *		If the initial condition \f$ (I, \phi) \f$ is outside the valid domain
  *		of the IM, we don't iterate. In that case, the function silently
  *		returns \f$ (I, \phi) \f$ as the final condition.
  *
  *		The output angle \f$\phi'\f$ is forced to be in \f$[0, \pi)\f$.
  */
void IM(double I, double phi, double *Ip, double *phip)
{
    double nu;   /* Interpolated nu value at I */
    double nu0;   /* Interpolated nu value at I=0 */
    double nu7;   /* Interpolated nu value at I=7 */

	if(I<=0 || I>7)	/* Initial condition is outside valid domain of IM */
	{
		fprintf(stderr, "I.C. outside valid domain of IM\n");
		*Ip = I;
		*phip = phi;
		return;
	}

    /* Compute nu(I) for action value I as the linear interpolation between 
     * \f$\nu(I=0)\f$ and \f$\nu(I=7)\f$. */
    nu0 = 2*M_PI*2.0173992405867889e+00/2.0763641364824408e+00;
    nu7 = 2*M_PI*2.0155777552071199e+00/2.0781208798199020e+00;
    nu = nu0*((7-I)/7) + nu7*((I-0)/7);

	/* Find the image (I', \phi') of (I,phi) by the inner map. */
    *phip = constrainAngle(phi + nu);
    *Ip = I;
}
