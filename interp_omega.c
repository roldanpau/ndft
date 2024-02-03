/** \file interp_omega.c
  * \brief Find approximating polynomial to \f$\omega(I)\f$.
  *
  * Given the data \f$\omega(I=1), dotsc, \omega(I=7)\f$, find the best
  * approximating polynomial \f$ P(I) \f$ of degree \f$M \leq 6 \f$ to those
  * values.
  * Given the desired degree \f$M\f$, interpolate the \f$ M+1 \f$ first points
  * to obtain \f$ P(I) \f$. 
  * Then evaluate interpolating polynomial \f$ P(I) \f$ at many points (for
  * later plotting P) in the range \f$ I=1 \f$ to \f$ I=7 \f$. (Effectively
  * extrapolating the polynomial to a larger range).
  *
  * NOTES: 
  *
  * USAGE:	
  *		./interp_omega 2 > interp_poly_omega_M2
  *		./interp_omega 3 > interp_poly_omega_M3
  *
  * CALLED BY:	
  *
  */

#include <stdlib.h>
#include <stdio.h>
#include "T_module.h"

int
main (int argc, char *argv[])
{
	const int ntori=7;		/* Number of tori used in numerical SM */

    double dd[ntori];           /* divided differences of omega(I) */

	double I;

	if(argc != 2)
	{
		fprintf(stderr, "Num of args incorrect. Usage: %s deg\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	int M = atoi(argv[1]);	/* M = Degree of Taylor expansion */

    /* Read Taylor series (divided differences) from file */
    read_T(ntori,dd);

    double omega;   /* omega(I) */
	for(I=1; I<=7; I += 0.1)
	{
		/* Compute omega(I) for action value I */
		omega_eval(ntori,dd,M,I,&omega);
		printf("%g %g\n", I, omega);
	}
	return 0;
}
