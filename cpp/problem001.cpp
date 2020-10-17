/*
This problem was recently asked by Google.

Given a list of numbers and a number k, return whether any two numbers from the
list add up to k.

For example, given [10, 15, 3, 7] and k of 17, return true since 10 + 7 is 17.

Bonus: Can you do this in one pass?
*/

#include <iostream>
#include <unordered_set> // For std::unordered_set<T> (hash-maps)
#include <vector>        // For std::vector<T> (dynamic arrays)

// Overall complexity: O(n), where (n == arr.size()).
bool two_sum(const std::vector<int> &arr, const int target) {
  std::unordered_set<int> seen; // A set of numbers seen so far
  for (const int num : arr) {
    // If we've seen our 'corresponding number', return true.
    if (seen.count(target - num))
      return true;
    // Otherwise, continue and update our seen list.
    seen.insert(num);
  }
  // If we get to this point, we found no pairs, so return false
  return false;
}

int main() {
  assert(two_sum({}, 0) == false);     // Empty lists work
  assert(two_sum({2}, 4) == false);    // Doesn't take (2, 2) as a valid pair
  assert(two_sum({2, 3}, 5) == true);  // Small debuggable example
  assert(two_sum({2, 3}, 4) == false); // Small debuggable example
  assert(two_sum({10, 15, 3, 7}, 17) == true);  // Sample example
  assert(two_sum({11, 15, 3, 7}, 17) == false); // Sample example, modified
  std::cout << "Passed all test!" << std::endl;
}
