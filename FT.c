/** \file FT.c
  * \brief Compute Fourier-Taylor series and write it to file. Given \f$ (I,\phi') \f$, find \f$ pd{L^*}{\phi'} \f$.
  *
  * First and foremost, compute the coefficients of the Fourier-Taylor series,
  * in the form of divided differences ddA and ddB. Write them to file ddA.res
  * and ddB.res. 
  *
  * Given \f$ (I,\phi') \f$, find the value of the Fourier-Taylor series at
  * that point: 
  * \f\[ pd{L^*}{\phi'} = \sum_{n=1}^{N} (B_n(I) \sin{n\phi'} + A_n(I)
  * \cos{n\phi'}). \f\]
  *
  *	The degree (N,M) of the Fourier-Taylor series can be modified in the code.
  *
  * This function is used to approximate the transition map, because
  * \f\[ I'    = I + pd{L^*}{\phi'}. \f\]
  *
  * NOTES: 
  *		Fourier coeffs are read from files coeffs_*.res, which were generated
  *		by fft.sh. 
  *
  *		Do the same for the second scattering map, reading coeffs from files
  *     coeffs_*_SM2.res, and writing coeffs to ddA_SM2.res and ddB_SM2.res.
  *
  *		For now, we use the same degree (N,N) of FT expansion for both SM1 and
  *		SM2.
  *
  * USAGE:	./FT 2 0
  *
  * CALLED BY:	
  *
  */

#include <stdlib.h>
#include <stdio.h>
#include "FT_module.h"

int
main (int argc, char *argv[])
{
	const int nfour=65; 	/* Number of Fourier coeffs used in FFT */
	const int ntori=8;		/* Number of tori used in numerical SM */

	/* Table containing for all tori, their Fourier coeffs */
	double A_all[ntori][nfour];	
	double B_all[ntori][nfour];	

	const int N=10;	/* Degree of Fourier expansion */
	const int M=3;	/* Degree of Taylor expansion */

	double A[N+1];	/* Fourier coefficients A_0(I), A_1(I), ..., A_N(I) */
	double B[N+1];	/* Fourier coefficients B_0(I), B_1(I), ..., B_n(I) */

	double Ap[N+1];	/* Derivative of Fourier coefficients A_0(I), A_1(I), ..., A_N(I) */
	double Bp[N+1];	/* Derivative of Fourier coefficients B_0(I), B_1(I), ..., B_n(I) */

	double ddA[nfour][ntori];	/* divided differences of Fourier coeffs A_n(I) */
	double ddB[nfour][ntori];	/* divided differences of Fourier coeffs B_n(I) */

    double I, phip;

    if(argc != 3)
    {
        fprintf(stderr, "Num of args incorrect. Usage: %s scaled_I phip\n",
              argv[0]);
        exit(EXIT_FAILURE);
    }

    I = atof(argv[1]);	/* scaled action level, e.g. I=2 */
    phip = atof(argv[2]);	/* \phi' */


	/*** Compute coefs of FT series for SM1 ***/

    /* Read table A_all, B_all with F. coefs of all tori */
    read_Fourier_coefs(ntori, nfour, SM1, A_all, B_all);

    /* Compute FT series (divided differences) */
    compute_FT(ntori,nfour,A_all,ddA);	
    compute_FT(ntori,nfour,B_all,ddB);

    /* Write FT series (divided differences) to file */
    write_FT(nfour,ntori,SM1,ddA,ddB);


	/*** Compute coefs of FT series for SM2 ***/

    /* Read table A_all, B_all with F. coefs of all tori */
    read_Fourier_coefs(ntori, nfour, SM2, A_all, B_all);

    /* Compute FT series (divided differences) */
    compute_FT(ntori,nfour,A_all,ddA);	
    compute_FT(ntori,nfour,B_all,ddB);

    /* Write FT series (divided differences) to file */
    write_FT(nfour,ntori,SM2,ddA,ddB);


	/*** Evaluate FT series of SM1 at (I, phip) ***/

    /* Read FT series (divided differences) from file */
    read_FT(nfour,ntori,SM1,ddA,ddB);

	/* Find the image I' of (I,phi) by the transition map. */
    coefs_eval(nfour,ntori,ddA,N,M,I,A);	/* Compute F. coefs A_n(I) for action value I */
    coefs_eval(nfour,ntori,ddB,N,M,I,B);	/* Compute F. coefs B_n(I) for action value I */

    printf("%f %f %f\n", I, phip, I + dL_dphi(N, A, B, phip));

	/* Find dL_dphi(I,phi'). */
    dcoefs_eval(nfour,ntori,ddA,N,M,I,Ap);	/* Compute F. coefs A_n(I) for action value I */
    dcoefs_eval(nfour,ntori,ddB,N,M,I,Bp);	/* Compute F. coefs B_n(I) for action value I */

    printf("%f %f %f\n", I, phip, dL_dI(N, Ap, Bp, phip));
	
    return 0;
}
