
#' @useDynLib miranda, .registration=TRUE
NULL


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Get/set the internal state of the generator
#'
#' \itemize{
#' \item{splitmix64 - 8 raw bytes}
#' \item{xoshiro - 32 raw bytes}
#' \item{romutrio - 24 raw bytes}
#' \item{lehmer64 - 16 raw bytes}
#' }
#'
#' @return raw vector holding state
#'
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
get_state_splitmix64 <- function() {
  .Call(get_state_splitmix64_)
}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Set the internal state of generator
#'
#' \itemize{
#' \item{splitmix64 - 8 raw bytes}
#' \item{xoshiro - 32 raw bytes}
#' \item{romutrio - 24 raw bytes}
#' \item{lehmer64 - 16 raw bytes}
#' }
#'
#' @param state raw vector of length 8
#'
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set_state_splitmix64 <- function(state) {
  stopifnot(is.raw(state), length(state) == 8L)
  invisible(.Call(set_state_splitmix64_, state))
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Set PRNG seed
#'
#' @param seedlo,seedhi PRNG seeds need to be 64-bit unsigned integers - which
#'        aren't actually a type in R.  Instead allow user to pass in 2 32bit
#'        integers - \code{seedhi} will be shifted by 32bits to be the upper
#'        part of a reconstructed 64bit int within the C code.  Default for seedhi is
#'        524287L (6th mersenne prime) - no real justification for this choice.
#'        I think this counts as a Nothing-Up-My-Sleeve number.
#'
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set_seed_splitmix64 <- function(seedlo, seedhi = 524287L) {
  stopifnot(length(seedlo) == 1)
  stopifnot(length(seedhi) == 1)
  invisible(.Call(set_seed_splitmix64_, as.integer(seedlo), as.integer(seedhi)))
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Fetch single uniform random number
#'
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
runif1_splitmix64 <- function() {
  .Call(runif1_splitmix64_)
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' Generate a vector of uniform random numbers
#'
#' @param n Number of observations
#' @param min,max lower and upper limit.
#'
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
runif_splitmix64 <- function(n, min=0, max=1) {
  .Call(runif_splitmix64_, as.integer(n), min, max)
}




#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname runif_splitmix64
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
runif_splitmix64_as_bytes <- function(n, min=0, max=1) {
  .Call(runif_splitmix64_as_bytes_, as.integer(n), min, max)
}



