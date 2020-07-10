


test_that("state get/set works", {

  state <- get_state_lehmer64()
  nums   <- runif_lehmer64(10)
  set_state_lehmer64(state)
  expect_identical(nums, runif_lehmer64(10))

  state <- get_state_romutrio()
  nums   <- runif_romutrio(10)
  set_state_romutrio(state)
  expect_identical(nums, runif_romutrio(10))

  state <- get_state_splitmix64()
  nums   <- runif_splitmix64(10)
  set_state_splitmix64(state)
  expect_identical(nums, runif_splitmix64(10))

  state <- get_state_xoshiro256p()
  nums   <- runif_xoshiro256p(10)
  set_state_xoshiro256p(state)
  expect_identical(nums, runif_xoshiro256p(10))
})
