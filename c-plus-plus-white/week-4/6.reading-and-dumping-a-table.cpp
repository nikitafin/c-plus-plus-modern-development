#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

int
main() {
  std::ifstream inputFile("input.txt");
  if (inputFile.is_open()) {
    int rowCount, columnCount;
    inputFile >> rowCount >> columnCount;
    for (int i = 0; i < rowCount; ++i) {
      int temp;
      for (int j = 0; j < columnCount; ++j) {
        // get num
        inputFile >> temp;
        std::cout << std::setw(10) << temp;
        if (j != columnCount - 1) {
          std::cout << " ";
        }
        // skip delimiter
        inputFile.ignore(1);
      }
      if (i != rowCount - 1) {
        std::cout << std::endl;
      }
    }
  }
  return 0;
}