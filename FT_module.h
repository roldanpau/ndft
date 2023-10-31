/** \file FT_module.h
  * \brief Functions to compute Fourier-Taylor series and write it to file. Given \f$ (I,\phi') \f$, find \f$ pd{L^*}{\phi'} \f$.
  *
  * NOTES: 
  *		Fourier coeffs are read from files coeffs_*.res, which were generated
  *		by fft.sh
  *
  */

void read_Fourier_coefs(size_t ntori, size_t nfour, 
		double A_all[ntori][nfour], double B_all[ntori][nfour]);

void compute_FT(size_t ntori, size_t nfour, double coefs_all[ntori][nfour],
		double dd[nfour][ntori]);

void write_FT(size_t nfour, size_t ntori, double ddA[nfour][ntori], double
		ddB[nfour][ntori]);
void read_FT(size_t nfour, size_t ntori, double ddA[nfour][ntori], double
		ddB[nfour][ntori]);

void coefs_eval(size_t nfour, size_t ntori, double ddA[nfour][ntori], size_t N,
		size_t M, double I, double A[N+1]);
void dcoefs_eval(size_t nfour, size_t ntori, double ddA[nfour][ntori], size_t N,
		size_t M, double I, double A[N+1]);


double dL_dphi(size_t N, double A[N+1], double B[N+1], double phi);
double dL_dI(size_t N, double Ap[N+1], double Bp[N+1], double phi);
