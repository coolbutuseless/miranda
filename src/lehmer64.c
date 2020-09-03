
#include <R.h>
#include <Rinternals.h>
#include <stdint.h>
#include "splitmix64.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// PRNG State
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef _WIN32
unsigned __int128 g_lehmer64_state;
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Original PRNG
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef _WIN32
uint64_t next_lehmer64() {
  g_lehmer64_state *= 0xda942042e4dd58b5;
  return g_lehmer64_state >> 64;
}
#endif


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Set a seed
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP set_seed_lehmer64_(SEXP seedlo, SEXP seedhi) {
#ifndef _WIN32
  uint64_t index = asInteger(seedlo) + ((uint64_t)asInteger(seedhi) << 32);
  g_lehmer64_state = runif1_splitmix64_stateless(index + 0) +
                     ((unsigned __int128 )runif1_splitmix64_stateless(index + 1) << 64);
#endif
  return R_NilValue;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// get state
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP get_state_lehmer64_(void) {
#ifdef _WIN32
  return R_NilValue;
#else
  SEXP bytes = PROTECT(allocVector(RAWSXP, 16));
  void *pbytes = (void *)RAW(bytes);

  memcpy(pbytes, &g_lehmer64_state, 16);

  UNPROTECT(1);
  return(bytes);
#endif
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// set state
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP set_state_lehmer64_(SEXP state_) {
#ifndef _WIN32
  void *values = (void *)RAW(state_);

  memcpy(&g_lehmer64_state, values, 16);
#endif
  return R_NilValue;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// C function callable from R to generate single random number in [0,1]
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP runif1_lehmer64_() {
#ifdef _WIN32
  Rprintf("lehmer64 relies on a 64bit R build")
  double result_double = 0;
#else
  g_lehmer64_state *= 0xda942042e4dd58b5;

  uint64_t result_int64 = g_lehmer64_state >> 64;
  double result_double = (result_int64 >> 11) * 0x1.0p-53;
#endif
  return ScalarReal(result_double);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// C function callable from R to generate multiple random numbers in [0,1]
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP runif_lehmer64_(SEXP n_, SEXP min_, SEXP max_) {
#ifdef _WIN32
  Rprintf("lehmer64 relies on a 64bit R build")
  return ScalarReal(0);
#else
  int n = asInteger(n_);
  double dmin = asReal(min_);
  double dmax = asReal(max_);
  double drange = dmax - dmin;

  SEXP dbl_vec = PROTECT(allocVector(REALSXP, n));
  double *dbl_ptr = REAL(dbl_vec);

  for (int i = 0; i < n; i++) {
    g_lehmer64_state *= 0xda942042e4dd58b5;

    uint64_t result = g_lehmer64_state >> 64;
    *dbl_ptr++ = (result >> 11) * 0x1.0p-53 * drange + dmin;
  }

  UNPROTECT(1);
  return dbl_vec;
#endif
}

