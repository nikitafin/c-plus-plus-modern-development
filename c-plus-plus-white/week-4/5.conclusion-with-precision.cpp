#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

int
main() {
  std::ifstream inputFile("input.txt");
  if (inputFile.is_open()) {
    double value;
    while (inputFile >> value) {
      std::cout << std::fixed << std::setprecision(3) << value << std::endl;
    }
  }

  return 0;
}