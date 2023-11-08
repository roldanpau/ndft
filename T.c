/** \file T.c
  * \brief Compute Taylor series of \f$\omega(I)\f$ and write it to file.
  *
  * First and foremost, compute the coefficients of the Taylor series, in the
  * form of divided differences dd. Write them to file ddOmega.res.
  *
  * Given \f$ I \f$, find the value of the Taylor series at that point: 
  * \f\[ \omega(I)  = \sum_{l=0}^{L} c_l I^l. \f\]
  *
  *	The degree L of the Taylor series can be modified in the code.
  *
  * This function is used to approximate the transition map, because
  * \f\[ \phi'    = \phi - \omega(I) - d{\widetilde{L}}/d{I}. \f\]
  *
  * NOTES: 
  *		Omega values are read from file omega_all.res, which were generated by
  *		omega_all.sh
  *
  * USAGE:	./T 2
  *
  * CALLED BY:	
  *
  */

#include <stdlib.h>
#include <stdio.h>
#include "T_module.h"

int
main (int argc, char *argv[])
{
	const int ntori=5;		/* Number of tori used in numerical SM */

	/* Table containing for all tori, their omega values */
	double omega_all[ntori];	

	const int M=2;	/* Degree of Taylor expansion */

	double omega;	/* Interpolated omega value at I */

	double dd[ntori];	/* divided differences of omega(I) */

    double I;

    if(argc != 2)
    {
        fprintf(stderr, "Num of args incorrect. Usage: %s scaled_I\n",
              argv[0]);
        exit(EXIT_FAILURE);
    }

    I = atof(argv[1]);	/* scaled action level, e.g. I=2 */

    /* Read table omega_all, with omega values of all tori */
    read_omegas(ntori, omega_all);

    /* Compute Taylor series (divided differences) */
    compute_T(ntori,omega_all,dd);	

    /* Write Taylor series (divided differences) to file */
    write_T(ntori,dd);

    /* Read Taylor series (divided differences) from file */
    read_T(ntori,dd);

    /* Compute omega(I) for action value I */
    omega_eval(ntori,dd,M,I,&omega);	

    printf("%f %f\n", I, omega);
    return 0;
}
