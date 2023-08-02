#include <string>

struct Specialization {
  std::string value;
  explicit Specialization(const std::string &value) : value(value) {}
};
struct Course {
  std::string value;
  explicit Course(const std::string &value) : value(value) {}
};
struct Week {
  std::string value;
  explicit Week(const std::string &value) : value(value) {}
};

struct LectureTitle {
  std::string specialization;
  std::string course;
  std::string week;

  LectureTitle(Specialization sp, Course c, Week w)
      : specialization(sp.value), course(c.value), week(w.value) {}
};