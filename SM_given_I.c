/* SM_given_I:
   Given an action value I, find the image under the scattering map 
   of the torus T(I).
   */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>

const int NPOINTS = 100;
double A0, A2, B2, A4, B4;	/* Fourier coefficients */

typedef struct
{
    double *d;
    double *coef;
    double *work;
}
polynomial_state_t;

double get_coef(const char *filename, double I)
{
  const int n=5;
  double xi, yi, x[n], y[n];

  /* auxiliary variables */
  double *xp, *yp;
  FILE *fp;

   /* Read input curve */
    xp = x; yp = y;
    fp = fopen(filename, "r");
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

	yi=d0+d1*(I-2)+d2*(I-2)*(I-3);
	//printf("Fourier coef: %.8f\n", yi);

	//xi = I;
	//yi = gsl_spline_eval (spline, xi, acc);

    gsl_spline_free (spline);
    gsl_interp_accel_free (acc);
  }
  return yi;
}

double dL(double phi)
{
	return A2*cos(2*phi) + A4*cos(4*phi) + B2*sin(2*phi) + B4*sin(4*phi);
}

int
main (int argc, char *argv[])
{
  double I, Ip;

  int i;
  double phip, dphi;

  if(argc != 2)
  {
	  fprintf(stderr, "Num of args incorrect. Usage: %s scaled_I\n", argv[0]);
	  exit(EXIT_FAILURE);
  }
  
  I = atof(argv[1]);	/* scaled action level, e.g. I=2 */

  A0 = 0.001*I;
  A2 = get_coef("A2_scaled.dat", I);
  B2 = get_coef("B2_scaled.dat", I);
  A4 = get_coef("A4_scaled.dat", I);
  B4 = get_coef("B4_scaled.dat", I);

  dphi = 2*M_PI/(NPOINTS-1);
  for(i=0; i<NPOINTS; i++)
  {
	  phip = i*dphi;
	  Ip = A0 + dL(phip);
	  printf("%f %f\n", phip, Ip);
  }
  return 0;
}
