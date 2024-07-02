/** \file TM_module.c
  * \brief Functions to compute the transition map \f$ (I', \phi') = \gamma(I,\phi) \f$.
  *
  *	The degree (N,M) of the Fourier-Taylor series are provided as parameters to
  *	function TM.
  *
  * CALLED BY: diffusion_shortest_path_TM.c
  *
  */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>       // M_PI
#include "FT_module.h"
#include "T_module.h"
#include "IM_module.h"
#include "SM_module.h"

/**
  * \brief Compute the transition map \f$ (I', \phi') = \gamma(I,\phi) \f$.
  *
  * NOTE:
  *		The degree of the Fourier-Taylor expansion used is \f$N, M\f$ (provided
  *		as parameters to this function).
  *
  *		If the initial condition \f$ (I, \phi) \f$ is outside the known domain
  *		of the SM, we don't iterate. In that case, the function silently
  *		returns \f$ (I, \phi) \f$ as the final condition.
  *
  * \return SUCCESS or ERR_IC_OUTSIDE_DOM when IC is outside domain of SM.
  */
int TM(int nfour, int ntori, double ddA[nfour][ntori], 
        double ddB[nfour][ntori], double ddOmega[ntori-1], int N, int M, double
        I, double phi, double *Ip, double *phip)
{
	/* Auxiliary variables */
	double Ip1, phip1;
	double Ip2, phip2;
	int err;

	/* Recall that TM is the composition of IM \circ SM \circ IM */
	IM(I, phi, &Ip1, &phip1);
	err = SM(nfour, ntori, ddA, ddB, ddOmega, N, M, Ip1, phip1, &Ip2, &phip2);
	if(err)
	{
		/* If the initial condition \f$ (I, \phi) \f$ is outside the known domain
		 * of the SM, we don't iterate. In that case, the function silently
		 * returns \f$ (I, \phi) \f$ as the final condition.
		 */
		fprintf(stderr, "Error computing transition map! Not iterating.\n");
		*Ip = I;
		*phip = phi;
		return err;
	}
	IM(Ip2, phip2, Ip, phip);
	return SUCCESS;
}
