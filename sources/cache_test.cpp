// Copyright 2021 Galaktionov Andrey <galaktionovaa@student.bmstu.ru>

#include "cache_test.hpp"

#include <random>

std::vector<unsigned> buffer_size(std::vector<unsigned>& cache_size) {
  std::vector<unsigned> buff_size;

  unsigned helper = cache_size.front() / 2;
  while (helper < 3 * cache_size.back() / 2) {
    buff_size.push_back(helper);
    helper *= 2;
  }
  return buff_size;
}

unsigned* set_of_test(unsigned buff_size, move_type t, unsigned lot_of_iter) {
  if (buff_size == 0) return nullptr;

  unsigned lot_of_elements =
      (buff_size * K / sizeof(unsigned)) / STEP;  // buff size in kib
  if (lot_of_elements == 0) return nullptr;

  auto* set_of_elements = new unsigned[lot_of_elements];
  auto* test_arr = new unsigned[lot_of_iter];

  unsigned helper = 0;

  if (t == right_type) {
    for (unsigned i = 0; i < lot_of_elements; ++i) {
      set_of_elements[i] = helper;
      helper += STEP;
    }
  } else {
    helper = 0;
    for (unsigned i = lot_of_elements; i > 0; --i) {
      set_of_elements[i - 1] = helper;
      helper += STEP;
    }
  }

  unsigned j;
  for (unsigned i = 0; i < lot_of_iter; ++i) {
    j = i % lot_of_elements;
    test_arr[i] = set_of_elements[j];
  }

  if (t == random_type)
    std::shuffle(test_arr, test_arr - 1 + lot_of_iter,
                 std::mt19937(std::random_device()()));

  delete[] set_of_elements;
  return test_arr;
}

unsigned* make_array(unsigned buff_size) {
  auto* arr =
      new unsigned[buff_size * K / sizeof(unsigned)];  // buff size in kib
  return arr;
}

void result_out(move_type t, unsigned number,
                std::vector<unsigned>& buffer_size, clock_t duration,
                std::ostream& os) {
  if (number == 0) {
    os << "investigation:" << std::endl << "  travel_variant: ";
    switch (t) {
      case right_type:
        os << "right";
        break;
      case reverse_type:
        os << "reverse";
        break;
      case random_type:
        os << "random";
    }
    os << std::endl << "  experiments:" << std::endl;
  }
  os << "  - experiment:" << std::endl
     << "      number: " << number + 1 << std::endl
     << "      input_data:" << std::endl
     << "        buffer_size: " << buffer_size.at(number) << "kib" << std::endl
     << "      results:" << std::endl
     << "        duration: " << duration * 1000000000 / CLOCKS_PER_SEC << "ns"
     << std::endl
     << std::endl;
}

void cache_test(std::vector<unsigned>& cache_size, unsigned lot_of_iter,
                std::ostream& os) {
  std::vector<unsigned> buff_size = buffer_size(cache_size);

  [[maybe_unused]] unsigned helper = 0;
  clock_t start = 0;
  clock_t end = 0;
  for (unsigned i = 0; i < LOT_OF_TYPE; ++i) {
    for (unsigned j = 0; j < buff_size.size(); ++j) {
      [[maybe_unused]] unsigned* set =
          set_of_test(buff_size.at(j), (move_type)i, lot_of_iter);
      if (set == nullptr) {
        result_out((move_type)i, j, buff_size, 0, os);
        continue;
      }
      [[maybe_unused]] unsigned* arr = make_array(buff_size.at(j));
      if (arr == nullptr) throw(std::errc::not_enough_memory);

      for (unsigned k = 0; k < lot_of_iter; ++k)
        helper = arr[set[k]];  // warm up

      start = clock();
      for (unsigned k = 0; k < lot_of_iter; ++k) helper = arr[set[k]];
      end = clock();

      result_out((move_type)i, j, buff_size, end - start, os);

      delete[] set;
      delete[] arr;
    }
  }

  std::destroy(buff_size.begin(), buff_size.end());
}
