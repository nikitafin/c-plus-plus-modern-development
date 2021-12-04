#include <vector>

#include "test_runner.h"

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template <typename Token>
using Sentence = std::vector<Token>;

// Класс Token имеет метод bool IsEndSentencePunctuation() const
template <typename Token>
std::vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
  // Напишите реализацию функции, не копируя объекты типа Token
}

struct TestToken {
  std::string data;
  bool is_end_sentence_punctuation = false;

  bool IsEndSentencePunctuation() const { return is_end_sentence_punctuation; }
  bool operator==(const TestToken& other) const {
    return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
  }
};

std::ostream& operator<<(std::ostream& stream, const TestToken& token) { return stream << token.data; }

// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void TestSplitting() {
  ASSERT_EQUAL(SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
               vector<Sentence<TestToken>>({{{"Split"}, {"into"}, {"sentences"}, {"!"}}}));

  ASSERT_EQUAL(SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
               vector<Sentence<TestToken>>({{{"Split"}, {"into"}, {"sentences"}, {"!", true}}}));

  ASSERT_EQUAL(
      SplitIntoSentences(vector<TestToken>(
          {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
      vector<Sentence<TestToken>>({
          {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
          {{"Without"}, {"copies"}, {".", true}},
      }));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSplitting);
  return 0;
}
