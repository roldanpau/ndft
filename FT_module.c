/** \file FT_module.c
  * \brief Functions to compute Fourier-Taylor series and write it to file. Given \f$ (I,\phi') \f$, find \f$ pd{L^*}{\phi'} \f$.
  *
  * NOTES: 
  *		Fourier coeffs are read from files coeffs_*.res, which were generated
  *		by fft.sh
  *
  * CALLED BY: FT.c, FT_error.c	
  *
  */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>

static const char ddA_FILE[] = "ddA.res";
static const char ddB_FILE[] = "ddB.res";

void read_Fourier_coefs(size_t ntori, size_t nfour, 
		double A_all[ntori][nfour], double B_all[ntori][nfour]) 
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

/** 
 * \brief Compute FT series, i.e. divided differences of Fourier coeffs A(I) or
 * B(I).
 *
 * @param[in]   ntori	Number of tori
 * @param[in]   nfour	Number of Fourier coefficients computed by FFT
 * @param[in]   coefs_all	Table containing for each torus I, its Fourier coefs. A_n (or B_n).
 * @param[out]  dd  Fourier-Taylor series (div. difs. of Fourier coeffs).
 * 
 */
void compute_FT(size_t ntori, size_t nfour, double coefs_all[ntori][nfour],
		double dd[nfour][ntori]) 
{
	const int n=ntori;

	for(int j=0; j<nfour; j++)
    {
		double x[n], y[n];

		/* input curve */
		for(int i=0; i<n; i++)
        {
            x[i] = i+2;			/* I */
            y[i] = coefs_all[i][j];	/* A_j(I) or B_j(I) */
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
			dd[j][i] = state->d[i];

        gsl_spline_free (spline);
        gsl_interp_accel_free (acc);
    }
}

/** 
 * \brief Write FT series (divided differences) to file.
 *
 * @param[in]   nfour   Degree of the Fourier series = nfour-1.
 * @param[in]   ntori   Degree of the Taylor series = ntori-1.
 *
 * @param[in]  ddA     Fourier-Taylor series (div. difs. of coefs A_j).
 * @param[in]  ddB     Fourier-Taylor series (div. difs. of coefs B_j).
 */
void write_FT(size_t nfour, size_t ntori, double ddA[nfour][ntori], double
		ddB[nfour][ntori])
{
    FILE *fpA = fopen(ddA_FILE, "w");
    FILE *fpB = fopen(ddB_FILE, "w");
    for(int i=0; i<nfour; i++)
    {
        for(int j=0; j<ntori; j++)
        {
            fprintf(fpA, "%lf ", ddA[i][j]);
            fprintf(fpB, "%lf ", ddB[i][j]);
        }
        fprintf(fpA, "\n");
        fprintf(fpB, "\n");
    }
    fclose(fpA);
    fclose(fpB);
}

/** 
 * \brief Read FT series (divided differences) from file.
 *
 * @param[in]   nfour   Degree of the Fourier series = nfour-1.
 * @param[in]   ntori   Degree of the Taylor series = ntori-1.
 *
 * @param[out]  ddA     Fourier-Taylor series (div. difs. of coefs A_j).
 * @param[out]  ddB     Fourier-Taylor series (div. difs. of coefs B_j).
 */
void read_FT(size_t nfour, size_t ntori, double ddA[nfour][ntori], double
		ddB[nfour][ntori])
{
    FILE *fpA = fopen(ddA_FILE, "r");
    FILE *fpB = fopen(ddB_FILE, "r");

	int nIt;	// Number of read items
    for(int i=0; i<nfour; i++)
    {
        for(int j=0; j<ntori; j++)
        {
            nIt = fscanf(fpA, "%lf ", &(ddA[i][j]));
            nIt = fscanf(fpB, "%lf ", &(ddB[i][j]));
        }
        nIt = fscanf(fpA, "\n");
        nIt = fscanf(fpB, "\n");
    }
    fclose(fpA);
    fclose(fpB);
}

/** 
 * \brief Evaluate Fourier coefs A_j (or B_j) at I using Taylor interpolation.
 *
 * @param[in]   nfour   Max degree of the Fourier series = nfour-1.
 * @param[in]   ntori   Max degree of the Taylor series = ntori-1.
 * @param[in]   ddA Complete Fourier-Taylor series (div. difs. of Fourier coeffs).
 * @param[in]   N   Degree of the Fourier series.
 * @param[in]   M   Degree of the Taylor series.
 * @param[in]   I   Action at which we want to evaluate.
 * @param[out]  A   Fourier coefs A_j(I) (or B_j(I)).
 */
void coefs_eval(size_t nfour, size_t ntori, double ddA[nfour][ntori], size_t N,
		size_t M, double I, double A[N+1]) 
{
	for(int j=0; j<=N; j++)
    {
        double d0, d1, d2, d3, d4;
        d0 = ddA[j][0];
        d1 = ddA[j][1];
        d2 = ddA[j][2];
        d3 = ddA[j][3];
        d4 = ddA[j][4];

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
    }
}

/** 
 * \brief Evaluate derivative of Fourier coefs A_j (or B_j) at I using Taylor interpolation.
 *
 * @param[in]   nfour   Max degree of the Fourier series = nfour-1.
 * @param[in]   ntori   Max degree of the Taylor series = ntori-1.
 * @param[in]   ddA Complete Fourier-Taylor series (div. difs. of Fourier coeffs).
 * @param[in]   N   Degree of the Fourier series.
 * @param[in]   M   Degree of the Taylor series.
 * @param[in]   I   Action at which we want to evaluate.
 * @param[out]  A   Fourier coefs A_j(I) (or B_j(I)).
 */
void dcoefs_eval(size_t nfour, size_t ntori, double ddA[nfour][ntori], size_t N,
		size_t M, double I, double Ap[N+1]) 
{
	double I0=2;
	double I1=3;
	double I2=4;
	double I3=5;
	for(int j=0; j<=N; j++)
    {
        double d0, d1, d2, d3, d4;
        d0 = ddA[j][0];
        d1 = ddA[j][1];
        d2 = ddA[j][2];
        d3 = ddA[j][3];
        d4 = ddA[j][4];

        /* Interpolate F. coef A_j' at I */
        switch(M)
        {
            case 0:
                Ap[j] = 0;
                break;
            case 1:
                Ap[j] = d1;
                break;
            case 2: 
                Ap[j] = d1 + d2*((I-I1)+(I-I0));
                break;
            case 3:
                Ap[j] = d1 + d2*((I-I1)+(I-I0)) +
					d3*((I-I1)*(I-I2) + (I-I0)*(I-I2) + (I-I0)*(I-I1));
                break;
            case 4:
                Ap[j] =  d1 + d2*((I-I1)+(I-I0)) +
					d3*((I-I1)*(I-I2) + (I-I0)*(I-I2) + (I-I0)*(I-I1)) +
					d4*((I-I1)*(I-I2)*(I-I3) + (I-I0)*(I-I2)*(I-I3) +
							(I-I0)*(I-I1)*(I-I3) + (I-I0)*(I-I1)*(I-I2));
                break;
            default:
                break;
        }
    }
}

/**
 * \brief Given \f$(I,\phi')\f$, find \f$pd{\widetilde{L}}{\phi'}(I,\phi)\f$
 *
 * @param[in] N		Degree of Fourier series
 * @param[in] A		A = (A_0, A_1, ..., A_N), Fourier coeffs evaluated at I
 * @param[in] B		B = (B_0, B_1, ..., B_N), Fourier coeffs evaluated at I
 * @param[in] phi	Angle where to evaluate the partial derivative.
 */
double dL_dphi(size_t N, double A[N+1], double B[N+1], double phi)
{
	double res = 0.0;
	for(int j=1; j<=N; j++)
	{
		res = res + (A[j]*cos(j*phi) + B[j]*sin(j*phi));
	}
	return res;
}

/**
 * \brief Given \f$ (I,\phi') \f$, find \f$ pd{\widetilde{L}}{I}(I,\phi) \f$
 *
 * @param[in] N		Degree of Fourier series
 * @param[in] Ap	A' = (A_0', A_1', ..., A_N'), A_k' := dA_k/dI(I)
 * @param[in] Bp	B' = (B_0', B_1', ..., B_N'), B_k' := dB_k/dI(I)
 * @param[in] phi	Angle where to evaluate the partial derivative.
 */
double dL_dI(size_t N, double Ap[N+1], double Bp[N+1], double phi)
{
	double res = 0.0;
	for(int j=1; j<=N; j++)
	{
		res = res + (Ap[j]/j*sin(j*phi) - Bp[j]/j*cos(j*phi));
	}
	return res;
}

