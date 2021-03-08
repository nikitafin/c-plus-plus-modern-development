#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <string>

#include "test_runner.h"
// using namespace std;

class Editor {
 private:
  std::list<char> text;
  std::list<char> buffer;
  std::list<char>::iterator cursorPosition;
  //  size_t cursorPosition;
  //  std::string text;
  //  std::string buffer;

  //  std::string::iterator cursorPosition;

 public:
  // Реализуйте конструктор по умолчанию и объявленные методы
  Editor() : text{}, buffer{}, cursorPosition{text.end()} {}

  void Left() {
    if (cursorPosition != text.begin()) {
      --cursorPosition;
    }
  }

  void Right() {
    if (cursorPosition != text.end()) {
      ++cursorPosition;
    }
  }

  void Insert(char token) {
    cursorPosition = text.insert(cursorPosition, token);
    ++cursorPosition;
  }

  void Cut(size_t tokens = 1) {
    if (tokens == 0) {
      buffer.clear();
    } else {
      size_t validLength =
          static_cast<size_t>(std::distance(cursorPosition, text.end()));

      buffer = {cursorPosition,
                std::next(cursorPosition, std::min(tokens, validLength))};
      cursorPosition =
          text.erase(cursorPosition,
                     std::next(cursorPosition, std::min(tokens, validLength)));
    }
  }

  void Copy(size_t tokens = 1) {
    if (tokens == 0) {
      buffer.clear();
    } else {
      buffer = {cursorPosition, std::next(cursorPosition, tokens)};
    }
  }

  void Paste() {
    cursorPosition = text.insert(cursorPosition, buffer.begin(), buffer.end());
    //    ++cursorPosition;
    //    text.splice(cursorPosition, buffer);

    cursorPosition = std::next(cursorPosition, buffer.size());
    //    text.insert(cursorPosition, buffer);
    //    cursorPosition += buffer.size();
  }

  std::string GetText() const { return {text.begin(), text.end()}; }
};

void TypeText(Editor& editor, const std::string& text) {
  for (char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;
    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for (size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);

    for (size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }

    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);

    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;

    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const std::string text = "esreveR";
  for (char c : text) {
    editor.Insert(c);
    editor.Left();
  }

  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");

  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
  return 0;
}
