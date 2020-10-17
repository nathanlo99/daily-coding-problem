/*
This problem was asked by Uber.

Given an array of integers, return a new array such that each element at index i
of the new array is the product of all the numbers in the original array except
the one at i.

For example, if our input was [1, 2, 3, 4, 5], the expected output would be
[120, 60, 40, 30, 24]. If our input was [3, 2, 1], the expected output would be
[2, 3, 6].

Follow-up: what if you can't use division?
*/

#include <iostream>
#include <vector>

std::vector<int> exclusive_prod(const std::vector<int> &arr) {
  const size_t n = arr.size();
  assert(n != 0); // The input array should never be empty

  // prefix_product[i] stores the product of arr[0], arr[1], ..., arr[i-1]
  std::vector<int> prefix_product(n);
  // suffix_product[i] stores the product of arr[i+1], arr[i+2], ..., arr[n-1]
  std::vector<int> suffix_product(n);

  prefix_product[0] = 1;
  for (size_t idx = 1; idx < n; ++idx) {
    prefix_product[idx] = prefix_product[idx - 1] * arr[idx - 1];
  }
  suffix_product[n - 1] = 1;
  for (size_t idx = n - 1; idx >= 1; --idx) {
    suffix_product[idx - 1] = suffix_product[idx] * arr[idx];
  }

  std::vector<int> result(n);
  for (size_t idx = 0; idx < n; ++idx) {
    result[idx] = prefix_product[idx] * suffix_product[idx];
  }
  return result;
}

int main() {
  // Single element array: check for out of bounds indexing, etc.
  assert(exclusive_prod({1}) == std::vector<int>({1}));
  // Small debuggable cases
  assert(exclusive_prod({1, 0}) == std::vector<int>({0, 1}));
  assert(exclusive_prod({1, 2, 4}) == std::vector<int>({8, 4, 2}));
  // Sample cases
  assert(exclusive_prod({1, 2, 3, 4, 5}) ==
         std::vector<int>({120, 60, 40, 30, 24}));
  assert(exclusive_prod({3, 2, 1}) == std::vector<int>({2, 3, 6}));
  std::cout << "All tests pass!" << std::endl;
}
