
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# onLoad set a seed for all the generators.
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
.onLoad <- function(...) {
  if (exists('set_seed_xoshiro256p_')) {
    set_seed_xoshiro256p(stats::runif(1) * 2^31, stats::runif(1) * 2^31)
    set_seed_lehmer64   (stats::runif(1) * 2^31, stats::runif(1) * 2^31)
    set_seed_splitmix64 (stats::runif(1) * 2^31, stats::runif(1) * 2^31)
    set_seed_romutrio   (stats::runif(1) * 2^31, stats::runif(1) * 2^31)
  }
}


.onUnload <- function (libpath) {
  library.dynam.unload("miranda", libpath)
}
