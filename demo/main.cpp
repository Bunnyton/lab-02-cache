#include "cache_test.hpp"

int main() {
  std::vector<unsigned> cache_size;
  cache_size.push_back(128);
  cache_size.push_back(2048);
  cache_test(cache_size, 1000, std::cout);
}