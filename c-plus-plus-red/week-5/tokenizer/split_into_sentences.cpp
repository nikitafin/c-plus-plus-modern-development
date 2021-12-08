#include <vector>
#include <algorithm>

#include "test_runner.h"

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template<typename Token>
using Sentence = std::vector<Token>;

// Класс Token имеет метод bool IsEndSentencePunctuation() const
template<typename Token>
std::vector<Sentence<Token>> SplitIntoSentences(std::vector<Token> tokens) {
  std::vector<Sentence<Token>> sentences;

  for (auto it = tokens.begin(); it != tokens.end();) {
    Sentence<Token> temp_sentence;
    auto punctuation_it = std::find_if(it, tokens.end(), [](auto &token) {
      return token.IsEndSentencePunctuation();
    });
    if (punctuation_it != tokens.end()) {
      punctuation_it = std::find_if(punctuation_it, tokens.end(), [](auto &token) {
        return !token.IsEndSentencePunctuation();
      });
    }
    for (; it != punctuation_it; ++it) {
      temp_sentence.push_back(std::move(*it));
    }
    sentences.push_back(std::move(temp_sentence));
  }

  return sentences;
}

struct TestToken {
  std::string data;
  bool is_end_sentence_punctuation = false;

  bool IsEndSentencePunctuation() const { return is_end_sentence_punctuation; }
  bool operator==(const TestToken &other) const {
    return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
  }
  TestToken &operator=(const TestToken &) = delete;
};

std::ostream &operator<<(std::ostream &stream, const TestToken &token) { return stream << token.data; }

// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void TestSplitting() {
  ASSERT_EQUAL(SplitIntoSentences(std::vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
               std::vector<Sentence<TestToken>>({{{"Split"}, {"into"}, {"sentences"}, {"!"}}}));

  ASSERT_EQUAL(SplitIntoSentences(std::vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
               std::vector<Sentence<TestToken>>({{{"Split"}, {"into"}, {"sentences"}, {"!", true}}}));

  ASSERT_EQUAL(
      SplitIntoSentences(std::vector<TestToken>(
          {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
      std::vector<Sentence<TestToken>>({
                                           {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
                                           {{"Without"}, {"copies"}, {".", true}},
                                       }));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSplitting);
  return 0;
}
