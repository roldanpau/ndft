/** \file phase_port_SM.c
  * \brief Plot the phase portrait of the (damped) scattering map.
  *
  * Take a bunch of initial conditions in the NHIM of the form (\f$ \phi=0,
  * I\in[2,4] \f$) and iterate them by the SM many times (say, 1000
  * iterations). The goal is to see if we can identify invariant tori, chaotic
  * zones, stable islands, etc.
  *
  * For each orbit \f[ (I_1, \phi_1) \to (I_2, \phi_2) \to \cdots \to (I_n,
  * \phi_n) \f] 
  * we output the whole orbit itself, to be displayed as dots.
  *
  * NOTES: 
  *
  * USAGE:	./phase_port_SM 100 1000 0.1 > phase_port_SM.res
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

	int norb;	/* Number of orbits */
	int nit;	/* Number of iterations of the SM */
	double a;	/* Perturbation parameter (size of non-integrable part) */

	double ddA[nfour][ntori];	/* divided differences of Fourier coeffs A_n(I) */
	double ddB[nfour][ntori];	/* divided differences of Fourier coeffs B_n(I) */
    double ddOmega[ntori];      /* divided differences of omega(I) */

    double I, phi;      /* (I, \phi) = Point in the domain of the SM */
    double Ip, phip;    /* (I', \phi') = Image of (I, phi) by the SM */

    if(argc != 4)
    {
		fprintf(stderr, 
				"Num of args incorrect. Usage: %s norbits niterations a\n",
				argv[0]);
        exit(EXIT_FAILURE);
    }
	norb = atoi(argv[1]);
	nit = atoi(argv[2]);
	a = atof(argv[3]);

    /* Read FT series (divided differences) from file */
    read_FT(nfour,ntori,ddA,ddB);

    /* Read Taylor series (divided differences) from file */
    read_T(ntori,ddOmega);

	/* Iterate over all orbits */
	for(int i=0; i<= norb; i++)
	{
//		for(int j=0; j<= norb; j++)
//		{
			/* Initialize initial condition */
			I = 2.0+i*4.0/norb;				// Start in the middle of the NHIM
//			phi = j*2*M_PI/norb;
			phi=0;

			/* Iterate the SM a few times */
			for(int it=0; it<nit; it++)
			{
				damped_SM(nfour, ntori, ddA, ddB, ddOmega, I, phi, &Ip, &phip, a);
				I = Ip;
				phi = phip;

				/* Output iterate */
				printf("%f %f\n", Ip, phip);
			}
//		}
	}
    return 0;
}
