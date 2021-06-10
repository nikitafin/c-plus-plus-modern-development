#include "test_runner.h"
#include <sstream>
#include <string>

class Logger {
 public:
  explicit Logger(std::ostream &output_stream) : os_(output_stream) {
  }

  void SetLogLine(bool value) { log_line_ = value; }
  void SetLogFile(bool value) { log_file_ = value; }

  void Log(const std::string &message, int line, const char *file) {
    if (log_file_ and log_line_) {
      os_ << file << ":" << line << " ";
    } else if (log_file_) {
      os_ << file << " ";
    } else if (log_line_) {
      os_ << "Line " << line << " ";
    }

    os_ << message << std::endl;
  }

  void Log(const std::string &message) {
    if (log_file_ and log_line_) {
      os_ << __FILE__ << ":" << __LINE__ << " ";
    } else if (log_file_) {
      os_ << __FILE__ << " ";
    } else if (log_line_) {
      os_ << "Line " << __LINE__ << " ";
    }

    os_ << message << std::endl;
  }

 private:
  std::ostream &os_;
  bool log_line_ = false;
  bool log_file_ = false;
};

#define LOG(logger, message) logger.Log(message, __LINE__, __FILE__)

void TestLog() {
#line 1 "logger.cpp"

  std::ostringstream logs;
  Logger l(logs);
  LOG(l, "hello");

  l.SetLogFile(true);
  LOG(l, "hello");

  l.SetLogLine(true);
  LOG(l, "hello");

  l.SetLogFile(false);
  LOG(l, "hello");

  std::string expected = "hello\n";
  expected += "logger.cpp hello\n";
  expected += "logger.cpp:10 hello\n";
  expected += "Line 13 hello\n";
  ASSERT_EQUAL(logs.str(), expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestLog);
}
