/** \file max_d2Ltilde_dI.c
  * \brief For each I\in[1,7] find \f$ \max \lvert \pd[2]{\tilde{L}}{I} (I,\phi') \rvert \f$ over all points \phi'.
  *
  *	The degree (N,M) of the Fourier-Taylor series can be modified in the code.
  *
  * NOTES: 
  *     Caller must specify which SM to use (SM1 or SM2) as a command-line
  *     argument.
  *
  * USAGE:
  *		./max_d2Ltilde_dI SM > outfile
  *		./max_d2Ltilde_dI 1 > max_d2Ltilde_dI.res
  *
  * CALLED BY: 
  *		twist.sh
  *
  */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>	// M_PI, fmax, fabs

#include "FT_module.h"

/* Number of points \phi' where \f$\pd[2]{\tilde{L}}{I} (I,\phi')\f$ is evaluated */
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

	double App[N+1];	/* Second derivative of Fourier coefficients A_0(I), A_1(I), ..., A_N(I) */
	double Bpp[N+1];	/* Second derivative of Fourier coefficients B_0(I), B_1(I), ..., B_n(I) */

	double I, phip;

    /* auxiliary vars */
    int iSM;
	double dphi;
	double val,max_val;

	if(argc != 2)
	{
		fprintf(stderr, "Num of args incorrect. Usage: %s SM\n", argv[0]);
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

    /* Read FT series (divided differences) from file */
    read_FT(nfour,ntori,bSM,ddA,ddB);

    for(I=1; I<=7; I += 0.1)
    {
		/* Compute second derivative of F. coefs A_n(I), B_n(I) for action
		 * value I */
		d2coefs_eval(nfour,ntori,ddA,N,M,I,App);
		d2coefs_eval(nfour,ntori,ddB,N,M,I,Bpp);

		max_val = 0;
		dphi = 2*M_PI/(NPOINTS-1);
		for(int i=0; i<NPOINTS; i++)
		{
			phip = i*dphi;
			val = fabs(d2L_dI(N, App, Bpp, phip));
			max_val = fmax(max_val, val);
		}
		printf("%f %f\n", I, max_val);
	}
	return 0;
}
