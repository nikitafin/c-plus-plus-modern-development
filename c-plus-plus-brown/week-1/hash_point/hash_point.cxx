// TODO(Nikita): use module std lib
module;
#include <unordered_set>
export module hash_point; // TODO(Nikita): IDE broken if modern_cxx

export namespace modern_cxx::brown {

using CoordType = int;

struct Point3D {
  CoordType x; // NOLINT
  CoordType y; // NOLINT
  CoordType z; // NOLINT

  auto operator==(Point3D const &Other) const noexcept -> bool {
    return (x == Other.x) && (y == Other.y) && (z == Other.z);
  }
};

struct Hasher {
  std::size_t operator()(Point3D const &Other) const noexcept {
    constexpr auto kMagicNum = 0x9e3779b9;
    auto const Hx            = h(Other.x);
    auto const Hy            = h(Other.y);
    auto const Hz            = h(Other.z);

    auto const Result = Hx * Hx * kMagicNum + Hy * kMagicNum + Hz;

    return Result;
  }

private:
  std::hash<CoordType> h;
};

} // namespace modern_cxx::brown
