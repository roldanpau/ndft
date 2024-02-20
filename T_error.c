/** \file T_error.c
  * \brief Find the error of the Taylor approximation.
  *
  * Find the error of the Taylor approximation over the domain \f$
  * I\in[I_\min, I_\max] \f$. The local domain is chosen to be [0,3], while
  * the global domain is chosen [0,7].
  *
  * The error depends on the degree N of the Fourier expansion, and degree M of
  * the Taylor expansion. Thus for each pair (M,N) we compute the error, and
  * print it to stdout.
  *
  * NOTES: 
  *		We measure only the error in the \f$ \phi \f$ component, not in
  *		I. The error in \f$ I \f$ is measured in FT_error.c
  *
  * USAGE:	./T_error Imax > T_error.res
  *
  * CALLED BY:	
  *
  */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>		// fabs
#include "FT_module.h"
#include "T_module.h"
#include "SM_module.h"

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

int
main (int argc, char *argv[])
{
	const int nfour=65; 	/* Number of Fourier coeffs used in FFT */
	const int ntori=8;		/* Number of tori used in numerical SM */

    /* For local SM, the max error is computed up to torus Imax only */
    int Imax;               

    /* divided differences of Fourier coeffs A_n(I) */
	double ddA[nfour][ntori];	

    /* divided differences of Fourier coeffs B_n(I) */
	double ddB[nfour][ntori];	
	double ddOmega[ntori-1];	        /* divided differences of omega(I) */

    double I, phi;      /* (I, \phi) = Point in the domain of the SM */

    /* (I', \phi') = Image of (I, phi) by the NUMERICAL SM */
    double Ip, phip;    

    /* (\tilde I', \tilde \phi') = Image of (I, phi) by the SM SERIES */
    double tIp, tphip;

	double error; 
	double max_error_tor;	/* max approx. error over all points on torus I */
	double max_error;

	/* auxiliary vars */
	char filename_dom[100];
	char filename_rng[100];
	FILE *fp_dom;
	FILE *fp_rng;
	double Itor, t;

	if(argc != 2)
	{
		fprintf(stderr, "Num of args incorrect. Usage: %s Imax\n", argv[0]);
		exit(EXIT_FAILURE);
	}
    Imax = atoi(argv[1]);
  
    /* Read FT series (divided differences) from file */
    read_FT(nfour,ntori,ddA,ddB);

    /* Read Taylor series (divided differences) from file */
    read_T(ntori-1,ddOmega);

	for(int N=2; N<nfour; N+=2)	/* N = Degree of Fourier expansion */
    {
        /* M = Degree of Taylor expansion */
        for(int M=0; M<min(ntori-1, Imax); M++)	
        {
            max_error = 0.0;
			/* We skip torus I=0, since error is 0 for that one */
            for(Itor=1; Itor<=Imax; Itor++)
            {
                sprintf(filename_dom, "curve1_%d_%d_dom_0.res", (int)Itor+1,
                        (int)Itor+1);
                sprintf(filename_rng, "curve1_%d_%d_rng_0.res", (int)Itor+1,
                        (int)Itor+1);

                fp_dom = fopen(filename_dom, "r");
                fp_rng = fopen(filename_rng, "r");

                max_error_tor = 0.0;

                /* For each numerical value of the transition map (I,\phi) ->
                 * (I',\phi'), 
                 */
                /* (1) Read I,\phi,I',\phi'. */
                while((fscanf(fp_dom,"%le %le %le", &I, &phi, &t) != EOF) && 
                        (fscanf(fp_rng,"%le %le %le", &Ip, &phip, &t) != EOF))	
                {
                    /* Scale I (I's are not scaled in curve1_%d_%d_dom_0.res) */
                    I = I*1000;
                    Ip = Ip*1000;
                
                    /* (2) Compute approximate SM using FT model. */
                    SM(nfour, ntori, ddA, ddB, ddOmega, N, M, I, phi, &tIp,
                            &tphip);

                    /* (3) Find max approximation error over all points on
                     * torus I */
					error = constrainAngle(tphip - phip);
					error = (error<M_PI ? error : 2*M_PI - error);
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
                fprintf(stderr, "Max error for torus %d is: %f\n", (int)Itor, max_error_tor);
                if(max_error_tor>max_error) max_error = max_error_tor;
            }
            printf("%d %d %f\n", N, M, max_error);
        }
		printf("\n");
	}
	return 0;
}
