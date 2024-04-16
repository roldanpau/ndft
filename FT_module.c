/** \file FT_module.c
  * \brief Functions to compute Fourier-Taylor series and write it to file. Given \f$ (I,\phi') \f$, find \f$ pd{L^*}{\phi'} \f$.
  *
  * NOTES: 
  *		Fourier coeffs are read from files coeffs_*.res, which were generated
  *		by fft.sh
  *
  *		Do the same for the second scattering map, reading coeffs from files
  *		coeffs_*_SM2.res, and writing coeffs to ddA_SM2.res and ddB_SM2.res.
  *
  * CALLED BY: FT.c, FT_error.c	
  *
  */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>
#include "FT_module.h"		// SM_t

static const char A2_FILE[] = "A2.res";
static const char B2_FILE[] = "B2.res";
static const char A4_FILE[] = "A4.res";
static const char B4_FILE[] = "B4.res";
static const char ddA_FILE[] = "ddA.res";
static const char ddB_FILE[] = "ddB.res";

static const char A2_FILE_SM2[] = "A2_SM2.res";
static const char B2_FILE_SM2[] = "B2_SM2.res";
static const char A4_FILE_SM2[] = "A4_SM2.res";
static const char B4_FILE_SM2[] = "B4_SM2.res";
static const char ddA_FILE_SM2[] = "ddA_SM2.res";
static const char ddB_FILE_SM2[] = "ddB_SM2.res";

void write_Fourier_all_tori(size_t ntori, size_t nfour, 
		double coefs_all[ntori][nfour], int four, const char *filename);

/** 
 * \brief Read Fourier coefficients from files coeffs_*.res.
 *
 * Read Fourier coefficients from files coeffs_*.res, which were generated by
 * fft.sh. Since the scattering map is \f$\pi\f$-periodic, odd Fourier
 * coefficients should be zero. Thus we decide to zero all odd coefficients to
 * impose that the Fourier series preserves the symmetry.
 *
 * Fourier coefficients \f$ A_n(0), B_n(0) \f$ are zero, so we set them
 * separately.
 *
 * @param[in]   ntori	Number of tori
 * @param[in]   nfour	Number of Fourier coefficients computed by FFT
 * @param[in]   SM		SM1 or SM2
 *
 * @param[out]  A_all	Table containing for each torus I, its Fourier coefs.
 * A_n.
 * @param[out]  B_all	Table containing for each torus I, its Fourier coefs.
 * B_n.
 */
void read_Fourier_coefs(size_t ntori, size_t nfour, SM_t SM,
		double A_all[ntori][nfour], double B_all[ntori][nfour]) 
{
	/* auxiliary variables */
	char filename[100];
	double *Ap, *Bp;
	FILE *fp;
	int coeff_num;
	int i,j;

	/* Fourier coefficients \f$ A_n(0), B_n(0) \f$ of first torus are known to
	 * be zero, so we set them separately. */
	for(j=0; j<nfour; j++)
		A_all[0][j] = 0;

	/* Read Fourier coeffs of all other tori from file */
	for(int i=1; i<ntori; i++)
	{
		if(SM == SM1) sprintf(filename, "coeffs_%d.res", i+1);
		else sprintf(filename, "coeffs_%d_SM2.res", i+1);

		Ap = A_all[i];
		Bp = B_all[i];

		fp = fopen(filename, "r");
		while(fscanf(fp,"%d %le %le", &coeff_num, Ap, Bp) != EOF) {
			/* Zero all odd Fourier coefficients */
			if(coeff_num % 2 != 0)	
			{
				*Ap=0; 
				*Bp=0;
			}

			/* advance pointers */
			Ap ++; Bp ++;

		}
		fclose(fp);
	}

	if(SM == SM1)
	{
		write_Fourier_all_tori(ntori, nfour, A_all, 2, A2_FILE); 
		write_Fourier_all_tori(ntori, nfour, B_all, 2, B2_FILE); 
		write_Fourier_all_tori(ntori, nfour, A_all, 4, A4_FILE); 
		write_Fourier_all_tori(ntori, nfour, B_all, 4, B4_FILE); 
	}
	else	// SM2
	{	
		write_Fourier_all_tori(ntori, nfour, A_all, 2, A2_FILE_SM2); 
		write_Fourier_all_tori(ntori, nfour, B_all, 2, B2_FILE_SM2); 
		write_Fourier_all_tori(ntori, nfour, A_all, 4, A4_FILE_SM2); 
		write_Fourier_all_tori(ntori, nfour, B_all, 4, B4_FILE_SM2); 
	}
}

