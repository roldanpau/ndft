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
  *		Caller must specify which SM to use (SM1 or SM2) as a command-line
  *		argument.
  *
  * USAGE:	
  *		./interp_omega SM I > outfile
  *		./interp_omega 1 2 > interp_poly_omega_M2
  *		./interp_omega 1 3 > interp_poly_omega_M3
  *
  * CALLED BY:	
  *
  */

#include <stdlib.h>
#include <stdio.h>
#include "T_module.h"
#include "FT_module.h"	// SM_t

static const char ddOmega_FILE[] = "ddOmega.res";
static const char ddOmega_FILE_SM2[] = "ddOmega_SM2.res";

int
main (int argc, char *argv[])
{
	const int ntori=8;		/* Number of tori used in numerical SM */
    double dd[ntori];       /* divided differences of omega(I) */
	SM_t bSM;				/* Which SM (SM1 or SM2) */
	int M;					/* M = Degree of Taylor expansion */
	
	/* auxiliary vars */
	int iSM;
	double I;
	
	if(argc != 3)
	{
		fprintf(stderr, "Num of args incorrect. Usage: %s SM deg\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	iSM = atoi(argv[1]);
	if(iSM==1)
		bSM = SM1;
	else
		bSM = SM2;

	M = atoi(argv[2]);

    /* Read Taylor series (divided differences) from file */
	if(bSM==SM1)	read_T(ntori-1,ddOmega_FILE,dd);
	else			read_T(ntori-1,ddOmega_FILE_SM2,dd);

    double omega;   /* omega(I) */
	for(I=1; I<=7; I += 0.1)
	{
		/* Compute omega(I) for action value I */
		omega_eval(ntori-1,dd,M,I,&omega);
		printf("%g %g\n", I, omega);
	}
	return 0;
}
