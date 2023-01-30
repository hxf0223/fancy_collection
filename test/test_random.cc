#include <ostream>
#include <vector>

#include "effolkronium/random.hpp"
#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
                          // in one cpp file
#include "catch.hpp"

using Random = effolkronium::random_static;

namespace {

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
  os << "(size " << v.size() << ") [";
  for (const auto& e : v) {
    os << e << ", ";
  }
  os << "]";
  return os;
}

} // namespace

// demo random's usage with vector
TEST_CASE("vector random") {
  auto rnd_vec = Random::get<std::vector>(1, 100, 32); // get random vector size 32, random value range 1 ~ 100
  std::cout << rnd_vec << std::endl;
}
