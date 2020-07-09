

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname get_state_splitmix64
#' @useDynLib miranda get_state_romutrio_
#' @return raw vector holding state
#'
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
get_state_romutrio <- function() {
  .Call(get_state_romutrio_)
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname set_state_splitmix64
#' @useDynLib miranda set_state_romutrio_
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set_state_romutrio <- function(state) {
  stopifnot(is.raw(state), length(state) == 24L)
  invisible(.Call(set_state_romutrio_, state))
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname set_seed_splitmix64
#' @useDynLib miranda set_seed_romutrio_
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set_seed_romutrio <- function(seedlo, seedhi = 524287L) {
  stopifnot(length(seedlo) == 1)
  stopifnot(length(seedhi) == 1)
  invisible(.Call(set_seed_romutrio_, as.integer(seedlo), as.integer(seedhi)))
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname runif1_splitmix64
#' @useDynLib miranda runif1_romutrio_
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
runif1_romutrio <- function() {
  .Call(runif1_romutrio_)
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#' @rdname runif_splitmix64
#' @useDynLib miranda runif_romutrio_
#' @export
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
runif_romutrio <- function(n, min=0, max=1) {
  .Call(runif_romutrio_, as.integer(n), min, max)
}

