#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_complex.h>

#define REAL(z,i) ((z)[2*(i)])
#define IMAG(z,i) ((z)[2*(i)+1])

int
main (void)
{
	FILE *fp;
	const int n = 256;

	double x[n], y[n];	// input data

	/* auxiliary variables */
	double *xp, *yp;

	/* Read input curve */
    xp = x; yp = y;
    fp = fopen("curve_interp", "r");
    while(fscanf(fp,"%le %le", xp, yp) != EOF) {
        /* advance pointers */
        xp ++; yp ++;
    }

  int i; double data[2*n];

  for (i = 0; i < n; i++)
    {
       REAL(data,i) = y[i]; IMAG(data,i) = 0.0;
    }

  /*
  for (i = 0; i < n; i++)
    {
      printf ("%d %e %e\n", i,
              REAL(data,i), IMAG(data,i));
    }
  printf ("\n\n");
	*/

  gsl_fft_complex_radix2_forward (data, 1, n);	// stride == 1

  for (i = 0; i < n; i++)
    {
		double re = REAL(data,i)/sqrt(n);
		double im = IMAG(data,i)/sqrt(n);

	  printf ("%d %e %e %e\n", i, re, im, sqrt(re*re+im*im));
    }

  return 0;
}

