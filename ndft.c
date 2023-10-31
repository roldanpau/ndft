/*
 * Copyright (c) 2002, 2017 Jens Keiner, Stefan Kunis, Daniel Potts
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define NFFT_PRECISION_DOUBLE

#include "nfft3mp.h"

static void simple_test_nfft_1d(void)
{
  NFFT(plan) p;

  int N = 14;
  int M = 19;

  const char *error_str;

  /** init an one dimensional plan */
  NFFT(init_1d)(&p, N, M);

  /** init pseudo random nodes */
  NFFT(vrand_shifted_unit_double)(p.x, p.M_total);
 
  /** precompute psi, the entries of the matrix B */
  if (p.flags & PRE_ONE_PSI)
      NFFT(precompute_one_psi)(&p);

  /** init pseudo random Fourier coefficients and show them */
  NFFT(vrand_unit_complex)(p.f_hat,p.N_total);
  NFFT(vpr_complex)(p.f_hat, p.N_total, "given Fourier coefficients, vector f_hat");

  /** check for valid parameters before calling any trafo/adjoint method */
  error_str = NFFT(check)(&p);
  if (error_str != 0)
  {
    printf("Error in nfft module: %s\n", error_str);
    return;
  }

  /** direct trafo and show the result */
  NFFT(trafo_direct)(&p);
  NFFT(vpr_complex)(p.f,p.M_total,"ndft, vector f");

  /** approx. trafo and show the result */
  NFFT(trafo)(&p);
  NFFT(vpr_complex)(p.f,p.M_total,"nfft, vector f");

  /** approx. adjoint and show the result */
  NFFT(adjoint_direct)(&p);
  NFFT(vpr_complex)(p.f_hat,p.N_total,"adjoint ndft, vector f_hat");

  /** approx. adjoint and show the result */
  NFFT(adjoint)(&p);
  NFFT(vpr_complex)(p.f_hat,p.N_total,"adjoint nfft, vector f_hat");

  /** finalise the one dimensional plan */
  NFFT(finalize)(&p);
}

int main(void)
{
  printf("1) computing a one dimensional ndft, nfft and an adjoint nfft\n\n");
  simple_test_nfft_1d();
  return EXIT_SUCCESS;
}
