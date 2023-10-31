/** \file spline_interp.c
  * \brief Interpolate curve using splines on an equispaced set of nodes.
  *
  * Read a curve from file, interpolate it using splines on an equispaced set
  * of nodes, and print interpolated curve to stdout.
  *
  * NOTES: 
  *		No need to specify the number of points in datafile (the prog figures
  *		it out).
  *		
  * USAGE:	./lin_interp curve > curve_interp
  *
  * CALLED BY:	fft.sh
  */


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>

const int nNodes=128;	//!< Number of nodes where to eval interp func

int countlines(char *filename)
{
  FILE *fp;
  int ch=0;
  int lines=0;

	fp = fopen(filename, "r");
	if (fp == NULL) return 0;
	
	while(!feof(fp))
	{
	  ch = fgetc(fp);
	  if(ch == '\n')
	  {
		lines++;
	  }
	}

	fclose(fp);
	return lines;
}

int
main (int argc, char *argv[])
{
	FILE *fp;
	char *filename;

	if (argc != 2) {
		printf("Usage: %s datafile\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	filename = argv[1];

	/* Find number of points in datafile */
	const int n = countlines(filename);

	double *xp, *yp;
	double xi, yi;

	double x[n], y[n];
	double dx;
	int i;

	/* Read input curve */
	xp = x; yp = y;
	fp = fopen(filename, "r");
	if (fp == NULL) return 0;
	while(fscanf(fp,"%le %le", xp, yp) != EOF) {
		/* advance pointers */
		xp ++; yp ++;
	}
	fclose(fp);

	/* Interpolate curve using splines on an equispaced set of nodes */
  {
    gsl_interp_accel *acc
      = gsl_interp_accel_alloc ();
    gsl_spline *spline
      = gsl_spline_alloc (gsl_interp_cspline, n);

    gsl_spline_init (spline, x, y, n);

//    for (xi = x[0]; xi < x[n-1]; xi += 0.01)

	dx = (x[n-1]-x[0])/nNodes;
      for (i=0; i<nNodes; i++)
      {
		  xi = x[0] + i*dx;
        yi = gsl_spline_eval (spline, xi, acc);
        printf ("%g %g\n", xi, yi);
      }
    gsl_spline_free (spline);
    gsl_interp_accel_free (acc);
  }
  return 0;
}
