/** \file FT_error.c
  * \brief Find the error of the Fourier-Taylor approximation.
  *
  * Find the error of the Fourier-Taylor approximation.
  * The error depends on the degree N of the Fourier expansion, and degree M of
  * the Taylor expansion. Thus for each pair (M,N) we compute the error, and
  * print it to stdout.
  *
  * NOTES: 
  *		For the moment, we measure only the error in the I component, not in
  *		\phi.
  *
  * USAGE:	./FT_error > FT_error.res
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

	int I;
	double phi; 
	double Ip, phip;	/* Numerical values of I', phi' */
	double Ip_approx; /* I' computed using FT approximate model */
	double error; 
	double max_error_tor;	/* max approx. error over all points on torus I */
	double max_error;

	/* auxiliary vars */
	char filename_dom[100];
	char filename_rng[100];
	FILE *fp_dom;
	FILE *fp_rng;
	double Iaux, t;

	if(argc != 1)
	{
		fprintf(stderr, "Num of args incorrect. Usage: %s\n", argv[0]);
		exit(EXIT_FAILURE);
	}
  
    /* Read FT series (divided differences) from file */
    read_FT(nfour,ntori,ddA,ddB);

	for(int N=2; N<nfour; N+=2)	/* N = Degree of Fourier expansion */
    {
		for(int M=0; M<ntori; M++)	/* M = Degree of Taylor expansion */
		{
			double A[N+1];	/* Fourier coefficients A_0(I), A_1(I), ..., A_N(I) */
			double B[N+1];	/* Fourier coefficients B_0(I), B_1(I), ..., B_N(I) */

			max_error = 0.0;
			for(I=1; I<8; I++)
			{
				/* Compute F. coefs A_n(I), B_n(I) for action value I */
				coefs_eval(nfour,ntori,ddA,N,M,I,A);
				coefs_eval(nfour,ntori,ddB,N,M,I,B);

				sprintf(filename_dom, "curve1_%d_%d_dom_0.res", (int)I+1, (int)I+1);
				sprintf(filename_rng, "curve1_%d_%d_rng_0.res", (int)I+1, (int)I+1);

				fp_dom = fopen(filename_dom, "r");
				fp_rng = fopen(filename_rng, "r");

				max_error_tor = 0.0;

				/* For each numerical value of the transition map (I,\phi) ->
				 * (I',\phi'), 
				 */
				while((fscanf(fp_dom,"%le %le %le", &Iaux, &phi, &t) != EOF) && 
						(fscanf(fp_rng,"%le %le %le", &Ip, &phip, &t) != EOF))	
				{
					/* Scale I (I's are not scaled in curve1_%d_%d_dom_0.res) */
					Iaux = Iaux*1000;
					Ip = Ip*1000;
				
					/* (1) Read I,\phi,I',\phi'. */
					/* (2) Compute approximate SM using FT model. */
					Ip_approx = I + dL_dphi(N, A, B, phip);

					/* (3) Find max approximation error over all points on torus I */
					error = fabs(Ip_approx - Ip);
					if(error>max_error_tor) max_error_tor = error;
					/*
					printf("Num. SM: (%f %f) -> %f \t Approx. SM: (%f %f) -> %f\n", 
							Iaux, phip, Ip, 
							Iaux, phip, Ip_approx);
							*/
					//printf("%f\n", error);
				}
				fclose(fp_dom);
				fclose(fp_rng);
				fprintf(stderr, "Max error for torus %d is: %f\n", (int)I, max_error_tor);
				if(max_error_tor>max_error) max_error = max_error_tor;
			}
			printf("%d %d %f\n", N, M, max_error);
		}
		printf("\n");
	}
	return 0;
}
