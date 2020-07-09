
// #define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Reference:
// https://stackoverflow.com/questions/42313373/r-cmd-check-note-found-no-calls-to-r-registerroutines-r-usedynamicsymbols#42339658
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void R_init_miranda(DllInfo *info) {
 R_registerRoutines(info, NULL, NULL, NULL, NULL);
 R_useDynamicSymbols(info, TRUE);
}

