

/*  Written in 2015 by Sebastiano Vigna (vigna@acm.org)

 To the extent possible under law, the author has dedicated all copyright
 and related and neighboring rights to this software to the public domain
 worldwide. This software is distributed without any warranty.

 See <http://creativecommons.org/publicdomain/zero/1.0/>. */

#include <R.h>
#include <Rinternals.h>
#include <stdint.h>

/* This is a fixed-increment version of Java 8's SplittableRandom generator
 See http://dx.doi.org/10.1145/2714064.2660195 and
 http://docs.oracle.com/javase/8/docs/api/java/util/SplittableRandom.html

 It is a very fast generator passing BigCrush, and it can be useful if
 for some reason you absolutely want 64 bits of state. */

// Source code adapted from: http://xorshift.di.unimi.it/splitmix64.c

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// PRNG State
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static uint64_t splitmix64_state; /* The state can be seeded with any value. */


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Set a seed
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP set_seed_splitmix64_(SEXP seedlo, SEXP seedhi) {

  splitmix64_state = asInteger(seedlo) + ((uint64_t)asInteger(seedhi) << 32);

  return R_NilValue;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Original PRNG
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uint64_t next_splitmix64() {
  uint64_t z = (splitmix64_state += 0x9e3779b97f4a7c15);
  z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
  z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
  return z ^ (z >> 31);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Calculate a splitmix64 random uin64 using the given index.
// This does *NOT* affect global state of PRNG.
// Use this with a seed to bootstrap the seeds of other PRNGs
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uint64_t runif1_splitmix64_stateless(uint64_t index) {
  uint64_t z = (index += 0x9e3779b97f4a7c15);
  z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
  z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
  return z ^ (z >> 31);
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// get state
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP get_state_splitmix64_(void) {

  SEXP bytes = PROTECT(allocVector(RAWSXP, 8));
  void *pbytes = (void *)RAW(bytes);

  memcpy(pbytes, &splitmix64_state, 8);

  UNPROTECT(1);
  return(bytes);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// set state
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP set_state_splitmix64_(SEXP state_) {

  void *values = (void *)RAW(state_);

  memcpy(&splitmix64_state, values, 8);

  return R_NilValue;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// C function callable from R to generate single random number in [0,1]
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP runif1_splitmix64_() {
  uint64_t z = (splitmix64_state += 0x9e3779b97f4a7c15);
  z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
  z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
  uint64_t result = z ^ (z >> 31);

  double result_double = (result >> 11) * 0x1.0p-53;

  return ScalarReal(result_double);
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// C function callable from R to generate multiple random numbers in [0,1]
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP runif_splitmix64_(SEXP n_, SEXP min_, SEXP max_) {

  int n = asInteger(n_);
  double dmin = asReal(min_);
  double dmax = asReal(max_);
  double drange = dmax - dmin;

  SEXP dbl_vec = PROTECT(allocVector(REALSXP, n));
  double *dbl_ptr = REAL(dbl_vec);


  for (int i = 0; i < n; i++) {
    uint64_t z = (splitmix64_state += 0x9e3779b97f4a7c15);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
    z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
    uint64_t result = z ^ (z >> 31);

    *dbl_ptr++ = (result >> 11) * 0x1.0p-53 * drange + dmin;
  }

  UNPROTECT(1);
  return dbl_vec;
}






//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// C function callable from R to generate multiple random numbers in [0,1]
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP runif_splitmix64_as_bytes_(SEXP n_, SEXP min_, SEXP max_) {

  int n = asInteger(n_);
  double dmin = asReal(min_);
  double dmax = asReal(max_);
  double drange = dmax - dmin;

  SEXP raw_vec = PROTECT(allocVector(RAWSXP, n * 8));
  double *dbl_ptr = (double *)RAW(raw_vec);


  for (int i = 0; i < n; i++) {
    uint64_t z = (splitmix64_state += 0x9e3779b97f4a7c15);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
    z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
    uint64_t result = z ^ (z >> 31);

    *dbl_ptr++ = (result >> 11) * 0x1.0p-53 * drange + dmin;
  }

  UNPROTECT(1);
  return raw_vec;
}






