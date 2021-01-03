#include <test_runner.h>

#include <sstream>
#include <string>

using namespace std;

class Logger {
public:
  explicit Logger(ostream &output_stream) : os(output_stream) {
  }

  void SetLogLine(bool value) { log_line = value; }
  void SetLogFile(bool value) { log_file = value; }

  void FileName(const std::string &new_file_name) { file_name = new_file_name; }
  void LineNum(int new_line_num) { line_num = new_line_num; }

  void Log(const string &message) {
    if (log_file and log_line) {
      os << file_name << ":" << line_num << " ";
    } else if (log_file and not log_line) {
      os << file_name << " ";
    } else if (not log_file and log_line) {
      os << "Line " << line_num << " ";
    }
    os << message << std::endl;
  }

private:
  ostream &os;
  std::string file_name;
  int line_num;
  bool log_line = false;
  bool log_file = false;
};

#define LOG(logger, message) { \
   logger.FileName(__FILE__);  \
   logger.LineNum(__LINE__);   \
   logger.Log(message);        \
}

void TestLog() {
#line 1 "logger.cpp"

  ostringstream logs;
  Logger l(logs);
  LOG(l, "hello");

  l.SetLogFile(true);
  LOG(l, "hello");

  l.SetLogLine(true);
  LOG(l, "hello");

  l.SetLogFile(false);
  LOG(l, "hello");

  string expected = "hello\n";
  expected += "logger.cpp hello\n";
  expected += "logger.cpp:10 hello\n";
  expected += "Line 13 hello\n";
  ASSERT_EQUAL(logs.str(), expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestLog);
}
