

test_that("package load initialises state", {

  # The chances of there being multiple zero bytes is pretty darn low.
  # The most probable reason for their appearance is if the seed is not
  # setting the state correctly
  expect_true(sum(get_state_lehmer64()    == raw(1)) <= 4)
  expect_true(sum(get_state_romutrio()    == raw(1)) <= 4)
  expect_true(sum(get_state_splitmix64()  == raw(1)) <= 4)
  expect_true(sum(get_state_xoshiro256p() == raw(1)) <= 4)
})
