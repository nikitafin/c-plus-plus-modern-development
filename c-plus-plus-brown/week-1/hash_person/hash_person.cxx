module;
#include <string>
export module hash_person;

namespace {

constexpr std::size_t kMagicNum = 0x9e3779b9;

constexpr std::size_t kMagicNum2 = kMagicNum * kMagicNum;

constexpr std::size_t kMagicNum3 = kMagicNum2 * kMagicNum;

}; // namespace

export namespace modern_cxx::brown {

struct Address {
  std::string city, street;
  int building;

  auto operator==(Address const &Other) const -> bool {
    return (city == Other.city) && (street == Other.street) &&
           (building == Other.building);
  }
};

struct Person {
  std::string name;
  int height;
  double weight;
  Address address;

  auto operator==(Person const &Other) const -> bool {
    return (name == Other.name) && (height == Other.height) &&
           (weight == Other.weight) && (address == Other.address);
  }
};

struct AddressHasher {
  auto operator()(Address const &Addr) const noexcept -> std::size_t {
    auto const CityHash     = Hs(Addr.city);
    auto const StreetHash   = Hs(Addr.street);
    auto const BuildingHash = Hi(Addr.building);

    std::size_t const Result =
        kMagicNum2 * CityHash + kMagicNum * StreetHash + BuildingHash;

    return Result;
  }

private:
  std::hash<std::string> Hs;
  std::hash<int> Hi;
};

struct PersonHasher {

  auto operator()(Person const &P) const noexcept -> std::size_t {
    auto const NameHash   = Hs(P.name);
    auto const HeightHash = Hi(P.height);
    auto const WeightHash = Hd(P.weight);
    auto const AddrHash   = Ha(P.address);

    auto const Result = kMagicNum3 * NameHash + kMagicNum2 * HeightHash +
                        kMagicNum * WeightHash + AddrHash;

    return Result;
  }

private:
  std::hash<std::string> Hs;
  std::hash<int> Hi;
  std::hash<double> Hd;
  AddressHasher Ha;
};

} // namespace modern_cxx::brown