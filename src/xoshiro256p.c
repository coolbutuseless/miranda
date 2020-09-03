/*  Written in 2018 by David Blackman and Sebastiano Vigna (vigna@acm.org)

 To the extent possible under law, the author has dedicated all copyright
 and related and neighboring rights to this software to the public domain
 worldwide. This software is distributed without any warranty.

 See <http://creativecommons.org/publicdomain/zero/1.0/>. */

#include <R.h>
#include <Rinternals.h>
#include <stdint.h>

#include "splitmix64.h"

/* This is xoshiro256+ 1.0, our best and fastest generator for floating-point
 numbers. We suggest to use its upper bits for floating-point
 generation, as it is slightly faster than xoshiro256++/xoshiro256**. It
 passes all tests we are aware of except for the lowest three bits,
 which might fail linearity tests (and just those), so if low linear
 complexity is not considered an issue (as it is usually the case) it
 can be used to generate 64-bit outputs, too.

 We suggest to use a sign test to extract a random Boolean value, and
 right shifts to extract subsets of bits.

 The state must be seeded so that it is not everywhere zero. If you have
 a 64-bit seed, we suggest to seed a splitmix64 generator and use its
 output to fill s. */


static inline uint64_t rotl(const uint64_t x, int k) {
  return (x << k) | (x >> (64 - k));
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// PRNG State
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static uint64_t xoshiro256p_state[4];

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Original PRNG
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uint64_t next_xoshiro256p(void) {
  const uint64_t result = xoshiro256p_state[0] + xoshiro256p_state[3];

  const uint64_t t = xoshiro256p_state[1] << 17;

  xoshiro256p_state[2] ^= xoshiro256p_state[0];
  xoshiro256p_state[3] ^= xoshiro256p_state[1];
  xoshiro256p_state[1] ^= xoshiro256p_state[2];
  xoshiro256p_state[0] ^= xoshiro256p_state[3];

  xoshiro256p_state[2] ^= t;

  xoshiro256p_state[3] = rotl(xoshiro256p_state[3], 45);

  return result;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// get state
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP get_state_xoshiro256p_(void) {

  SEXP bytes = PROTECT(allocVector(RAWSXP, 32));
  void *pbytes = (void *)RAW(bytes);

  memcpy(pbytes, &xoshiro256p_state, 32);

  UNPROTECT(1);
  return(bytes);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// set state
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP set_state_xoshiro256p_(SEXP state_) {

  void *values = (void *)RAW(state_);

  memcpy(&xoshiro256p_state, values, 32);

  return R_NilValue;
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Set a seed
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP set_seed_xoshiro256p_(SEXP seedlo, SEXP seedhi) {

  uint64_t index = asInteger(seedlo) + ((uint64_t)asInteger(seedhi) << 32);

  xoshiro256p_state[0] = runif1_splitmix64_stateless(index + 0);
  xoshiro256p_state[1] = runif1_splitmix64_stateless(index + 1);
  xoshiro256p_state[2] = runif1_splitmix64_stateless(index + 2);
  xoshiro256p_state[3] = runif1_splitmix64_stateless(index + 3);

  return R_NilValue;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// C function callable from R to generate single random number in [0,1]
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP runif1_xoshiro256p_(void) {
  const uint64_t result = rotl(xoshiro256p_state[0] + xoshiro256p_state[3], 23) + xoshiro256p_state[0];

  const uint64_t t = xoshiro256p_state[1] << 17;

  xoshiro256p_state[2] ^= xoshiro256p_state[0];
  xoshiro256p_state[3] ^= xoshiro256p_state[1];
  xoshiro256p_state[1] ^= xoshiro256p_state[2];
  xoshiro256p_state[0] ^= xoshiro256p_state[3];

  xoshiro256p_state[2] ^= t;

  xoshiro256p_state[3] = rotl(xoshiro256p_state[3], 45);

  double result_double = (result >> 11) * 0x1.0p-53;

  return ScalarReal(result_double);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// C function callable from R to generate multiple random numbers in [0,1]
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP runif_xoshiro256p_(SEXP n_, SEXP min_, SEXP max_) {

  int n = asInteger(n_);
  double dmin = asReal(min_);
  double dmax = asReal(max_);
  double drange = dmax - dmin;

  SEXP dbl_vec = PROTECT(allocVector(REALSXP, n));
  double *dbl_ptr = REAL(dbl_vec);

  for (int i = 0; i < n; i++) {
    uint64_t result = rotl(xoshiro256p_state[0] + xoshiro256p_state[3], 23) + xoshiro256p_state[0];
    const uint64_t t = xoshiro256p_state[1] << 17;

    xoshiro256p_state[2] ^= xoshiro256p_state[0];
    xoshiro256p_state[3] ^= xoshiro256p_state[1];
    xoshiro256p_state[1] ^= xoshiro256p_state[2];
    xoshiro256p_state[0] ^= xoshiro256p_state[3];

    xoshiro256p_state[2] ^= t;

    xoshiro256p_state[3] = rotl(xoshiro256p_state[3], 45);

    *dbl_ptr++ = (result >> 11) * 0x1.0p-53 * drange + dmin;
  }

  UNPROTECT(1);
  return dbl_vec;
}



/* This is the jump function for the generator. It is equivalent
 to 2^128 calls to next(); it can be used to generate 2^128
 non-overlapping subsequences for parallel computations. */

SEXP jump_xoshiro256p_(void) {
  static const uint64_t JUMP[] = { 0x180ec6d33cfd0aba, 0xd5a61266f0c9392c, 0xa9582618e03fc9aa, 0x39abdc4529b1661c };

  uint64_t s0 = 0;
  uint64_t s1 = 0;
  uint64_t s2 = 0;
  uint64_t s3 = 0;
  for(int i = 0; i < sizeof JUMP / sizeof *JUMP; i++) {
    for(int b = 0; b < 64; b++) {
      if (JUMP[i] & UINT64_C(1) << b) {
        s0 ^= xoshiro256p_state[0];
        s1 ^= xoshiro256p_state[1];
        s2 ^= xoshiro256p_state[2];
        s3 ^= xoshiro256p_state[3];
      }
      next_xoshiro256p();
    }
  }

  xoshiro256p_state[0] = s0;
  xoshiro256p_state[1] = s1;
  xoshiro256p_state[2] = s2;
  xoshiro256p_state[3] = s3;

  return R_NilValue;
}


/* This is the long-jump function for the generator. It is equivalent to
 2^192 calls to next(); it can be used to generate 2^64 starting points,
 from each of which jump() will generate 2^64 non-overlapping
 subsequences for parallel distributed computations. */

SEXP long_jump_xoshiro256p_(void) {
  static const uint64_t LONG_JUMP[] = { 0x76e15d3efefdcbbf, 0xc5004e441c522fb3, 0x77710069854ee241, 0x39109bb02acbe635 };

  uint64_t s0 = 0;
  uint64_t s1 = 0;
  uint64_t s2 = 0;
  uint64_t s3 = 0;
  for(int i = 0; i < sizeof LONG_JUMP / sizeof *LONG_JUMP; i++) {
    for(int b = 0; b < 64; b++) {
      if (LONG_JUMP[i] & UINT64_C(1) << b) {
        s0 ^= xoshiro256p_state[0];
        s1 ^= xoshiro256p_state[1];
        s2 ^= xoshiro256p_state[2];
        s3 ^= xoshiro256p_state[3];
      }
      next_xoshiro256p();
    }
  }

  xoshiro256p_state[0] = s0;
  xoshiro256p_state[1] = s1;
  xoshiro256p_state[2] = s2;
  xoshiro256p_state[3] = s3;

  return R_NilValue;
}
