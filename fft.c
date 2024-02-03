/** \file fft.c
  * \brief Compute Fourier coefficients of \f$\mathcal{L}'\f$ (REAL Fourier series)
  *
  * Read a curve from file, compute its Fourier coeffs \f$A_n, B_n\f$, and
  * print them to stdout.
  *
  * NOTES: 
  *		We assume that the number of points in curve is 128 (this comes from
  *		lin_interp.c). Thus, the number of real Fourier coeffs is 64.
  *	
  *		The norms of the coeffs are also printed (to stderr).
  *
  * USAGE:	./fft curve_interp > coeffs.res 2> fft.res
  *
  * CALLED BY:	fft.sh
  *
  */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_real.h>

int
main (int argc, char *argv[])
{
	FILE *fp;
	const int n = 128;

	double x[n], y[n];	// input data

	/* auxiliary variables */
	double *xp, *yp;
	int i;

	/* Read filename with interpolated curve */
	char *filename;

	if (argc != 2) {
		printf("Usage: %s datafile\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	filename = argv[1];

	/* Read input curve */
    xp = x; yp = y;
    fp = fopen(filename, "r");
    while(fscanf(fp,"%le %le", xp, yp) != EOF) {
        /* advance pointers */
        xp ++; yp ++;
    }
	fclose(fp);

	/* Compute the frequency coefficients of the real sequence y */
	/* For k < n/2, the real part of the k-th term is stored in location k, 
	   and the corresponding imaginary part is stored in location n-k.
	   The terms for k=0 and k=n/2 are both purely real, and are stored 
	   in locations 0 and n/2. */
  gsl_fft_real_radix2_transform(y, 1, n);	// stride == 1
 
    /* Write coefficients to stdout
  for (i = 0; i < n; i++)
    {
	    fprintf (stdout, "%e\n", y[i]);
    } */

 for (i = 0; i <= n/2; i++)
    {
		double re;
		double im;

		// Fourier coefficients of $\mathcal{L}'$, expressed in Amadeu's
		// notation (REAL Fourier series).
		double An, Bn;	

		/* FFT storage Convention for first and last coefs is special */
		if(i == 0 || i == n/2) 
		{
			re = y[i];
			im = 0;
		}
		else
		{
			re = y[i];
			im = y[n-i];
		}

		/* Write coefficients (for REAL Fourier series, in Amadeu's notation) 
		   to stdout */
		if(i == 0 || i == n/2) 
		{
			An = re/n;	// A0
			Bn = 0.0;	// B0
			fprintf (stdout, "%d %e %e\n", i, An, Bn);
		}
		else
		{
			An = 2*re/n;
			Bn = -2*im/n;
			fprintf (stdout, "%d %e %e\n", i, An, Bn);
		}

		/* Write norm to stderr */
	    fprintf (stderr, "%d %e %e\n", i, fabs(An), fabs(Bn));
    }

  return 0;
}

