/** \file omega.c
  * \brief Given an action \f$ I \f$, find the shift of the transition map
  *
  * Let an action \f$ I \f$ be fixed. Read a set of points mapped by the
  * transition map: \f$ (I,\phi) \to (I', \phi') \f$. For each point, find the
  * shift of the transition map,
  * \f\[ \omega(I) = \phi-\phi'-d{\widetilde{L}}/d{I}. \f\]
  * Finally, average \f$ \omega(I) \f$ over all angles, and print result to
  * stdout.
  *
  * NOTES: 
  *		In principle, \f$ \omega(I) \f$ should be constant w.r.t. \f$ \phi \f$.
  *
  * USAGE:	./omega 2 > omega.res
  *
  * CALLED BY: omega_all.sh	
  *
  */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>	// M_PI

#include "FT_module.h"

int
main (int argc, char *argv[])
{
	const int nfour=65; 	/* Number of Fourier coeffs used in FFT */
	const int ntori=8;		/* Number of tori used in numerical SM */

	double ddA[nfour][ntori];	/* divided differences of Fourier coeffs A_n(I) */
	double ddB[nfour][ntori];	/* divided differences of Fourier coeffs B_n(I) */

	const int N=6;	/* Degree of Fourier expansion */
	const int M=4;	/* Degree of Taylor expansion */

	double Ap[N+1];	/* Derivative of Fourier coefficients A_0(I), A_1(I), ..., A_N(I) */
	double Bp[N+1];	/* Derivative of Fourier coefficients B_0(I), B_1(I), ..., B_n(I) */

	double I, phi;
	double Ip, phip;	/* Numerical values of I', phi' */

	/* auxiliary vars */
	char filename_dom[100];
	char filename_rng[100];
	FILE *fp_dom;
	FILE *fp_rng;
	double Iaux, t;

	double omega;
	double omega_sum = 0;	// Sum of all omegas 
	int num_omegas = 0;			// Number of omegas

	if(argc != 2)
	{
		fprintf(stderr, "Num of args incorrect. Usage: %s scaled_I\n", argv[0]);
		exit(EXIT_FAILURE);
	}
  
	I = atof(argv[1]);	/* scaled action level, e.g. I=2 */

    /* Read FT series (divided differences) from file */
    read_FT(nfour,ntori,ddA,ddB);

    dcoefs_eval(nfour,ntori,ddA,N,M,I,Ap);	/* Compute F. coefs A_n(I) for action value I */
    dcoefs_eval(nfour,ntori,ddB,N,M,I,Bp);	/* Compute F. coefs B_n(I) for action value I */

	sprintf(filename_dom, "curve1_%d_%d_dom_0.res", (int)I+1, (int)I+1);
	sprintf(filename_rng, "curve1_%d_%d_rng_0.res", (int)I+1, (int)I+1);

	fp_dom = fopen(filename_dom, "r");
	fp_rng = fopen(filename_rng, "r");

	/* For each numerical value of the transition map (I,\phi) ->
	 * (I',\phi'), 
	 */
	while((fscanf(fp_dom,"%le %le %le", &Iaux, &phi, &t) != EOF) && 
			(fscanf(fp_rng,"%le %le %le", &Ip, &phip, &t) != EOF))	
	{
		omega = phi - phip - dL_dI(N, Ap, Bp, phip);
		if (omega<0) omega += 2*M_PI;
		printf("%f %f %f\n", I, phip, omega);
		omega_sum += omega;
		num_omegas ++;
	}
	fclose(fp_dom);
	fclose(fp_rng);

	fprintf(stderr, "%f %f\n", I, omega_sum / num_omegas);
	return 0;
}
