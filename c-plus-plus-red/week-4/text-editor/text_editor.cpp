#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "modernize-use-nodiscard"

#include <string>
#include <list>

#include "test_runner.h"

class Editor {
public:
  Editor() = default;

  void Left() {
    if (cursor != text.begin()) {
      cursor = std::prev(cursor);
      --position;
    }
  }

  void Right() {
    if (cursor != text.end()) {
      cursor = std::next(cursor);
      ++position;
    }
  }

  void Insert(char token) {
    text.insert(cursor, token);
    ++position;
  }

  void Cut(size_t tokens = 1U) {
    buffer.clear();
    if (tokens == 0U) {
      return;
    }

    std::size_t maxTokens = std::min(tokens, text.size() - position);

    auto newCursor = std::next(cursor, maxTokens);
    buffer.splice(buffer.begin(), text, cursor, newCursor);
    cursor = newCursor;
  }

  void Copy(size_t tokens = 1U) {
    buffer.clear();
    if (tokens == 0U) {
      return;
    }

    std::size_t maxTokens = std::min(tokens, text.size() - position);

    auto newCursor = std::next(cursor, maxTokens);
    buffer.insert(buffer.begin(), cursor, newCursor);
    cursor = newCursor;
  }

  void Paste() {
    text.insert(cursor, buffer.begin(), buffer.end());
    position += buffer.size();
  }

  std::string GetText() const {
    std::string textToReturn;
    textToReturn.reserve(text.size());
    for (const char &c: text) {
      textToReturn.push_back(c);
    }
    return textToReturn;
  }

private:
  std::list<char> text;
  std::list<char> buffer;
  std::list<char>::iterator cursor{text.begin()};
  std::list<char>::size_type position{0U};
};

void TypeText(Editor &editor, const std::string &text) {
  for (char c: text) {
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

    ASSERT_EQUAL(editor.GetText(), "world, hello")
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

    ASSERT_EQUAL(editor.GetText(), "misprint")
  }
}

void TestReverse() {
  Editor editor;

  const std::string text = "esreveR";
  for (char c: text) {
    editor.Insert(c);
    editor.Left();
  }

  ASSERT_EQUAL(editor.GetText(), "Reverse")
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "")

  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "")
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

  ASSERT_EQUAL(editor.GetText(), "example")
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
}

#pragma clang diagnostic pop