#include <iomanip>
#include <iostream>

int main(int argc, char **argv) {
  int *array = new int[100]; // NOLINT
  delete[] array;

  auto const boom_value = array[argc];  // BOOM

  std::cout << "No Boom. Use ASan";
  std::cout << "Programm " << std::quoted(argv[0]);

  return boom_value;
}
