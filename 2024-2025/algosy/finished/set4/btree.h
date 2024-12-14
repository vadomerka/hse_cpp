#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <cstdint>
#include <iostream>
#include <vector>

struct Node {
  Node(int t);
  std::vector<int> key;
  std::vector<Node *> children;
  Node *parent;
  bool isLeaf;
  int t = 0;
};

class BTree {
public:
  explicit BTree(int t);

  ~BTree();

  void insert(int key);

  size_t size() const;

  int64_t sum() const;

  void print(Node *node, int level = 0) {
    if (!node)
      return;

    std::cout << std::string(level * 4, ' ');
    std::cout << level << ": ";
    for (int key : node->key) {
      std::cout << key << " ";
    }
    std::cout << std::endl;

    for (Node *child : node->children) {
      print(child, level + 1);
    }
  }

  void display() { print(root); }

private:
  Node *root;
  int t_;
  int size_;
};

#endif