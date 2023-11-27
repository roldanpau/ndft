/** \file IM.c
  * \brief Compute the inner map \f$ (I', \phi') = \tau(I,\phi) \f$.
  *
  * NOTES: 
  * The inner map is approximated using linear interpolation on 
  * \f$I\in(2,6)\f$.
  *
  * USAGE:	./IM 2 0
  *
  */

#include <stdlib.h>
#include <stdio.h>
#include "IM_module.h"

int
main (int argc, char *argv[])
{
    double I, phi;      /* (I, \phi) = Point in the domain of the IM */
    double Ip, phip;    /* (I', \phi') = Image of (I, phi) by the IM */

    if(argc != 3)
    {
        fprintf(stderr, "Num of args incorrect. Usage: %s scaled_I phi\n",
              argv[0]);
        exit(EXIT_FAILURE);
    }

    I = atof(argv[1]);	    /* scaled action level, e.g. I=2 */
    phi = atof(argv[2]);	/* \phi */

	/* Compute the SM: (I, phi) -> (Ip, phip) */
	IM(I, phi, &Ip, &phip);
	
    printf("%f %f\n", Ip, phip);
    return 0;
}
