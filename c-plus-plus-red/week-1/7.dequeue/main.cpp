#include <vector>
#include <stdexcept>

template<typename type>
class Deque {
private:
  std::vector<type> front;
  std::vector<type> back;
public:
  Deque() : front{}, back{} {}

  bool Empty() const {
    return front.empty() and back.empty();
  }

  size_t Size() const {
    return front.size() + back.size();
  }

  type &operator[](size_t index) {
    if (index < front.size()) {
      return front[index];
    } else if (index - front.size() < back.size()) {
      return front[index - front.size()];
    } else {
      throw std::out_of_range("index out of range");
    }
  }

  type &operator[](size_t index) const {
    if (index < front.size()) {
      return front[index];
    } else if (index - front.size() < back.size()) {
      return front[index - front.size()];
    } else {
      throw std::out_of_range("index out of range");
    }
  }

  type &At(size_t index) {
    if (index < front.size()) {
      return front[index];
    } else if (index - front.size() < back.size()) {
      return front[index - front.size()];
    } else {
      throw std::out_of_range("index out of range");
    }
  }

  type &At(size_t index) const {
    if (index < front.size()) {
      return front[index];
    } else if (index - front.size() < back.size()) {
      return front[index - front.size()];
    } else {
      throw std::out_of_range("index out of range");
    }
  }

  type &Front() {
    if (!front.empty()) {
      return front.front();
    }
  }

  type &Front() const {
    if (!front.empty()) {
      return front.front();
    }
  }

  type &Back() {
    if (!back.empty()) {
      return back.back();
    }
  }

  type &Back() const {
    if (!back.empty()) {
      return back.back();
    }
  }

  void PushFront(type element) {
    front.push_back(element);
  }

  void PushBack(type element) {
    back.push_back(element);
  }
};

int main() {
  Deque<int> d;
  d.Back();
  d.Front();
  d.PushBack(10);
  auto a = d.Front();
  a = d.Back();

  return 0;
}