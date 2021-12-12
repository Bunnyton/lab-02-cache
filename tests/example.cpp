// Copyright 2021 Galaktionov Andrey <galaktionovaa@student.bmstu.ru>

#include <gtest/gtest.h>

#include <stdexcept>

#include "cache_test.hpp"

TEST(Example, EmptyTest) {
  std::vector<unsigned> cache_size;
  cache_size.push_back(128);
  cache_size.push_back(2048);
  EXPECT_THROW(cache_test(cache_size, 1000, std::cout), std::runtime_error);
}
