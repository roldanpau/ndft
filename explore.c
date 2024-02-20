/** \file explore.c
  * \brief Explore how far can pseudo-orbits travel in the action variable.
  *
  * Take a bunch of initial conditions on the torus \f$ I=I_0 \f$ of the NHIM
  * and iterate them by the SM several times (say, 512 iterations). The goal
  * is to see how far in the action variable \f$ I \f$ they travel.
  *
  * For each pseudo-orbit 
  * \f[ (I_1, \phi_1) \to (I_2, \phi_2) \to \cdots \to (I_n, \phi_n) \f] 
  * we output the final action value \f$ I_n \f$.
  *
  * NOTES: 
  *
  * USAGE:	./explore I_0 norbits niterations
  *
  */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>		// M_PI
#include "FT_module.h"
#include "T_module.h"
#include "SM_module.h"


int
main (int argc, char *argv[])
{
	const int nfour=64; 	/* Number of Fourier coeffs used in FFT */
	const int ntori=5;		/* Number of tori used in numerical SM */

	double I0;		/* Initial conditions are all on torus I=I0 */
	int norb;		/* Number of orbits */
	int nit;		/* Number of iterations of the SM */

	double ddA[nfour][ntori];	/* divided differences of Fourier coeffs A_n(I) */
	double ddB[nfour][ntori];	/* divided differences of Fourier coeffs B_n(I) */
    double ddOmega[ntori];      /* divided differences of omega(I) */

    const int N = 4;    /* Degree of Fourier series */
    const int M = 5;    /* Degree of Taylor series */

    double I, phi;      /* (I, \phi) = Point in the domain of the SM */
    double Ip, phip;    /* (I', \phi') = Image of (I, phi) by the SM */

    if(argc != 4)
    {
		fprintf(stderr, 
				"Num of args incorrect. Usage: %s I_0 norbits niterations\n",
				argv[0]);
        exit(EXIT_FAILURE);
    }
	I0 = atof(argv[1]);
	norb = atoi(argv[2]);
	nit = atoi(argv[3]);

	/* Array of final conditions (I_n, phi_n) */
	double I_all[norb];
	double phi_all[norb];	

    /* Read FT series (divided differences) from file */
    read_FT(nfour,ntori,ddA,ddB);

    /* Read Taylor series (divided differences) from file */
    read_T(ntori,ddOmega);

	/* Iterate over all orbits */
	for(int i=0; i<= norb; i++)
	{
		/* Initialize initial condition */
		I = I0;				// Start in the middle of the NHIM
		phi = i*2*M_PI/norb;

		/* Iterate the SM a few times */
		for(int it=0; it<nit; it++)
		{
			SM(nfour, ntori, ddA, ddB, ddOmega, N, M, I, phi, &Ip, &phip);
			I = Ip;
			phi = phip;
		}
		
		/* Record final condition */
		I_all[i] = Ip;
		phi_all[i] = phip;
		
		/* Output final condition */
		printf("%f %f\n", Ip, phip);
	}
    return 0;
}
