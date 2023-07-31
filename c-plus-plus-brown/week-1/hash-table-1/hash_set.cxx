// TODO(Nikita): use import std (only MSVC supports for now)
module;
#include <forward_list>
#include <iterator>
#include <unordered_map>
#include <vector>
export module hash_set;

export namespace modern_cxx::brown {

template <typename Type, typename Hasher>
class [[nodiscard]] HashSet final {
public:
  using BucketList = std::forward_list<Type>;

public:
  explicit HashSet(size_t num_buckets, const Hasher &hasher = {})
      : m_Hash{num_buckets}, m_Hasher{hasher} {}

  void Add(const Type &value) {
    if (Has(value)) {
      return;
    }

    auto const BucketNo = CalcBucketNo(value);
    m_Hash.at(BucketNo).push_front(value);
  }

  bool Has(const Type &value) const {
    auto const BucketNo = CalcBucketNo(value);
    BucketList const &bl = m_Hash.at(BucketNo);
    auto const Begin = std::begin(bl);
    auto const End = std::end(bl);

    auto const it = std::find(Begin, End, value);
    if (it == End) {
      return false;
    }

    return true;
  }

  void Erase(const Type &value) {
    auto const BucketNo = CalcBucketNo(value);
    m_Hash.at(BucketNo).remove(value);
  }

  const BucketList &GetBucket(const Type &value) const {
    auto const BucketNo = CalcBucketNo(value);
    return m_Hash.at(BucketNo);
  }

private:
  size_t CalcBucketNo(Type const &value) const noexcept {
    return m_Hasher(value) % m_Hash.size();
  }

private:
  std::vector<BucketList> m_Hash;
  Hasher m_Hasher; // NOTE: use inheritance ?
};

} // namespace modern_cxx::brown
