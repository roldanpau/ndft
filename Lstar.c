/** \file Lstar.c
  * \brief Evaluate the function \f$ L^*(I,\phi') \f$ on a grid of \f$ (I,
  * \phi') \f$ points.
  *
  * USAGE:	./Lstar > Lstar.res
  *
  */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>

const int NPOINTS_I = 101;		/* num of points in the I direction */
const int NPOINTS_PHI = 101;	/* num of points in the \phi' direction */
double A2, B2, A4, B4;	/* Fourier coefficients */

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

double Lstar(double phi)
{
	return A2/2*sin(2*phi) + A4/4*sin(4*phi) - B2/2*cos(2*phi) - B4/4*cos(4*phi);
}

int
main (int argc, char *argv[])
{
  double I, dI; 
  double Lst;

  int i,j;
  double phip, dphi;

  dI = (6.0-2.0)/(NPOINTS_I-1);
  for(i=0; i<NPOINTS_I; i++)
  {
	  I = 2.0+i*dI;
	  A2 = get_coef("A2_scaled.dat", I);
	  B2 = get_coef("B2_scaled.dat", I);
	  A4 = get_coef("A4_scaled.dat", I);
	  B4 = get_coef("B4_scaled.dat", I);

	  dphi = 2*M_PI/(NPOINTS_PHI-1);
	  for(j=0; j<NPOINTS_PHI; j++)
	  {
		  phip = j*dphi;
		  Lst = Lstar(phip);
		  printf("%f %f %f\n", I, phip, Lst);
	  }
  }
  return 0;
}
