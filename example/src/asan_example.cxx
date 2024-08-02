#include <print>

int main(int argc, char **argv) {
  int *array = new int[100];
  delete[] array;

  auto const boom_value = array[argc];  // BOOM

  std::println("No Boom. Use ASan");
  std::println("Programm {}", argv[0]);

  return boom_value;
}
