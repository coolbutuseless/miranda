
// #define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Reference:
// https://stackoverflow.com/questions/42313373/r-cmd-check-note-found-no-calls-to-r-registerroutines-r-usedynamicsymbols#42339658
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//void R_init_miranda(DllInfo *info) {
// R_registerRoutines(info, NULL, NULL, NULL, NULL);
// R_useDynamicSymbols(info, TRUE);
//}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
extern SEXP  set_seed_lehmer64_();
extern SEXP get_state_lehmer64_();
extern SEXP set_state_lehmer64_();
extern SEXP    runif1_lehmer64_();
extern SEXP     runif_lehmer64_();

extern SEXP  set_seed_splitmix64_();
extern SEXP get_state_splitmix64_();
extern SEXP set_state_splitmix64_();
extern SEXP    runif1_splitmix64_();
extern SEXP     runif_splitmix64_();
extern SEXP     runif_splitmix64_as_bytes_();

extern SEXP  set_seed_romutrio_();
extern SEXP get_state_romutrio_();
extern SEXP set_state_romutrio_();
extern SEXP    runif1_romutrio_();
extern SEXP     runif_romutrio_();

extern SEXP  set_seed_xoshiro256p_();
extern SEXP get_state_xoshiro256p_();
extern SEXP set_state_xoshiro256p_();
extern SEXP    runif1_xoshiro256p_();
extern SEXP     runif_xoshiro256p_();
extern SEXP      jump_xoshiro256p_();
extern SEXP long_jump_xoshiro256p_();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// .C      R_CMethodDef
// .Call   R_CallMethodDef
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
static const R_CallMethodDef CEntries[] = {
  // name       pointer     Num args
  { "set_seed_lehmer64_", (DL_FUNC)  &set_seed_lehmer64_, 2},
  {"get_state_lehmer64_", (DL_FUNC) &get_state_lehmer64_, 0},
  {"set_state_lehmer64_", (DL_FUNC) &set_state_lehmer64_, 1},
  {   "runif1_lehmer64_", (DL_FUNC)    &runif1_lehmer64_, 0},
  {    "runif_lehmer64_", (DL_FUNC)     &runif_lehmer64_, 3},

  { "set_seed_splitmix64_"         , (DL_FUNC)  &set_seed_splitmix64_         , 2},
  {"get_state_splitmix64_"         , (DL_FUNC) &get_state_splitmix64_         , 0},
  {"set_state_splitmix64_"         , (DL_FUNC) &set_state_splitmix64_         , 1},
  {   "runif1_splitmix64_"         , (DL_FUNC)    &runif1_splitmix64_         , 0},
  {    "runif_splitmix64_"         , (DL_FUNC)     &runif_splitmix64_         , 3},
  {    "runif_splitmix64_as_bytes_", (DL_FUNC)     &runif_splitmix64_as_bytes_, 3},

  { "set_seed_romutrio_", (DL_FUNC)  &set_seed_romutrio_, 2},
  {"get_state_romutrio_", (DL_FUNC) &get_state_romutrio_, 0},
  {"set_state_romutrio_", (DL_FUNC) &set_state_romutrio_, 1},
  {   "runif1_romutrio_", (DL_FUNC)    &runif1_romutrio_, 0},
  {    "runif_romutrio_", (DL_FUNC)     &runif_romutrio_, 3},

  { "set_seed_xoshiro256p_", (DL_FUNC)  &set_seed_xoshiro256p_, 2},
  {"get_state_xoshiro256p_", (DL_FUNC) &get_state_xoshiro256p_, 0},
  {"set_state_xoshiro256p_", (DL_FUNC) &set_state_xoshiro256p_, 1},
  {   "runif1_xoshiro256p_", (DL_FUNC)    &runif1_xoshiro256p_, 0},
  {    "runif_xoshiro256p_", (DL_FUNC)     &runif_xoshiro256p_, 3},
  {     "jump_xoshiro256p_", (DL_FUNC)      &jump_xoshiro256p_, 0},
  {"long_jump_xoshiro256p_", (DL_FUNC) &long_jump_xoshiro256p_, 0},
  {NULL, NULL, 0}   // Placeholder(?) to indicate last one.
};


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Register the methods
//
// Change the '_simplecall' suffix to match your package name
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void R_init_miranda(DllInfo *info) {
  R_registerRoutines(
    info,      // DllInfo
    NULL,      // .C
    CEntries,  // .Call
    NULL,      // Fortran
    NULL       // External
  );
  R_useDynamicSymbols(info, FALSE);
}
