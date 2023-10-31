/* FT_error_given_I:
   Given an action value I, find the error of the Fourier-Taylor approximation.
   For the moment, we measure only the error in the I component, not in \phi.

   The error will depend mostly on the degree N of the Fourier expansion,
   and degree M of the Taylor expansion. 
   */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>

#define nfour 64 	/* Number of Fourier coeffs used in FFT */
#define ntori 5 	/* Number of tori used in numerical SM */

/* Table containing for all tori, their Fourier coeffs */
double A_all[ntori][nfour];	
double B_all[ntori][nfour];	

void read_Fourier_coefs()
{
	/* auxiliary variables */
	char filename[100];
	double *Ap, *Bp;
	FILE *fp;
	int coeff_num;

	for(int i=0; i<ntori; i++)
	{
		sprintf(filename, "coeffs_%d.res", i+3);
		Ap = A_all[i];
		Bp = B_all[i];

		fp = fopen(filename, "r");
		while(fscanf(fp,"%d %le %le", &coeff_num, Ap, Bp) != EOF) {
			/* advance pointers */
			Ap ++; Bp ++;
		}
		fclose(fp);
	}
}

typedef struct
{
    double *d;
    double *coef;
    double *work;
}
polynomial_state_t;

void A_coefs(double *A, int N, int M, double I)
{
	const int n=ntori;

	/* Compute Fourier coefs A_j(I) for j=0,\dotsc, N 
	 * using Taylor interpolation at I */
	for(int j=0; j<=N; j++)
		{
		  double x[n], y[n];

		   /* input curve */
		  for(int i=0; i<n; i++)
			{
				x[i] = i+2;			/* I */
				y[i] = A_all[i][j];	/* A_j(I) */
			}
		  
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

			/* Interpolate F. coef A_j at I */
			switch(M)
			{
				case 0:
					A[j] = d0;
					break;
				case 1:
					A[j] = d0 + d1*(I-2);
					break;
				case 2: 
					A[j] = d0 + d1*(I-2) + d2*(I-2)*(I-3);
					break;
				case 3:
					A[j] = d0 + d1*(I-2) + d2*(I-2)*(I-3) +
						d3*(I-2)*(I-3)*(I-4);
					break;
				case 4:
					A[j] = d0 + d1*(I-2) + d2*(I-2)*(I-3) +
						d3*(I-2)*(I-3)*(I-4) + 
						d4*(I-2)*(I-3)*(I-4)*(I-5);
					break;
				default:
					break;
			}
			//printf("Fourier coef: %.8f\n", yi);

			//xi = I;
			//yi = gsl_spline_eval (spline, xi, acc);

			gsl_spline_free (spline);
			gsl_interp_accel_free (acc);
		}
}

void B_coefs(double *B, int N, int M, double I)
{
	const int n=ntori;

	/* Compute Fourier coefs B_j(I) for j=0,\dotsc, N 
	 * using Taylor interpolation at I */
	for(int j=0; j<=N; j++)
		{
		  double x[n], y[n];

		   /* input curve */
		  for(int i=0; i<n; i++)
			{
				x[i] = i+2;			/* I */
				y[i] = B_all[i][j];	/* B_j(I) */
			}
		  
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

			/* Interpolate F. coef B_j at I */
			switch(M)
			{
				case 0:
					B[j] = d0;
					break;
				case 1:
					B[j] = d0 + d1*(I-2);
					break;
				case 2: 
					B[j] = d0 + d1*(I-2) + d2*(I-2)*(I-3);
					break;
				case 3:
					B[j] = d0 + d1*(I-2) + d2*(I-2)*(I-3) +
						d3*(I-2)*(I-3)*(I-4);
					break;
				case 4:
					B[j] = d0 + d1*(I-2) + d2*(I-2)*(I-3) +
						d3*(I-2)*(I-3)*(I-4) + 
						d4*(I-2)*(I-3)*(I-4)*(I-5);
					break;
				default:
					break;
			}
			//printf("Fourier coef: %.8f\n", yi);

			//xi = I;
			//yi = gsl_spline_eval (spline, xi, acc);

			gsl_spline_free (spline);
			gsl_interp_accel_free (acc);
		}
}

double dL(double *A, double *B, int N, double phi)
{
	double res = 0.0;
	for(int j=1; j<=N; j++)
	{
		res = res + (A[j]*cos(j*phi) + B[j]*sin(j*phi));
	}
	return res;
}

int
main (int argc, char *argv[])
{

	const int N=1;	/* Degree of Fourier expansion */
	double A[N+1];	/* Fourier coefficients A_0(I), A_1(I), ..., A_N(I) */
	double B[N+1];	/* Fourier coefficients B_0(I), B_1(I), ..., B_n(I) */

	const int M=1;	/* Degree of Taylor expansion */

  double I, phi; 
  double Ip, phip;	/* Numerical values of I', phi' */
  double Ip_approx; /* I' computed using FT approximate model */
  double error, max_error;	/* max approx. error over all points on torus I */

  /* auxiliary vars */
  char filename_dom[100];
  char filename_rng[100];
  FILE *fp_dom;
  FILE *fp_rng;
  double Iaux, t;

  if(argc != 2)
  {
	  fprintf(stderr, "Num of args incorrect. Usage: %s scaled_I\n", argv[0]);
	  exit(EXIT_FAILURE);
  }
  
  I = atof(argv[1]);	/* scaled action level, e.g. I=2 */

  /* First, compute Fourier coefs A_n(I), B_n(I) */

  read_Fourier_coefs();	/* Read table A_all, B_all with F. coefs of all tori */

  A_coefs(A,N,M,I);	/* Compute F. coefs A_n(I) for action value I */
  B_coefs(B,N,M,I);	/* Compute F. coefs B_n(I) for action value I */

  /* For each numerical value of the transition map (I,\phi) -> (I',\phi'), 
	 (1) Read I,\phi,I',\phi'.
	 */

  sprintf(filename_dom, "win_%d_%d_dom_0.res", (int)I+1, (int)I+1);
  sprintf(filename_rng, "win_%d_%d_rng_0.res", (int)I+1, (int)I+1);

  /* (3) Find max approximation error over all points on torus I */
  max_error = 0.0;

	fp_dom = fopen(filename_dom, "r");
	fp_rng = fopen(filename_rng, "r");
	while((fscanf(fp_dom,"%le %le %le", &Iaux, &phi, &t) != EOF) && 
		(fscanf(fp_rng,"%le %le %le", &Ip, &phip, &t) != EOF))	
	{
		Ip_approx = 0.001*I + dL(A, B, N, phip);
		error = fabs(Ip_approx - Ip);
		if(error>max_error) max_error = error;
		/*
		printf("Num. SM: (%f %f) -> %f \t Approx. SM: (%f %f) -> %f\n", 
				Iaux, phip, Ip, 
				Iaux, phip, Ip_approx);
				*/
		printf("%f\n", error);
	}
	fclose(fp_dom);
	fclose(fp_rng);
	printf("Max error for torus %d is: %f\n", (int)I, max_error);

  return 0;
}
