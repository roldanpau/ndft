/** \file interp_domega.c
  * \brief Find approximating polynomial to \f$ \pd{\omega}{I}(I)\f$ and plot it.
  *
  * Approximating polynomial is found by derivating the series of 
  * \f$ \omega(I) \f$.
  * 
  * Then evaluate interpolating polynomial \f$ P(I) \f$ at many points (for
  * later plotting P) in the range \f$ I=1 \f$ to \f$ I=7 \f$. (Effectively
  * extrapolating the polynomial to a larger range).
  *
  * NOTES: 
  *		Caller must specify which SM to use (SM1 or SM2) as a command-line
  *		argument.
  *
  *		Degree deg is the degree of omega's series, not the degree of the
  *		derivative series.
  *
  * USAGE:	
  *		./interp_domega SM deg > outfile
  *		./interp_domega 1 5 > interp_poly_domega_M5
  *     ./interp_domega 2 6 > interp_poly_domega_M6_SM2
  *
  * CALLED BY:	
  *     interp_domega.sh
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

    double domega;   /* \pd{\omega}{I} */
	for(I=1; I<=7; I += 0.1)
	{
		/* Compute derivative for action value I */
		domega_eval(ntori-1,dd,M,I,&domega);
		printf("%g %g\n", I, domega);
	}
	return 0;
}
