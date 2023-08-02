// TODO(Nikita): use module std lib
module;
#include <cassert>
#include <deque>
export module modern_cxx;

export namespace modern_cxx::brown {

struct Node {
  Node(int Value, Node *Parent) noexcept : value(Value), parent(Parent) {}

  auto IsLeftSon(Node *Other) const noexcept -> bool {
    assert(Other);
    return left == Other;
  }

  auto IsRightSon(Node *Other) const noexcept -> bool {
    assert(Other);
    return right == Other;
  }

  int value;             // NOLINT
  Node *left  = nullptr; // NOLINT
  Node *right = nullptr; // NOLINT
  Node *parent;          // NOLINT
};

class NodeBuilder {
public:
  auto CreateRoot(int Value) -> Node * {
    m_Nodes.emplace_back(Value, nullptr);
    return &m_Nodes.back();
  }

  auto CreateLeftSon(Node *Me, int Value) -> Node * {
    assert(Me->left == nullptr);
    m_Nodes.emplace_back(Value, Me);
    Me->left = &m_Nodes.back();
    return Me->left;
  }

  auto CreateRightSon(Node *Me, int Value) -> Node * {
    assert(Me->right == nullptr);
    m_Nodes.emplace_back(Value, Me);
    Me->right = &m_Nodes.back();
    return Me->right;
  }

private:
  std::deque<Node> m_Nodes;
};

auto
Minimum(Node *Me) -> Node * {
  assert(Me);
  while (Me->left) {
    Me = Me->left;
  }
  return Me;
}

auto
Next(Node *Me) -> Node * {
  assert(Me);

  if (Me->right) {
    return Minimum(Me->right);
  }

  auto *Parent = Me->parent;
  if (Parent && Parent->IsLeftSon(Me)) {
    return Parent;
  }

  while (Parent && Parent->IsRightSon(Me)) {
    Me     = Parent;
    Parent = Me->parent;
  }

  return Parent;
}

} // namespace modern_cxx::brown
