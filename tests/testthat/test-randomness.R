

test_that("ranomness not insanely bad", {
  N <- 1e6

  # this is really testing that the output is not mostly zeros.
  # all xeros could occur when seed/state not initialised correctly
  # cor() will also throw an error if all values are zero, which is nice.
  nums <- runif_romutrio(N)   ; expect_true(abs(cor(head(nums, -1), tail(nums, -1))) < 0.1)
  nums <- runif_splitmix64(N) ; expect_true(abs(cor(head(nums, -1), tail(nums, -1))) < 0.1)
  nums <- runif_xoshiro256p(N); expect_true(abs(cor(head(nums, -1), tail(nums, -1))) < 0.1)
  skip_on_os("windows")
  nums <- runif_lehmer64(N)   ; expect_true(abs(cor(head(nums, -1), tail(nums, -1))) < 0.1)
})
