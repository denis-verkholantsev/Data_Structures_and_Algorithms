#include <iostream>

long long partition(int n, int k);

int main() {
  int n = 0;
  int k = 0;
  std::cin >> n >> k;
  std::cout << partition(n, k);
  return 0;
}

long long partition(int n, int k) {
  if (k > n) {
    return 0;
  }
  if (k == n || k == 1) {
    return 1;
  }
  long long** table = new long long*[2];
  table[0] = new long long[n];
  table[1] = new long long[n];
  for (int i = 0; i < n; ++i) {
    table[0][i] = 1;
  }
  int shift = 0;
  do {
    ++shift;
    table[1][shift] = 1;
    for (int i = shift + 1; i < n; ++i) {
      table[1][i] = table[0][i - 1] +
                    (shift + 1 > i - shift ? 0 : table[1][i - shift - 1]);
    }
    std::swap(table[0], table[1]);
  } while (shift != k - 1);
  long long result = table[0][n - 1];
  delete[] table[0];
  delete[] table[1];
  delete[] table;
  return result;
}