/** \file twist.c
  * \brief Compute the twist \f$\pd{\phi'}{I}(I,\phi')\f$.
  *
  * NOTES: 
  *     Caller must specify which SM to use (SM1 or SM2) as a command-line
  *     argument.
  *
  *		The degree (N,M) of the Fourier-Taylor series can be modified in the
  *		code.
  *
  * USAGE:
  *		./twist SM > outfile
  *		./twist 1 > twist.res
  *
  * CALLED BY: 
  *		twist.sh
  *
  */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>	// M_PI, fmax, fabs

#include "T_module.h"	// read_T, domega_eval
#include "FT_module.h"	// d2coefs_eval, d2L_dI, d2L_dphidI

/* Number of points \phi' where twist is evaluated */
const int NPOINTS = 100;	

static const char ddOmega_FILE[] = "ddOmega.res";
static const char ddOmega_FILE_SM2[] = "ddOmega_SM2.res";

int
main (int argc, char *argv[])
{
	const int nfour=65; 	/* Number of Fourier coeffs used in FFT */
	const int ntori=8;		/* Number of tori used in numerical SM */

	double ddA[nfour][ntori];	/* divided differences of Fourier coeffs A_n(I) */
	double ddB[nfour][ntori];	/* divided differences of Fourier coeffs B_n(I) */

    double dd_omega[ntori];       /* divided differences of omega(I) */

	int N;	/* Degree of Fourier expansion */
	int M;	/* Degree of Taylor expansion */

    SM_t bSM;           /* Which SM (SM1 or SM2) */

	double Ap[N+1];		/* Derivative of Fourier coefficients A_0(I), A_1(I), ..., A_N(I) */
	double Bp[N+1];		/* Derivative of Fourier coefficients B_0(I), B_1(I), ..., B_n(I) */
	double App[N+1];	/* Second derivative of Fourier coefficients A_0(I), A_1(I), ..., A_N(I) */
	double Bpp[N+1];	/* Second derivative of Fourier coefficients B_0(I), B_1(I), ..., B_n(I) */

	double I, phip;

    /* auxiliary vars */
    int iSM;
	double dphi;
	double domega;
	double twist;

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
		read_T(ntori-1,ddOmega_FILE,dd_omega);
	}
    else
	{
        bSM = SM2;
		N=4; M=6;
		read_T(ntori-1,ddOmega_FILE_SM2,dd_omega);
	}

    /* Read FT series (divided differences) from file */
    read_FT(nfour,ntori,bSM,ddA,ddB);

    for(I=1; I<=7; I += 0.1)
    {
        /* Compute derivative of omega for action value I */
        domega_eval(ntori-1,dd_omega,M,I,&domega);

		/* Compute Derivative of F. coefs A_n(I), B_n(I) for action value I */
		dcoefs_eval(nfour,ntori,ddA,N,M,I,Ap);
		dcoefs_eval(nfour,ntori,ddB,N,M,I,Bp);

		/* Compute second derivative of F. coefs A_n(I), B_n(I) for action
		 * value I */
		d2coefs_eval(nfour,ntori,ddA,N,M,I,App);
		d2coefs_eval(nfour,ntori,ddB,N,M,I,Bpp);

		dphi = 2*M_PI/(NPOINTS-1);
		for(int i=0; i<NPOINTS; i++)
		{
			phip = i*dphi;
			twist = -(domega + d2L_dI(N, App, Bpp, phip))/(1+d2L_dphidI(N, Ap, Bp, phip));
			printf("%f %f %f\n", I, phip, twist);
		}
		printf("\n");	// Next datablock
	}
	return 0;
}
