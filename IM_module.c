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
  *		The output angle \f$\phi'\f$ is forced to be in \f$[0, 2\pi)\f$.
  */
void IM(double I, double phi, double *Ip, double *phip)
{
    double nu;   /* Interpolated nu value at I */
    double nu2;   /* Interpolated nu value at I=2 */
    double nu6;   /* Interpolated nu value at I=6 */

	if(I<2 || I>6)	/* Initial condition is outside valid domain of IM */
	{
		fprintf(stderr, "I.C. outside valid domain of IM\n");
		*Ip = I;
		*phip = phi;
		return;
	}

    /* Compute nu(I) for action value I as the linear interpolation between 
     * \f$\nu(I=2)\f$ and \f$\nu(I=6)\f$. */
    nu2 = 2*M_PI*2.0168580747531935/2.0768829346313389;
    nu6 = 2*M_PI*2.0158262483234082/2.0778794649847017;
    nu = nu2*((6-I)/4) + nu6*((I-2)/4);

	/* Find the image (I', \phi') of (I,phi) by the inner map. */
    *phip = constrainAngle(phi + nu);
    *Ip = I;
}
