#include "utils.hpp"

#include <fstream>

std::optional<std::string> ember::readFile(std::filesystem::path path) {
  std::ifstream f(path);

  if (!f.is_open()) {
    return {};
  }

  f.seekg(0, std::ios::end);
  auto size = f.tellg();
  std::string buffer(size, ' ');
  f.seekg(0);
  f.read(&buffer[0], size);

  return buffer;
}

uint64_t ember::binomialCoefficient(int n, int k) {
  if (k > n) return 0;
  if (k == 0 || k == n) return 1;

  // Since C(n, k) = C(n, n-k)
  if (k > n - k) k = n - k;

  unsigned long long result = 1;
  for (int i = 0; i < k; ++i) {
    result *= (n - i);
    result /= (i + 1);
  }
  return result;
}