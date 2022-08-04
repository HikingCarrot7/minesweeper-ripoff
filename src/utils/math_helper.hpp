#ifndef MATH_HELPER_H
#define MATH_HELPER_H

#include <random>

namespace MathHelper {
inline int randomInt(int min, int max) {
  std::random_device rand_dev;
  std::default_random_engine rand_eng(rand_dev());
  std::uniform_int_distribution<int> dis(min, max);

  return dis(rand_eng);
}
}  // namespace MathHelper

#endif
