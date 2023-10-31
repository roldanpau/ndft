/** \file T_module.c
  * \brief Functions to compute Taylor series of \f$\omega(I)\f$ and write it to file.
  *
  * NOTES: 
  *		Values of \f$\omega(I=2,3,\dotsc,6)\f$ are read from file
  *		omega_all.res, which was generated by omega_all.sh
  *
  * CALLED BY: Taylor.c, FT_error.c	
  *
  */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>

static const char ddOmega_FILE[] = "ddOmega.res";

void read_omegas(size_t ntori, double omega_all[ntori]) 
{
	/* auxiliary variables */
	const char filename[] = "omega_all.res";
	FILE *fp;
	double I;

    fp = fopen(filename, "r");
	for(int i=0; i<ntori; i++)
	{
		fscanf(fp,"%le %le", &I, &(omega_all[i]));
	}
    fclose(fp);
}

typedef struct
{
    double *d;
    double *coef;
    double *work;
}
polynomial_state_t;

/** 
 * \brief Compute Taylor series, i.e. divided differences of \f$\omega(I)\f$.
 *
 * @param[in]   ntori	Number of tori
 * @param[in]   omega_all	Table containing for each torus I, \f$\omega(I)\f$.
 *
 * @param[out]  dd  Taylor series (div. difs. of omega).
 * 
 */
void compute_T(size_t ntori, double omega_all[ntori], double dd[ntori]) 
{
	const int n=ntori;

    double x[n], y[n];

    /* input curve */
    for(int i=0; i<n; i++)
    {
        x[i] = i+2;			    /* I */
        y[i] = omega_all[i];	/* \omega(I) */
    }
  
    gsl_interp_accel *acc
      = gsl_interp_accel_alloc ();
    gsl_spline *spline
      = gsl_spline_alloc (gsl_interp_polynomial, n);

    gsl_spline_init (spline, x, y, n);

    /* Obtain coefficients of interpolating polynomial P(x) */
    const polynomial_state_t *state = (const polynomial_state_t *) (spline
            -> interp -> state);

    for(int i=0; i<n; i++)
        dd[i] = state->d[i];

    gsl_spline_free (spline);
    gsl_interp_accel_free (acc);
}

/** 
 * \brief Write Taylor series (divided differences) to file.
 *
 * @param[in]   ntori   Degree of the Taylor series = ntori-1.
 * @param[in]   dd      Taylor series (div. difs. of omega).
 */
void write_T(size_t ntori, double dd[ntori])
{
    FILE *fp = fopen(ddOmega_FILE, "w");
    for(int j=0; j<ntori; j++)
    {
        fprintf(fp, "%lf ", dd[j]);
    }
    fprintf(fp, "\n");
    fclose(fp);
}

/** 
 * \brief Read Taylor series (divided differences) from file.
 *
 * @param[in]   ntori   Degree of the Taylor series = ntori-1.
 *
 * @param[out]  dd      Taylor series (div. difs. of omega).
 */
void read_T(size_t ntori, double dd[ntori])
{
    FILE *fp = fopen(ddOmega_FILE, "r");

	int nIt;	// Number of read items
    for(int j=0; j<ntori; j++)
    {
        nIt = fscanf(fp, "%lf ", &(dd[j]));
    }
    nIt = fscanf(fp, "\n");
    fclose(fp);
}

/** 
 * \brief Evaluate omega at I using Taylor interpolation.
 *
 * @param[in]   ntori   Max degree of the Taylor series = ntori-1.
 * @param[in]   dd      Complete Taylor series (div. difs. of omega).
 * @param[in]   M       Degree of the Taylor series.
 * @param[in]   I       Action at which we want to evaluate.
 *
 * @param[out]  omega_p     On exit, it points to the value omega(I).
 */
void omega_eval(size_t ntori, double dd[ntori], size_t M, double I, double
        *omega_p) 
{
    double d0, d1, d2, d3, d4;
    d0 = dd[0];
    d1 = dd[1];
    d2 = dd[2];
    d3 = dd[3];
    d4 = dd[4];

    /* Interpolate omega at I */
    switch(M)
    {
        case 0:
            *omega_p = d0;
            break;
        case 1:
            *omega_p = d0 + d1*(I-2);
            break;
        case 2: 
            *omega_p = d0 + d1*(I-2) + d2*(I-2)*(I-3);
            break;
        case 3:
            *omega_p = d0 + d1*(I-2) + d2*(I-2)*(I-3) +
                d3*(I-2)*(I-3)*(I-4);
            break;
        case 4:
            *omega_p = d0 + d1*(I-2) + d2*(I-2)*(I-3) +
                d3*(I-2)*(I-3)*(I-4) + 
                d4*(I-2)*(I-3)*(I-4)*(I-5);
            break;
        default:
            break;
    }
}

