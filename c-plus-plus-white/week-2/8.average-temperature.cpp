#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int average(const std::vector<int> &nums) {
  int sum = std::accumulate(nums.begin(), nums.end(), 0);
  return sum / nums.size();
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> nums(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> nums[i];
  }
  int avr = average(nums);
  std::vector<int> result;
  for (int i = 0; i < n; ++i) {
    if (nums[i] > avr) {
      result.push_back(i);
    }
  }
  std::cout << result.size() << std::endl;
  for (const auto &elem : result) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;

  return 0;
}