/** 
 * \brief Write Fourier coefficient `n' of each tori (torus=0,1,2,...,7).
 *
 * The file generated (e.g. A0.res) is used for inspection and plotted in
 * interp_poly_A2.plt.
 *
 * @param[in]   ntori	Number of tori
 * @param[in]   nfour	Number of Fourier coefficients computed by FFT
 * @param[in]	coefs_all	Table containing for each torus I, its Fourier coefs.
 * A_n/B_n.
 *
 * @param[in]	four	Fourier coefficient to write.
 *
 * @param[in]	filename	Name of file to write to (e.g. A0.res).
 */
void write_Fourier_all_tori(size_t ntori, size_t nfour, 
		double coefs_all[ntori][nfour], int four, const char *filename) 
{
	const int n=ntori;
	const int j=four;

	double x[n], y[n];

	/* auxiliary variables */
	FILE *fp;

	fp = fopen(filename, "w");

	/* Write coefs */
	for(int i=0; i<n; i++)
	{
		x[i] = i;			/* I */
		y[i] = coefs_all[i][j];	/* A_j(I) or B_j(I) */
		fprintf(fp, "%f %f\n", x[i], y[i]);
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
            x[i] = i;			/* I */
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
 * @param[in]   SM		SM1 or SM2
 *
 * @param[in]  ddA     Fourier-Taylor series (div. difs. of coefs A_j).
 * @param[in]  ddB     Fourier-Taylor series (div. difs. of coefs B_j).
 */
void write_FT(size_t nfour, size_t ntori, SM_t SM, double ddA[nfour][ntori],
		double ddB[nfour][ntori])
{
	FILE *fpA;
	FILE *fpB;
	if(SM==SM1)
	{
		fpA = fopen(ddA_FILE, "w");
		fpB = fopen(ddB_FILE, "w");
	}
	else // SM2
	{
		fpA = fopen(ddA_FILE_SM2, "w");
		fpB = fopen(ddB_FILE_SM2, "w");
	}
    for(int i=0; i<nfour; i++)
    {
        for(int j=0; j<ntori-1; j++)
        {
            fprintf(fpA, "%lf ", ddA[i][j]);
            fprintf(fpB, "%lf ", ddB[i][j]);
        }
		// Last divided difference, j == ntori-1, is treated differently, since
		// we don't want to add a space character after it.
        fprintf(fpA, "%lf\n", ddA[i][ntori-1]);
        fprintf(fpB, "%lf\n", ddB[i][ntori-1]);
    }
    fclose(fpA);
    fclose(fpB);
}

/** 
 * \brief Read FT series (divided differences) from file.
 *
 * @param[in]   nfour   Degree of the Fourier series = nfour-1.
 * @param[in]   ntori   Degree of the Taylor series = ntori-1.
 * @param[in]   SM		SM1 or SM2
 *
 * @param[out]  ddA     Fourier-Taylor series (div. difs. of coefs A_j).
 * @param[out]  ddB     Fourier-Taylor series (div. difs. of coefs B_j).
 */
void read_FT(size_t nfour, size_t ntori, SM_t SM, double ddA[nfour][ntori],
		double ddB[nfour][ntori])
{
	FILE *fpA;
	FILE *fpB;
	if(SM==SM1)
	{
		fpA = fopen(ddA_FILE, "r");
		fpB = fopen(ddB_FILE, "r");
	}
	else // SM2
	{
		fpA = fopen(ddA_FILE_SM2, "r");
		fpB = fopen(ddB_FILE_SM2, "r");
	}

	int nIt;	// Number of read items
    for(int i=0; i<nfour; i++)
    {
        for(int j=0; j<ntori-1; j++)
        {
            nIt = fscanf(fpA, "%lf ", &(ddA[i][j]));
            nIt = fscanf(fpB, "%lf ", &(ddB[i][j]));
        }
		// Last divided difference, j == ntori-1, is treated differently, since
		// we don't want to add a space character after it.
        nIt = fscanf(fpA, "%lf\n", &(ddA[i][ntori-1]));
        nIt = fscanf(fpB, "%lf\n", &(ddB[i][ntori-1]));
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
	const double I0=0;
	const double I1=1;
	const double I2=2;
	const double I3=3;
	const double I4=4;
	const double I5=5;
	const double I6=6;

        /* Interpolate F. coef A_j at I */
        assert(M<=7);
        switch(M)
        {
            case 0:
                A[j] = ddA[j][0];
                break;
            case 1:
                A[j] = ddA[j][0] + ddA[j][1]*(I-I0);
                break;
            case 2: 
                A[j] = ddA[j][0] + ddA[j][1]*(I-I0) + ddA[j][2]*(I-I0)*(I-I1);
                break;
            case 3:
                A[j] = ddA[j][0] + ddA[j][1]*(I-I0) + ddA[j][2]*(I-I0)*(I-I1) +
                    ddA[j][3]*(I-I0)*(I-I1)*(I-I2);
                break;
            case 4:
                A[j] = ddA[j][0] + ddA[j][1]*(I-I0) + ddA[j][2]*(I-I0)*(I-I1) +
                    ddA[j][3]*(I-I0)*(I-I1)*(I-I2) + 
                    ddA[j][4]*(I-I0)*(I-I1)*(I-I2)*(I-I3);
                break;
            case 5:
                A[j] = ddA[j][0] + ddA[j][1]*(I-I0) + ddA[j][2]*(I-I0)*(I-I1) +
                    ddA[j][3]*(I-I0)*(I-I1)*(I-I2) + 
                    ddA[j][4]*(I-I0)*(I-I1)*(I-I2)*(I-I3) +
                    ddA[j][5]*(I-I0)*(I-I1)*(I-I2)*(I-I3)*(I-I4);
                break;
            case 6:
                A[j] = ddA[j][0] + ddA[j][1]*(I-I0) + ddA[j][2]*(I-I0)*(I-I1) +
                    ddA[j][3]*(I-I0)*(I-I1)*(I-I2) + 
                    ddA[j][4]*(I-I0)*(I-I1)*(I-I2)*(I-I3) +
                    ddA[j][5]*(I-I0)*(I-I1)*(I-I2)*(I-I3)*(I-I4) +
                    ddA[j][6]*(I-I0)*(I-I1)*(I-I2)*(I-I3)*(I-I4)*(I-I5);
                break;
            case 7:
                A[j] = ddA[j][0] + ddA[j][1]*(I-I0) + ddA[j][2]*(I-I0)*(I-I1) +
                    ddA[j][3]*(I-I0)*(I-I1)*(I-I2) + 
                    ddA[j][4]*(I-I0)*(I-I1)*(I-I2)*(I-I3) +
                    ddA[j][5]*(I-I0)*(I-I1)*(I-I2)*(I-I3)*(I-I4) +
                    ddA[j][6]*(I-I0)*(I-I1)*(I-I2)*(I-I3)*(I-I4)*(I-I5) +
                    ddA[j][7]*(I-I0)*(I-I1)*(I-I2)*(I-I3)*(I-I4)*(I-I5)*(I-I6);
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
 * @param[out]  Ap   Derivative of Fourier coefs A_j(I) (or B_j(I)).
 */
void dcoefs_eval(size_t nfour, size_t ntori, double ddA[nfour][ntori], size_t N,
		size_t M, double I, double Ap[N+1]) 
{
	const double I0=0;
	const double I1=1;
	const double I2=2;
	const double I3=3;
	const double I4=4;
	const double I5=5;
	const double I6=6;

	for(int j=0; j<=N; j++)
    {
        /* Interpolate F. coef A_j' at I */
        assert(M<=7);
        switch(M)
        {
            case 0:
                Ap[j] = 0;
                break;
            case 1:
                Ap[j] = ddA[j][1];
                break;
            case 2: 
                Ap[j] = ddA[j][1] + ddA[j][2]*((I-I1)+(I-I0));
                break;
            case 3:
                Ap[j] = ddA[j][1] + ddA[j][2]*((I-I1)+(I-I0)) +
					ddA[j][3]*((I-I1)*(I-I2) + (I-I0)*(I-I2) + (I-I0)*(I-I1));
                break;
            case 4:
                Ap[j] =  ddA[j][1] + ddA[j][2]*((I-I1)+(I-I0)) +
					ddA[j][3]*((I-I1)*(I-I2) + (I-I0)*(I-I2) + (I-I0)*(I-I1)) +
					ddA[j][4]*((I-I1)*(I-I2)*(I-I3) + (I-I0)*(I-I2)*(I-I3) +
							(I-I0)*(I-I1)*(I-I3) + (I-I0)*(I-I1)*(I-I2));
                break;
            case 5:
                Ap[j] =  ddA[j][1] + 
                    ddA[j][2]*((I-I1)+(I-I0)) +
					ddA[j][3]*((I-I1)*(I-I2) + (I-I0)*(I-I2) + (I-I0)*(I-I1)) +
					ddA[j][4]*((I-I1)*(I-I2)*(I-I3) + (I-I0)*(I-I2)*(I-I3) +
							(I-I0)*(I-I1)*(I-I3) + (I-I0)*(I-I1)*(I-I2)) +
					ddA[j][5]*((I-I1)*(I-I2)*(I-I3)*(I-I4) + 
                            (I-I0)*(I-I2)*(I-I3)*(I-I4) +
							(I-I0)*(I-I1)*(I-I3)*(I-I4) + 
                            (I-I0)*(I-I1)*(I-I2)*(I-I4) + 
                            (I-I0)*(I-I1)*(I-I2)*(I-I3));
                break;
            case 6:
                Ap[j] =  ddA[j][1] + 
                    ddA[j][2]*((I-I1)+(I-I0)) +
					ddA[j][3]*((I-I1)*(I-I2) + (I-I0)*(I-I2) + (I-I0)*(I-I1)) +
					ddA[j][4]*((I-I1)*(I-I2)*(I-I3) + (I-I0)*(I-I2)*(I-I3) +
							(I-I0)*(I-I1)*(I-I3) + (I-I0)*(I-I1)*(I-I2)) +
					ddA[j][5]*((I-I1)*(I-I2)*(I-I3)*(I-I4) + 
                            (I-I0)*(I-I2)*(I-I3)*(I-I4) +
							(I-I0)*(I-I1)*(I-I3)*(I-I4) + 
                            (I-I0)*(I-I1)*(I-I2)*(I-I4) + 
                            (I-I0)*(I-I1)*(I-I2)*(I-I3)) +
					ddA[j][6]*((I-I1)*(I-I2)*(I-I3)*(I-I4)*(I-I5) + 
                            (I-I0)*(I-I2)*(I-I3)*(I-I4)*(I-I5) +
							(I-I0)*(I-I1)*(I-I3)*(I-I4)*(I-I5) + 
                            (I-I0)*(I-I1)*(I-I2)*(I-I4)*(I-I5) + 
                            (I-I0)*(I-I1)*(I-I2)*(I-I3)*(I-I5) +
                            (I-I0)*(I-I1)*(I-I2)*(I-I3)*(I-I4));
                break;
            case 7:
                Ap[j] =  ddA[j][1] + 
                    ddA[j][2]*((I-I1)+(I-I0)) +
					ddA[j][3]*((I-I1)*(I-I2) + (I-I0)*(I-I2) + (I-I0)*(I-I1)) +
					ddA[j][4]*((I-I1)*(I-I2)*(I-I3) + (I-I0)*(I-I2)*(I-I3) +
							(I-I0)*(I-I1)*(I-I3) + (I-I0)*(I-I1)*(I-I2)) +
					ddA[j][5]*((I-I1)*(I-I2)*(I-I3)*(I-I4) + 
                            (I-I0)*(I-I2)*(I-I3)*(I-I4) +
							(I-I0)*(I-I1)*(I-I3)*(I-I4) + 
                            (I-I0)*(I-I1)*(I-I2)*(I-I4) + 
                            (I-I0)*(I-I1)*(I-I2)*(I-I3)) +
					ddA[j][6]*((I-I1)*(I-I2)*(I-I3)*(I-I4)*(I-I5) + 
                            (I-I0)*(I-I2)*(I-I3)*(I-I4)*(I-I5) +
							(I-I0)*(I-I1)*(I-I3)*(I-I4)*(I-I5) + 
                            (I-I0)*(I-I1)*(I-I2)*(I-I4)*(I-I5) + 
                            (I-I0)*(I-I1)*(I-I2)*(I-I3)*(I-I5) +
                            (I-I0)*(I-I1)*(I-I2)*(I-I3)*(I-I4)) +
					ddA[j][7]*((I-I1)*(I-I2)*(I-I3)*(I-I4)*(I-I5)*(I-I6) + 
                            (I-I0)*(I-I2)*(I-I3)*(I-I4)*(I-I5)*(I-I6) +
							(I-I0)*(I-I1)*(I-I3)*(I-I4)*(I-I5)*(I-I6) + 
                            (I-I0)*(I-I1)*(I-I2)*(I-I4)*(I-I5)*(I-I6) + 
                            (I-I0)*(I-I1)*(I-I2)*(I-I3)*(I-I5)*(I-I6) +
                            (I-I0)*(I-I1)*(I-I2)*(I-I3)*(I-I4)*(I-I6) +
                            (I-I0)*(I-I1)*(I-I2)*(I-I3)*(I-I4)*(I-I5));
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

/**
 * \brief Given \f$(I,\phi')\f$, find \f$\widetilde{L}(I,\phi')\f$
 *
 * @param[in] N		Degree of Fourier series
 * @param[in] A		A = (A_0, A_1, ..., A_N), Fourier coeffs evaluated at I
 * @param[in] B		B = (B_0, B_1, ..., B_N), Fourier coeffs evaluated at I
 * @param[in] phip	Angle where to evaluate the function.
 */
double widetildeL(size_t N, double A[N+1], double B[N+1], double phip)
{
	double res = 0.0;
	for(int n=1; n<=N; n++)
	{
		res = res - B[n]/n*cos(n*phip) + A[n]/n*sin(n*phip);
	}
	return res;
}

