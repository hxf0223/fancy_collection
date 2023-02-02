#include <cassert>
#include <iostream>
#include <vector>

#include "catch.hpp"
#include "nadeau.h"

void print_pages() {
  static size_t pagesize = sysconf(_SC_PAGESIZE);
  int64_t bytes = getCurrentRSS();
  assert((bytes % pagesize) == 0);
  size_t pages = bytes / pagesize;
  std::cout << "page size: " << pagesize << "\t";
  std::cout << "bytes: " << bytes << "\t";
  std::cout << "pages: " << pages << std::endl;
}

TEST_CASE("print process memory usage") {
  print_pages();
  std::vector<uint8_t> v1(10);
  print_pages();
  std::vector<uint8_t> v2(1000000);
  print_pages();
  std::vector<uint8_t> v3;
  v3.reserve(1000000000);
  print_pages();
}
