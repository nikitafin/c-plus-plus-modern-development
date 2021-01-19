#include <vector>
#include <stdexcept>

template<typename type>
class Deque {
private:
  std::vector<type> front;
  std::vector<type> back;
public:
  Deque() : front{}, back{} {}
  bool Empty() const;
  size_t Size() const;

  const type &operator[](size_t index) const;
  type &operator[](size_t index);

  const type &At(size_t index) const;
  type &At(size_t index);

  const type &Front() const;
  type &Front();

  const type &Back() const;
  type &Back();

  void PushFront(const type &element);
  void PushBack(const type &element);
};

template<typename type>
bool Deque<type>::Empty() const {
  return front.empty() and back.empty();
}
template<typename type>
size_t Deque<type>::Size() const {
  return front.size() + back.size();
}
template<typename type>
const type &Deque<type>::operator[](size_t index) const {
  if (index > front.size() - 1) {
    return back[index - front.size()];
  } else {
    return front[front.size() - 1 - index];
  }
}
template<typename type>
type &Deque<type>::operator[](size_t index) {
  return const_cast<type &>(
      static_cast<const Deque &>(*this)[index]
  );
}
template<typename type>
const type &Deque<type>::At(size_t index) const {
  if (index > front.size() - 1) {
    if (index > back.size()) {
      throw std::out_of_range("out of range");
    }
    return back[index - front.size()];
  } else {
    return front[front.size() - 1 - index];
  }
}
template<typename type>
type &Deque<type>::At(size_t index) {
  return const_cast<type &>(
      static_cast<const Deque &>(*this).At(index)
  );
}
template<typename type>
const type &Deque<type>::Front() const {
  return front.back();
}
template<typename type>
type &Deque<type>::Front() {
  return front.back();
}
template<typename type>
const type &Deque<type>::Back() const {
  return back.back();
}
template<typename type>
type &Deque<type>::Back() {
  return back.back();
}
template<typename type>
void Deque<type>::PushFront(const type &element) {
  front.push_back(element);
}
template<typename type>
void Deque<type>::PushBack(const type &element) {
  back.push_back(element);
}