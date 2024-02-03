/** \file interp_coef.c
  * \brief Find approximating polynomial to Fourier coefficients \f$A_n(I)\f$.
  *
  * Given the data \f$A_n(I=1), dotsc, A_n(I=7)\f$, find the best approximating
  * polynomial \f$ P(I) \f$ of degree \f$M \leq 6 \f$ to those values.
  * Given the desired degree \f$M\f$, interpolate the \f$ M+1 \f$ first points
  * to obtain \f$ P(I) \f$. 
  * Then evaluate interpolating polynomial \f$ P(I) \f$ at many points (for
  * later plotting P) in the range \f$ I=1 \f$ to \f$ I=7 \f$. (Effectively
  * extrapolating the polynomial to a larger range).
  *
  * NOTES: 
  *
  * USAGE:	
  *		./interp_coef 1 four deg > interp_poly_A2
  *		./interp_coef 0 four deg > interp_poly_B2
  *
  * CALLED BY:	
  *
  */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>		// fabs
#include "FT_module.h"

int
main (int argc, char *argv[])
{
	const int nfour=64; 	/* Number of Fourier coeffs used in FFT */
	const int ntori=7;		/* Number of tori used in numerical SM */

	double ddA[nfour][ntori];	/* divided differences of Fourier coeffs A_n(I) */
	double ddB[nfour][ntori];	/* divided differences of Fourier coeffs B_n(I) */

	double I;

	if(argc != 4)
	{
		fprintf(stderr, "Num of args incorrect. Usage: %s isA four deg\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	/* isA = 1 means interpolate A_n, isA=0 means interpolate B_n */
	int isA = atoi(argv[1]);	
	int N = atoi(argv[2]);	/* N = Fourier coefficient */
	int M = atoi(argv[3]);	/* M = Degree of Taylor expansion */

    /* Read FT series (divided differences) from file */
    read_FT(nfour,ntori,ddA,ddB);

	if(isA)
	{
		double A[N+1];	/* Fourier coefficients A_0(I), A_1(I), ..., A_N(I) */

		for(I=1; I<=7; I += 0.1)
		{
			/* Compute F. coef A_n(I) for action value I */
			coefs_eval(nfour,ntori,ddA,N,M,I,A);
			printf("%g %g\n", I, A[N]);
		}
	}
	else // isB
	{
		double B[N+1];	/* Fourier coefficients B_0(I), B_1(I), ..., B_N(I) */

		for(I=1; I<=7; I += 0.1)
		{
			/* Compute F. coef B_n(I) for action value I */
			coefs_eval(nfour,ntori,ddB,N,M,I,B);
			printf("%g %g\n", I, B[N]);
		}
	}
	return 0;
}
