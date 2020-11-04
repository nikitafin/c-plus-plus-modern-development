#include <fstream>
#include <iostream>
#include <string>

#define part2

#ifdef part1
// 1st part
int main() {

  std::ifstream inputFile("input.txt");
  if (inputFile.is_open()) {
    std::string temp;
    while (std::getline(inputFile, temp)) {
      std::cout << temp << std::endl;
    }
  }

  return 0;
}
#else

int main() {
  std::ifstream inputFile("input.txt");
  std::ofstream outputFile("output.txt");
  if (inputFile.is_open() and outputFile.is_open()) {
    std::string temp;
    while (std::getline(inputFile, temp)) {
      outputFile << temp << std::endl;
    }
  }
}

#endif

