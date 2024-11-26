/** \file dLstar_dI
  * \brief Given I, find \f$\pd{\tilde{L}}{I} (I,\phi')\f$ at several points \phi'.
  *
  *	The degree (N,M) of the Fourier-Taylor series can be modified in the code.
  *
  * NOTES: 
  *     Caller must specify which SM to use (SM1 or SM2) as a command-line
  *     argument.
  *
  * USAGE:
  *		./dLstar_dI SM scaled_I > outfile
  *		./dLstar_dI 1 2 > dL_dI_I_2.dat
  *
  * CALLED BY: 
  *
  */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>	// M_PI

#include "FT_module.h"

/* Number of points \phi' where \f$\pd{\tilde{L}}{I} (I,\phi')\f$ is evaluated */
const int NPOINTS = 100;	

int
main (int argc, char *argv[])
{
	const int nfour=65; 	/* Number of Fourier coeffs used in FFT */
	const int ntori=8;		/* Number of tori used in numerical SM */

	double ddA[nfour][ntori];	/* divided differences of Fourier coeffs A_n(I) */
	double ddB[nfour][ntori];	/* divided differences of Fourier coeffs B_n(I) */

	int N;	/* Degree of Fourier expansion */
	int M;	/* Degree of Taylor expansion */

    SM_t bSM;           /* Which SM (SM1 or SM2) */

	double Ap[N+1];	/* Derivative of Fourier coefficients A_0(I), A_1(I), ..., A_N(I) */
	double Bp[N+1];	/* Derivative of Fourier coefficients B_0(I), B_1(I), ..., B_n(I) */

	double I, phip;

    /* auxiliary vars */
    int iSM;
	double dphi;

	if(argc != 3)
	{
		fprintf(stderr, "Num of args incorrect. Usage: %s SM scaled_I\n", argv[0]);
		exit(EXIT_FAILURE);
	}
  
    iSM = atoi(argv[1]);
    if(iSM==1)
	{
        bSM = SM1;
		N=4; M=5;
	}
    else
	{
        bSM = SM2;
		N=4; M=6;
	}

    I = atof(argv[2]);      /* scaled action level, e.g. I=2 */

    /* Read FT series (divided differences) from file */
    read_FT(nfour,ntori,bSM,ddA,ddB);

	/* Compute derivative of F. coefs A_n(I), B_n(I) for action value I */
    dcoefs_eval(nfour,ntori,ddA,N,M,I,Ap);
    dcoefs_eval(nfour,ntori,ddB,N,M,I,Bp);

	dphi = 2*M_PI/(NPOINTS-1);
	for(int i=0; i<NPOINTS; i++)
	{
		phip = i*dphi;

		/* Find dL_dphi(I,phi'). */
		printf("%f %f %f\n", I, phip, dL_dI(N, Ap, Bp, phip));
	}
	return 0;
}
