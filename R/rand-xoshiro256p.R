

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname get_state_splitmix64
#' @useDynLib miranda get_state_xoshiro256p_
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
get_state_xoshiro256p <- function() {
  .Call(get_state_xoshiro256p_)
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname set_state_splitmix64
#' @useDynLib miranda set_state_xoshiro256p_
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set_state_xoshiro256p <- function(state) {
  stopifnot(is.raw(state), length(state) == 32L)
  invisible(.Call(set_state_xoshiro256p_, state))
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname set_seed_splitmix64
#' @useDynLib miranda set_seed_xoshiro256p_
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set_seed_xoshiro256p <- function(seedlo, seedhi = 524287L) {
  stopifnot(length(seedlo) == 1)
  stopifnot(length(seedhi) == 1)
  invisible(.Call(set_seed_xoshiro256p_, as.integer(seedlo), as.integer(seedhi)))
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname runif1_splitmix64
#' @useDynLib miranda runif1_xoshiro256p_
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
runif1_xoshiro256p <- function() {
  .Call(runif1_xoshiro256p_)
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname runif_splitmix64
#' @useDynLib miranda runif_xoshiro256p_
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
runif_xoshiro256p <- function(n, min=0, max=1) {
  .Call(runif_xoshiro256p_, as.integer(n), min, max)
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' This is the jump function for the generator. It is equivalent
#' to 2^128 calls to next(); it can be used to generate 2^128
#' non-overlapping subsequences for parallel computations.
#'
#' @useDynLib miranda jump_xoshiro256p_
#'
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
jump_xoshiro256p <- function() {
  invisible(.Call(jump_xoshiro256p_))
}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' This is the long-jump function for the generator. It is equivalent to
#' 2^192 calls to next(); it can be used to generate 2^64 starting points,
#' from each of which jump() will generate 2^64 non-overlapping
#' subsequences for parallel distributed computations.
#'
#' @useDynLib miranda long_jump_xoshiro256p_
#'
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
long_jump_xoshiro256p <- function() {
  invisible(.Call(long_jump_xoshiro256p_))
}

