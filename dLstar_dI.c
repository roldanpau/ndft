/* dLstar_dI:
   Given an action value I, find the partial derivative
   $\pd{L^*}{I} (I,\phi')$ at several points \phi'.
   */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>	// M_PI

#include "FT_module.h"

const int NPOINTS = 100;

int
main (int argc, char *argv[])
{
	const int nfour=64; 	/* Number of Fourier coeffs used in FFT */
	const int ntori=5;		/* Number of tori used in numerical SM */

	double ddA[nfour][ntori];	/* divided differences of Fourier coeffs A_n(I) */
	double ddB[nfour][ntori];	/* divided differences of Fourier coeffs B_n(I) */

	const int N=4;	/* Degree of Fourier expansion */
	const int M=2;	/* Degree of Taylor expansion */

	double Ap[N+1];	/* Derivative of Fourier coefficients A_0(I), A_1(I), ..., A_N(I) */
	double Bp[N+1];	/* Derivative of Fourier coefficients B_0(I), B_1(I), ..., B_n(I) */

	double I;

	double phip, dphi;

	if(argc != 2)
	{
		fprintf(stderr, "Num of args incorrect. Usage: %s scaled_I\n", argv[0]);
		exit(EXIT_FAILURE);
	}
  
	I = atof(argv[1]);	/* scaled action level, e.g. I=2 */

    /* Read FT series (divided differences) from file */
    read_FT(nfour,ntori,ddA,ddB);

    dcoefs_eval(nfour,ntori,ddA,N,M,I,Ap);	/* Compute F. coefs A_n(I) for action value I */
    dcoefs_eval(nfour,ntori,ddB,N,M,I,Bp);	/* Compute F. coefs B_n(I) for action value I */

	dphi = 2*M_PI/(NPOINTS-1);
	for(int i=0; i<NPOINTS; i++)
	{
		phip = i*dphi;

		/* Find dL_dphi(I,phi'). */
		printf("%f %f %f\n", I, phip, dL_dI(N, Ap, Bp, phip));
	}
	return 0;
}
