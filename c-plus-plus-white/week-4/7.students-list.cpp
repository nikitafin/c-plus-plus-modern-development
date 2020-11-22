#include <iostream>
#include <vector>

struct Student {
  std::string firstName;
  std::string lastName;
  int day;
  int month;
  int year;
};

int main() {
  int studentsCount = 0;
  std::cin >> studentsCount;

  std::vector<Student> students(studentsCount);
  for (auto &student : students) {
    std::cin >> student.firstName >> student.lastName >> student.day >> student.month >> student.year;
  }

  int cmdCount = 0;
  std::cin >> cmdCount;
  for (int i = 0; i < cmdCount; ++i) {
    std::string cmd;
    int studentNumber;
    std::cin >> cmd >> studentNumber;
    if ((cmd != "name" and cmd != "date") or studentNumber > studentsCount or studentNumber < 1) {
      std::cout << "bad request" << std::endl;
    } else if (cmd == "name") {
      std::cout << students[studentNumber - 1].firstName << " " << students[studentNumber - 1].lastName << std::endl;
    } else if (cmd == "date") {
      std::cout << students[studentNumber - 1].day << "." << students[studentNumber - 1].month << "."
                << students[studentNumber - 1].year << std::endl;
    }

  }

  return 0;
}