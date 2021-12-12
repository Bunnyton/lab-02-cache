// Copyright 2021 Galaktionov Andrey <galaktionovaa@student.bmstu.ru>

#ifndef INCLUDE_CACHE_TEST_HPP_
#define INCLUDE_CACHE_TEST_HPP_

#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>

#define LOT_OF_TYPE 3
#define STEP 16
#define COEFFICIENT 1024

enum Move_type { right_type = 0, reverse_type = 1, random_type = 2 };
typedef enum Move_type move_type;

std::vector<unsigned> buffer_size(std::vector<unsigned>& cache_size);

unsigned* set_of_test(unsign3ed buff_size, move_type t, unsigned lot_of_iter);

unsigned* make_array(unsigned buff_size);

void result_out(move_type t, unsigned number,
                std::vector<unsigned>& buffer_size, clock_t duration,
                std::ostream& os);

void cache_test(std::vector<unsigned>& cache_size, unsigned lot_of_iter,
                std::ostream& os);

#endif  // INCLUDE_CACHE_TEST_HPP_
