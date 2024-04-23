/** \file diffusion_triple_greedy.c
  * \brief Starting at the given IC, successively iterate the IM and SM1,SM2 to gain action.
  *
  * We use a greedy strategy to produce the diffusion pseudo-orbit: Iterate the
  * (maximum of both SM's) if it gains action, otherwise iterate the IM.
  *
  * NOTES: 
  *		Fourier-Taylor coeffs for the generating function are read from files
  *		ddA.res and ddB.res, which were generated by FT. 
  *
  *		Taylor coeffs for omega are read from ddOmega.res, which was generated
  *		by T.
  *
  * USAGE:	./diffusion_triple_greedy scaledI phi, for example 
  *			./diffusion_triple_greedy 1 0
  *
  * CALLED BY: diffusion_triple_greedy.sh
  *
  */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>       // fabs
#include "FT_module.h"
#include "T_module.h"
#include "SM_module.h"
#include "IM_module.h"

static const char ddOmega_FILE[] = "ddOmega.res";
static const char ddOmega_FILE_SM2[] = "ddOmega_SM2.res";

int
main (int argc, char *argv[])
{
	const int nfour=65; 	/* Number of Fourier coeffs used in FFT */
	const int ntori=8;		/* Number of tori used in numerical SM */

	double ddA[nfour][ntori];	/* divided differences of Fourier coeffs A_n(I) */
	double ddB[nfour][ntori];	/* divided differences of Fourier coeffs B_n(I) */
    double ddOmega[ntori-1];      /* divided differences of omega(I) */

	double ddA_SM2[nfour][ntori];	/* divided differences of Fourier coeffs A_n(I) */
	double ddB_SM2[nfour][ntori];	/* divided differences of Fourier coeffs B_n(I) */
    double ddOmega_SM2[ntori-1];      /* divided differences of omega(I) */

    const int N = 4;    /* Degree of Fourier series */
    const int M = 6;    /* Degree of Taylor series */

    double I, phi;      /* (I, \phi) = Point in the domain of the SM */
    double Ip, phip;    /* (I', \phi') = Image of (I, phi) by the IM*/
    double Ip1, phip1;    /* (I', \phi') = Image of (I, phi) by the SM1 */
    double Ip2, phip2;    /* (I', \phi') = Image of (I, phi) by the SM2 */

    /* auxiliary vars */
	double phi_old;

    if(argc != 3)
    {
        fprintf(stderr, "Num of args incorrect. Usage: %s scaled_I phi\n",
              argv[0]);
        exit(EXIT_FAILURE);
    }

    I = atof(argv[1]);	    /* scaled action level, e.g. I=2 */
    phi = atof(argv[2]);	/* \phi */

    /* Read FT series (divided differences) from file */
    read_FT(nfour,ntori,SM1,ddA,ddB);
    read_FT(nfour,ntori,SM2,ddA_SM2,ddB_SM2);

    /* Read Taylor series (divided differences) from file */
    read_T(ntori-1,ddOmega_FILE,ddOmega);
    read_T(ntori-1,ddOmega_FILE_SM2,ddOmega_SM2);

	printf("%f %f %s\n", I, phi, "IM");
    while(I<7)
    {
		/* Compute SM1 and SM2 */
		SM(nfour, ntori, ddA, ddB, ddOmega, N, M, I, phi, &Ip1, &phip1);
		SM(nfour, ntori, ddA_SM2, ddB_SM2, ddOmega_SM2, N, M, I, phi, &Ip2, &phip2);

		if(Ip1>=Ip2 && Ip2>I)	/* Accept SM1 iterate */
		{
			I = Ip1;
			phi = (phip1>M_PI ? phip1-M_PI : phip1);
			
			printf("%f %f %s\n", I, phi, "SM1");
		}
		else if(Ip2>Ip1 && Ip1>I)	/* Accept SM2 iterate */
		{
			I = Ip2;
			phi = (phip2>M_PI ? phip2-M_PI : phip2);
			
			printf("%f %f %s\n", I, phi, "SM2");
		}
		else		/* Reject SM iterate. Take IM iterate instead. */
		{
			/* Compute the IM: (I, phi) -> (Ip, phip) */
			IM(I, phi, &Ip, &phip);
			I = Ip;
			phi_old = phi;
			phi = (phip>M_PI ? phip-M_PI : phip);

			/* If angle phi wrapped around \pi, print newline. 
			   This is a trick for correctly plotting line segments in
			   diffusion_SM2.plt.
			 */
			if(phi_old<M_PI/2 && phi>M_PI/2) printf("\n");
				
			printf("%f %f %s\n", I, phi, "IM");
		}
    }
    return 0;
}
