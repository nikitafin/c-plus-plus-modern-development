// TODO(Nikita): use import std (only MSVC supports for now)
module;
#include <forward_list>
#include <iterator>
#include <vector>
export module hash_set;

export namespace modern_cxx::brown {

template <typename Type, typename THasher>
class [[nodiscard]] HashSet final {
public:
  using BucketList = std::forward_list<Type>;

public:
  explicit HashSet(size_t NumBuckets, const THasher &Hasher = {})
      : m_Hash{NumBuckets}, m_Hasher{Hasher} {}

  void Add(const Type &Value) {
    if (Has(Value)) {
      return;
    }

    auto const BucketNo = CalcBucketNo(Value);
    m_Hash.at(BucketNo).push_front(Value);
  }

  auto Has(const Type &Value) const -> bool {
    auto const BucketNo = CalcBucketNo(Value);
    BucketList const &bl = m_Hash.at(BucketNo);
    auto const Begin = std::begin(bl);
    auto const End = std::end(bl);

    auto const it = std::find(Begin, End, Value);
    if (it == End) {
      return false;
    }

    return true;
  }

  void Erase(const Type &Value) {
    auto const BucketNo = CalcBucketNo(Value);
    m_Hash.at(BucketNo).remove(Value);
  }

  auto GetBucket(const Type &Value) const -> const BucketList & {
    auto const BucketNo = CalcBucketNo(Value);
    return m_Hash.at(BucketNo);
  }

private:
  auto CalcBucketNo(Type const &Value) const noexcept -> size_t {
    return m_Hasher(Value) % m_Hash.size();
  }

private:
  std::vector<BucketList> m_Hash;
  THasher m_Hasher; // NOTE: use inheritance ?
};

} // namespace modern_cxx::brown