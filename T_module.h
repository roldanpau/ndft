/** \file T_module.h
  * \brief Functions to compute Taylor series of \f$\omega(I)\f$ and write it to file.
  */

void read_omegas(size_t ntori, double omega_all[ntori]); 

void compute_T(size_t ntori, double omega_all[ntori], double dd[ntori]);

void write_T(size_t ntori, double dd[ntori]);
void read_T(size_t ntori, double dd[ntori]);

void omega_eval(size_t ntori, double dd[ntori], size_t M, double I, double
        *omega_p);
