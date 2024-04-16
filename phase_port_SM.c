/** \file phase_port_SM.c
  * \brief Plot the phase portrait of the (damped) scattering map.
  *
  * Take a bunch of initial conditions in the NHIM of the form (\f$ \phi=0,
  * I\in[Imin,Imax] \f$) and iterate them by the SM many times (say, 1000
  * iterations). The goal is to see if we can identify invariant tori, chaotic
  * zones, stable islands, etc.
  *
  * For each orbit 
  * \f[ (I_1, \phi_1) \to (I_2, \phi_2) \to \cdots \to (I_n, \phi_n) \f] 
  * we output the whole orbit itself, to be plotted as dots.
  *
  * NOTES: 
  *     Caller must specify which SM to use (SM1 or SM2) as a command-line
  *     argument.
  *
  * USAGE:	./phase_port_SM 1 Imin Imax 100 1000 0.1 > phase_port_SM.res
  *
  * CALLED_BY: phase_port_SM.sh
  */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>		// M_PI
#include "FT_module.h"
#include "T_module.h"
#include "SM_module.h"

static const char ddOmega_FILE[] = "ddOmega.res";
static const char ddOmega_FILE_SM2[] = "ddOmega_SM2.res";

int
main (int argc, char *argv[])
{
	const int nfour=65; 	/* Number of Fourier coeffs used in FFT */
	const int ntori=8;		/* Number of tori used in numerical SM */

	int norb;	/* Number of orbits */
	int nit;	/* Number of iterations of the SM */
	double a;	/* Perturbation parameter (size of non-integrable part) */

	double ddA[nfour][ntori];	/* divided differences of Fourier coeffs A_n(I) */
	double ddB[nfour][ntori];	/* divided differences of Fourier coeffs B_n(I) */
    double ddOmega[ntori-1];      /* divided differences of omega(I) */

    const int N = 4;    /* Degree of Fourier series */
    const int M = 5;    /* Degree of Taylor series */

    SM_t bSM;			/* Which SM (SM1 or SM2) */
    double I, phi;      /* (I, \phi) = Point in the domain of the SM */
    double Ip, phip;    /* (I', \phi') = Image of (I, phi) by the SM */

    double Imin, Imax;

    /* auxiliary vars */
    int iSM;

    if(argc != 7)
    {
		fprintf(stderr, 
                "Num of args incorrect. \
               Usage: %s SM Imin Imax norbits niterations a\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    iSM = atoi(argv[1]);
    if(iSM==1)
        bSM = SM1;
    else
        bSM = SM2;

    Imin = atof(argv[2]);
    Imax = atof(argv[3]);
	norb = atoi(argv[4]);
	nit = atoi(argv[5]);
	a = atof(argv[6]);

    /* Read FT series (divided differences) from file */
    read_FT(nfour,ntori,bSM,ddA,ddB);

    /* Read Taylor series (divided differences) from file */
    if(bSM==SM1)    read_T(ntori-1,ddOmega_FILE,ddOmega);
    else            read_T(ntori-1,ddOmega_FILE_SM2,ddOmega);

	/* Iterate over all orbits */
	for(int i=0; i<= norb; i++)
	{
//		for(int j=0; j<= norb; j++)
//		{
			/* Initialize initial condition */
			I = Imin+i*(Imax-Imin)/norb;
//			phi = j*2*M_PI/norb;
			phi=0;

			/* Iterate the SM nit times */
			for(int it=0; it<nit; it++)
			{
				damped_SM(nfour, ntori, ddA, ddB, ddOmega, N, M, I, phi, &Ip, &phip, a);
				I = Ip;
				phi = phip;

				/* Output iterate */
				printf("%f %f\n", Ip, phip);
			}
//		}
	}
    return 0;
}
