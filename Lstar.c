/** \file Lstar.c
  * \brief Evaluate the function \f$ L^*(I,\phi') \f$ on a grid of \f$ (I,
  * \phi') \f$ points.
  *
  * USAGE:	./Lstar > Lstar.res
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
    const int nfour=64;     /* Number of Fourier coeffs used in FFT */
    const int ntori=5;      /* Number of tori used in numerical SM */

    const int N=2; /* Degree of Fourier expansion */
    const int M=2;  /* Degree of Taylor expansion */

    double A[N+1];  /* Fourier coefficients A_0(I), A_1(I), ..., A_N(I) */
    double B[N+1];  /* Fourier coefficients B_0(I), B_1(I), ..., B_n(I) */

    double ddA[nfour][ntori];   /* divided differences of Fourier coeffs A_n(I) */
    double ddB[nfour][ntori];   /* divided differences of Fourier coeffs B_n(I) */

  double I, dI; 
  double Lst;

  int i,j;
  double phip, dphi;

    /* Read FT series (divided differences) from file */
    read_FT(nfour,ntori,ddA,ddB);

  dI = (6.0-2.0)/(NPOINTS_I-1);
  for(i=0; i<NPOINTS_I; i++)
  {
	  I = 2.0+i*dI;

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
