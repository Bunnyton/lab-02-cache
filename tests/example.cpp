// Copyright 2021 Galaktionov Andrey <galaktionovaa@student.bmstu.ru>

#include <stdexcept>
#include <gtest/gtest.h>

#include "cache_test.hpp"

TEST(Example, EmptyTest) {
    EXPECT_THROW(example(), std::runtime_error);
}
