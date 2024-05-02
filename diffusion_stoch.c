/** \file diffusion_stoch.c
  * \brief Starting at the given IC, randomly iterate the IM and SM to drift action.
  *
  * Starting at the given IC, randomly iterate the IM and SM until pseudo-orbit
  * leaves the predefined domain \f$ 1 \leq I \leq 6 \f$.
  *
  * NOTES: 
  *		Fourier-Taylor coeffs for the generating function are read from files
  *		ddA.res and ddB.res, which were generated by FT. 
  *
  *		Taylor coeffs for omega are read from ddOmega.res, which was generated
  *		by T.
  *
  *     Caller must specify which SM to use (SM1 or SM2) as a command-line
  *     argument.
  *
  * USAGE:	./diffusion SM scaledI phi, for example 
  *			./diffusion 1 2.5 3.14
  *
  * CALLED BY:	
  *
  */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>			// fabs
#include <gsl/gsl_rng.h>	// random number generator

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

    const int N = 4;    /* Degree of Fourier series */
    const int M = 6;    /* Degree of Taylor series */

    SM_t bSM;           /* Which SM (SM1 or SM2) */
    double I, phi;      /* (I, \phi) = Point in the domain of the SM */
    double Ip, phip;    /* (I', \phi') = Image of (I, phi) by the SM */

    /* auxiliary vars */
    int iSM;
	double phi_old;
	int bit;		// 0 or 1

    if(argc != 4)
    {
        fprintf(stderr, "Num of args incorrect. Usage: %s SM scaled_I phi\n",
              argv[0]);
        exit(EXIT_FAILURE);
    }

    iSM = atoi(argv[1]);
    if(iSM==1)
        bSM = SM1;
    else
        bSM = SM2;

    I = atof(argv[2]);	    /* scaled action level, e.g. I=2 */
    phi = atof(argv[3]);	/* \phi */

    /* Read FT series (divided differences) from file */
    read_FT(nfour,ntori,bSM,ddA,ddB);

    /* Read Taylor series (divided differences) from file */
    if(bSM==SM1)    read_T(ntori-1,ddOmega_FILE,ddOmega);
    else            read_T(ntori-1,ddOmega_FILE_SM2,ddOmega);

	/* creates an instance of the Tausworthe generator */
	gsl_rng * r = gsl_rng_alloc(gsl_rng_taus);

	printf("%f %f %s\n", I, phi, "IM");
    while(1<I && I<7)
    {
		bit = (int)gsl_rng_get(r) % 2;

		if(bit == 0)
		{
			phi_old = phi;

			/* Compute the IM: (I, phi) -> (Ip, phip) */
			IM(I, phi, &Ip, &phip);
			I = Ip;
			phi = (phip>M_PI ? phip-M_PI : phip);

			if(bSM==SM2)
			{
				/* If angle phi wrapped around \pi, print newline. 
				   This is a trick for correctly plotting line segments in
				   diffusion_SM2.plt.
				 */
				if(phi_old<M_PI/2 && phi>M_PI/2) printf("\n");
			}
			printf("%f %f %s\n", I, phi, "IM");
		}
		else
		{
            /* Compute the SM: (I, phi) -> (Ip, phip) */
            SM(nfour, ntori, ddA, ddB, ddOmega, N, M, I, phi, &Ip, &phip);
            I = Ip;
            phi = (phip>M_PI ? phip-M_PI : phip);
            
            printf("%f %f %s\n", I, phi, "SM");
		}
    }

	gsl_rng_free(r);
    return 0;
}
