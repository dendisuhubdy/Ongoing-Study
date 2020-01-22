#include <iostream>

#include "filter_cpp.h"


int main(void) {
  valarray<double> x{
      1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4,
      2.6, 2.8, 3.0, 3.2, 3.4, 3.6, 3.8, 4.0,
  };

  valarray<double> b(0.2, 5);
  valarray<double> a{ 1.0 };

  valarray<double> z{ 0.0 };

  auto result = Filter(b, a, x, z);

  for (auto v : result.filteredSignal)
      std::cout << v << std::endl;

  return 0;
}
