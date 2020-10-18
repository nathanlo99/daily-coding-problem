/*
Given the root to a binary tree, implement serialize(root), which serializes the
tree into a string, and deserialize(s), which deserializes the string back into
the tree.

For example, given the following Node class
```
class Node:
  def __init__(self, val, left=None, right=None):
    self.val = val
    self.left = left
    self.right = right
```

The following test should pass:
```
node = Node('root', Node('left', Node('left.left')), Node('right'))
assert deserialize(serialize(node)).left.left.val == 'left.left'
```
*/

#include <iostream>
#include <memory>
#include <string>

struct Node {
  std::string val;
  std::shared_ptr<Node> left, right;
  Node(const std::string &val, const std::shared_ptr<Node> &left,
       const std::shared_ptr<Node> &right)
      : val(val), left(left), right(right) {}
};

std::string serialize(const std::shared_ptr<Node> &root) {
  if (root == nullptr)
    return "nullptr";
  const std::string &left_serial = serialize(root->left),
                    &right_serial = serialize(root->right);
  return "{\"" + root->val + "\"," + left_serial + "," + right_serial + "}";
}

std::pair<std::string, size_t> string_helper(const std::string &data,
                                             const size_t start) {
  assert(data[start] == '"');
  const size_t end = data.find('"', start + 1), length = end - start + 1;
  return std::make_pair(data.substr(start + 1, length - 2), length);
}

std::pair<std::shared_ptr<Node>, size_t>
deserialize_helper(const std::string &data, const size_t start) {
  if (data[start] == 'n') {
    return std::make_pair(nullptr, std::string("nullptr").size());
  } else if (data[start] == '{') {
    size_t idx = start + 1;
    const auto &[val, val_size] = string_helper(data, idx);
    idx += val_size + 1;
    const auto &[left, left_size] = deserialize_helper(data, idx);
    idx += left_size + 1;
    const auto &[right, right_size] = deserialize_helper(data, idx);
    idx += right_size + 1;
    return std::make_pair(std::make_shared<Node>(val, left, right),
                          idx - start);
  }
  assert(false && "Invalid starting character");
}

std::shared_ptr<Node> deserialize(const std::string &data) {
  return deserialize_helper(data, 0).first;
}

int main() {
  const std::shared_ptr<Node> root = std::make_shared<Node>(
      "root",
      std::make_shared<Node>(
          "left", std::make_shared<Node>("left_left", nullptr, nullptr),
          nullptr),
      std::make_shared<Node>("right", nullptr, nullptr));
  const std::string &serialized = serialize(root);
  const std::shared_ptr<Node> new_root = deserialize(serialized);
  assert(new_root->left->left->val == "left_left");
  assert(new_root->left->val == "left");
  assert(new_root->right->val == "right");
  assert(new_root->val == "root");
  std::cout << "All tests passed!" << std::endl;
}
