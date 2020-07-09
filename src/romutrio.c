
// Romu Pseudorandom Number Generators
//
// Copyright 2020 Mark A. Overton
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// ------------------------------------------------------------------------------------------------
//
// Website: romu-random.org
// Paper:   http://arxiv.org/abs/2002.11331
//
// Copy and paste the generator you want from those below.
// To compile, you will need to #include <stdint.h> and use the ROTL definition below.

#include <R.h>
#include <Rinternals.h>
#include <stdint.h>
#include "splitmix64.h"

#define ROTL(d,lrot) ((d<<(lrot)) | (d>>(8*sizeof(d)-(lrot))))


//===== RomuTrio ==================================================================================
//
// Great for general purpose work, including huge jobs.
// Est. capacity = 2^75 bytes. Register pressure = 6. State size = 192 bits.


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// PRNG State
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static uint64_t romutrio_state_x, romutrio_state_y, romutrio_state_z;  // set to nonzero seed



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Original PRNG
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// uint64_t romuTrio_random () {
//   uint64_t xp = romutrio_state_x, yp = romutrio_state_y, zp = romutrio_state_z;
//   romutrio_state_x = 15241094284759029579u * zp;
//   romutrio_state_y = yp - xp;  romutrio_state_y = ROTL(romutrio_state_y,12);
//   romutrio_state_z = zp - yp;  romutrio_state_z = ROTL(romutrio_state_z,44);
//   return xp;
// }


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Set a seed
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP set_seed_romutrio_(SEXP seedlo, SEXP seedhi) {

  uint64_t index = asInteger(seedlo) + ((uint64_t)asInteger(seedhi) << 32);

  romutrio_state_x = runif1_splitmix64_stateless(index + 0);
  romutrio_state_y = runif1_splitmix64_stateless(index + 1);
  romutrio_state_z = runif1_splitmix64_stateless(index + 2);

  return R_NilValue;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// get state
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP get_state_romutrio_(void) {

  SEXP bytes = PROTECT(allocVector(RAWSXP, 24));
  void *pbytes = (void *)RAW(bytes);

  memcpy(pbytes +  0, &romutrio_state_x, 8);
  memcpy(pbytes +  8, &romutrio_state_y, 8);
  memcpy(pbytes + 16, &romutrio_state_z, 8);

  UNPROTECT(1);
  return(bytes);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// set state
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP set_state_romutrio_(SEXP state_) {

  void *values = (void *)RAW(state_);

  memcpy(&romutrio_state_x, values +  0, 8);
  memcpy(&romutrio_state_y, values +  8, 8);
  memcpy(&romutrio_state_z, values + 16, 8);

  return R_NilValue;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// C function callable from R to generate single random number in [0,1]
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP runif1_romutrio_(void) {
  uint64_t xp = romutrio_state_x, yp = romutrio_state_y, zp = romutrio_state_z;
  romutrio_state_x = 15241094284759029579u * zp;
  romutrio_state_y = yp - xp;  romutrio_state_y = ROTL(romutrio_state_y,12);
  romutrio_state_z = zp - yp;  romutrio_state_z = ROTL(romutrio_state_z,44);

  double result_double = (xp >> 11) * 0x1.0p-53;

  return ScalarReal(result_double);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// C function callable from R to generate multiple random numbers in [0,1]
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SEXP runif_romutrio_(SEXP n_, SEXP min_, SEXP max_) {

  int n = asInteger(n_);
  double dmin = asReal(min_);
  double dmax = asReal(max_);
  double drange = dmax - dmin;

  SEXP dbl_vec = PROTECT(allocVector(REALSXP, n));
  double *dbl_ptr = REAL(dbl_vec);

  for (int i = 0; i < n; i++) {
    uint64_t xp = romutrio_state_x, yp = romutrio_state_y, zp = romutrio_state_z;
    romutrio_state_x = 15241094284759029579u * zp;
    romutrio_state_y = yp - xp;  romutrio_state_y = ROTL(romutrio_state_y,12);
    romutrio_state_z = zp - yp;  romutrio_state_z = ROTL(romutrio_state_z,44);

    *dbl_ptr++ = (xp >> 11) * 0x1.0p-53 * drange + dmin;
  }

  UNPROTECT(1);
  return dbl_vec;
}








