/** \file SM_module.c
  * \brief Functions to compute the scattering map \f$ (I', \phi') = \sigma(I,\phi) \f$.
  *
  *	The degree (N,M) of the Fourier-Taylor series can be modified in the code.
  *
  * CALLED BY: SM, SM_given_I
  *
  */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>       // M_PI
#include "FT_module.h"
#include "T_module.h"

/** \brief Iteratively find \f$ \phi' = F(\phi'; I, \phi) \f$.
 *
 *  Variable \f$ \phi' \f$ is defined implicitly by equation
 *  \f\[ \phi' = \phi - \omega(I) - \pd{\gft}{I}(I, \phi'). \f\]
 *  Iterate the right hand side, starting with 
 *  \f\[ \phi'_0 = \phi - \omega(I), \f\]
 *  until \f$ \phi' \f$ converges.
 */
double iteration(size_t N, double Ap[N+1], double Bp[N+1], double omega, 
        double phi)
{
    double phip, phip_old;

    phip_old = 4*M_PI;
    phip = phi - omega;
    //printf("phip: %f\n", phip);
    while(fabs(phip - phip_old)>1.e-5)
    {
        phip_old = phip;
        phip = phi - omega - dL_dI(N, Ap, Bp, phip);
        //printf("phip: %f\n", phip);
    } 
    return constrainAngle(phip);
}

/** \brief Iteratively find \f$ \phi' = F(\phi'; I, \phi) \f$.
 *
 *  Variable \f$ \phi' \f$ is defined implicitly by equation
 *  \f\[ \phi' = \phi - \omega(I) - \pd{\gft}{I}(I, \phi'). \f\]
 *  Iterate the right hand side, starting with 
 *  \f\[ \phi'_0 = \phi - \omega(I), \f\]
 *  until \f$ \phi' \f$ converges.
 */
double damped_iteration(size_t N, double Ap[N+1], double Bp[N+1], double omega,
		double phi, double a)
{
    double phip, phip_old;

    phip_old = 4*M_PI;
    phip = phi - omega;
    //printf("phip: %f\n", phip);
    while(fabs(phip - phip_old)>1.e-5)
    {
        phip_old = phip;
        phip = phi - omega - a*dL_dI(N, Ap, Bp, phip);
        //printf("phip: %f\n", phip);
    } 
    return constrainAngle(phip);
}

/**
  * \brief Compute the scattering map \f$ (I', \phi') = \sigma(I,\phi) \f$.
  *
  * NOTE:
  *		The degree of the Fourier-Taylor expansion used is \f$N, L\f$ (hardcoded
  *		at the beginning of this file).
  *
  *		If the initial condition \f$ (I, \phi) \f$ is outside the known domain
  *		of the SM, we don't iterate. In that case, the function silently
  *		returns \f$ (I, \phi) \f$ as the final condition.
  */
void SM(int nfour, int ntori, double ddA[nfour][ntori], 
        double ddB[nfour][ntori], double ddOmega[ntori-1], int N, int M, double
        I, double phi, double *Ip, double *phip)
{
	double A[N+1];	/* Fourier coefficients A_0(I), A_1(I), ..., A_N(I) */
	double B[N+1];	/* Fourier coefficients B_0(I), B_1(I), ..., B_n(I) */

    /* Derivative of Fourier coefficients A_0(I), A_1(I), ..., A_N(I) */
	double Ap[N+1];	
	double Bp[N+1];	

    double omega;   /* Interpolated omega value at I */

	if(I<=0 || I>7)	/* Initial condition is outside known domain of SM */
	{
		fprintf(stderr, "I.C. outside known domain of SM\n");
		*Ip = I;
		*phip = phi;
		return;
	}

    /* Compute Fourier coefs A_n(I), B_n(I) for action value I */
    coefs_eval(nfour,ntori,ddA,N,M,I,A);
    coefs_eval(nfour,ntori,ddB,N,M,I,B);

    /* Compute derivative of F. coefs A_n(I), B_n(I) for action value I */
    dcoefs_eval(nfour,ntori,ddA,N,M,I,Ap);
    dcoefs_eval(nfour,ntori,ddB,N,M,I,Bp);

    /* Compute omega(I) for action value I */
    omega_eval(ntori-1,ddOmega,M,I,&omega);

	/* Find the image (I', \phi') of (I,phi) by the transition map. */
    *phip = iteration(N, Ap, Bp, omega, phi);
    *Ip = I + dL_dphi(N, A, B, *phip);
}


/**
  * \brief Compute the damped scattering map, damped by non-integrability
  * parameter \f$a\f$.
  *
  * NOTE:
  *		The degree of the Fourier-Taylor expansion used is \f$N, L\f$ (hardcoded
  *		at the beginning of this file).
  *
  *		If the initial condition \f$ (I, \phi) \f$ is outside the known domain
  *		of the SM, we DO iterate. (To see what happens above/below tori [2,4].)
  */
void damped_SM(int nfour, int ntori, double ddA[nfour][ntori], 
        double ddB[nfour][ntori], double ddOmega[ntori-1], int N, int M, double
        I, double phi, double *Ip, double *phip, double a)
{
	double A[N+1];	/* Fourier coefficients A_0(I), A_1(I), ..., A_N(I) */
	double B[N+1];	/* Fourier coefficients B_0(I), B_1(I), ..., B_n(I) */

    /* Derivative of Fourier coefficients A_0(I), A_1(I), ..., A_N(I) */
	double Ap[N+1];	
	double Bp[N+1];	

    double omega;   /* Interpolated omega value at I */

	if(I<=0 || I>7)	/* Initial condition is outside known domain of SM */
	{
		fprintf(stderr, "I.C. outside known domain of SM\n");
		*Ip = I;
		*phip = phi;
		return;
	}

    /* Compute Fourier coefs A_n(I), B_n(I) for action value I */
    coefs_eval(nfour,ntori,ddA,N,M,I,A);
    coefs_eval(nfour,ntori,ddB,N,M,I,B);

    /* Compute derivative of F. coefs A_n(I), B_n(I) for action value I */
    dcoefs_eval(nfour,ntori,ddA,N,M,I,Ap);
    dcoefs_eval(nfour,ntori,ddB,N,M,I,Bp);

    /* Compute omega(I) for action value I */
    omega_eval(ntori-1,ddOmega,M,I,&omega);

	/* Find the image (I', \phi') of (I,phi) by the transition map. */
    *phip = damped_iteration(N, Ap, Bp, omega, phi, a);
    *Ip = I + a*dL_dphi(N, A, B, *phip);
}


