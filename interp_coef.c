#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>

typedef struct 
{
	double *d;
	double *coef;
	double *work;
}
polynomial_state_t;

int
main (void)
{
  int i;
  const int n=5;
  double xi, yi, x[n], y[n];

  /* auxiliary variables */
  double *xp, *yp;
  FILE *fp;
  double dx;

   /* Read input curve */
    xp = x; yp = y;
    fp = fopen("B2_scaled.dat", "r");
    while(fscanf(fp,"%le %le", xp, yp) != EOF) {
        /* advance pointers */
        xp ++; yp ++;
    }
    fclose(fp);
  
  {
    gsl_interp_accel *acc
      = gsl_interp_accel_alloc ();
    gsl_spline *spline
      = gsl_spline_alloc (gsl_interp_polynomial, n);

    gsl_spline_init (spline, x, y, n);

	/* Obtain coefficients of interpolating polynomial P(x) */
	const polynomial_state_t *state = (const polynomial_state_t *) (spline ->
			interp -> state);
	double d0, d1, d2, d3, d4;
	d0 = state->d[0];
	d1 = state->d[1];
	d2 = state->d[2];
	d3 = state->d[3];
	d4 = state->d[4];
	fprintf(stderr, "d0: %g, d1: %g, d2: %g, d3: %g, d4: %g\n", 
			d0, d1, d2, d3, d4);

	/* Evaluate interp polynomial P(x) at many points (for plotting P) */
	dx = (x[n-1] - x[0]) / 100;
    for (xi = x[0]; xi < x[n-1]; xi += dx)
      {
        yi = gsl_spline_eval (spline, xi, acc);
        printf ("%g %g\n", xi, yi);
      }
    gsl_spline_free (spline);
    gsl_interp_accel_free (acc);
  }
  return 0;
}
