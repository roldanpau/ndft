/** \file Lstar.c
  * \brief Evaluate the function \f$ \widetilde{\mathcal{L}}(I,\phi') \f$ on a grid of \f$ (I,
  * \phi') \f$ points.
  *
  *	NOTES:
  *     Caller must specify which SM to use (SM1 or SM2) as a command-line
  *     argument.
  *
  * USAGE:	./Lstar 1 > Lstar.res (SM1)
  *
  */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>
#include "FT_module.h"      /* widetildeL */

const int NPOINTS_I = 101;		/* num of points in the I direction */
const int NPOINTS_PHI = 101;	/* num of points in the \phi' direction */

int
main (int argc, char *argv[])
{
    const int nfour=65;     /* Number of Fourier coeffs used in FFT */
    const int ntori=8;      /* Number of tori used in numerical SM */

    const int N=4; /* Degree of Fourier expansion */
    const int M=5;  /* Degree of Taylor expansion */

    double A[N+1];  /* Fourier coefficients A_0(I), A_1(I), ..., A_N(I) */
    double B[N+1];  /* Fourier coefficients B_0(I), B_1(I), ..., B_n(I) */

    double ddA[nfour][ntori];   /* divided differences of Fourier coeffs A_n(I) */
    double ddB[nfour][ntori];   /* divided differences of Fourier coeffs B_n(I) */

    SM_t bSM;           /* Which SM (SM1 or SM2) */

  double I, dI; 
  double Lst;

  int i,j;
  double phip, dphi;

    /* auxiliary vars */
    int iSM;

	if(argc != 2)
    {
		fprintf(stderr, "Num of args incorrect. Usage: %s SM\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    iSM = atoi(argv[1]);
	if(iSM==1) bSM = SM1;
	else bSM = SM2;

    /* Read FT series (divided differences) from file */
    read_FT(nfour,ntori,bSM,ddA,ddB);

  dI = (7.0-0.0)/(NPOINTS_I-1);
  for(i=0; i<NPOINTS_I; i++)
  {
	  I = 0.0+i*dI;

    /* Compute F. coefs A_n(I) for action value I */
    coefs_eval(nfour,ntori,ddA,N,M,I,A);    
    coefs_eval(nfour,ntori,ddB,N,M,I,B);

	  dphi = 2*M_PI/(NPOINTS_PHI-1);
	  for(j=0; j<NPOINTS_PHI; j++)
	  {
		  phip = j*dphi;
		  Lst = widetildeL(N,A,B,phip);
		  printf("%f %f %f\n", I, phip, Lst);
	  }
  }
  return 0;
}
