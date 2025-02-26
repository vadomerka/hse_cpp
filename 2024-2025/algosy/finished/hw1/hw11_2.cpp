#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

class Node {
public:
  bool isLeaf;
  std::vector<int> keys;
  std::vector<Node *> children;

  Node(bool leaf) : isLeaf(leaf) {}
};

class Tree234 {
public:
  int count = 0;

private:
  Node *root;

  void splitChild(Node *parent, int childIndex) {
    count++;
    Node *child = parent->children[childIndex];

    Node *newChild = new Node(child->isLeaf);

    parent->keys.insert(parent->keys.begin() + childIndex, child->keys[1]);

    newChild->keys.push_back(child->keys[2]);

    if (!child->isLeaf) {
      newChild->children.push_back(child->children[2]);
      newChild->children.push_back(child->children[3]);
    }

    child->keys.resize(1);
    if (!child->isLeaf) {
      child->children.resize(2);
    }

    parent->children.insert(parent->children.begin() + childIndex + 1,
                            newChild);
  }

  void insertNonFull(Node *node, int key) {
    if (node->isLeaf) {
      node->keys.insert(
          std::upper_bound(node->keys.begin(), node->keys.end(), key), key);
    } else {
      int i = 0;
      while (i < node->keys.size() && key > node->keys[i]) {
        i++;
      }

      if (node->children[i]->keys.size() == 3) {
        splitChild(node, i);
        if (key > node->keys[i]) {
          i++;
        }
      }

      insertNonFull(node->children[i], key);
    }
  }

public:
  Tree234() : root(nullptr) {}

  void insert(int key) {
    if (!root) {
      root = new Node(true);
      root->keys.push_back(key);
    } else {
      if (root->keys.size() == 3) {
        Node *newRoot = new Node(false);
        newRoot->children.push_back(root);

        splitChild(newRoot, 0);
        root = newRoot;
      }
      insertNonFull(root, key);
    }
  }

  void print(Node *node, int level = 0) {
    if (!node)
      return;

    std::cout << std::string(level * 4, ' ');
    for (int key : node->keys) {
      std::cout << key << " ";
    }
    std::cout << std::endl;

    for (Node *child : node->children) {
      print(child, level + 1);
    }
  }

  void display() { print(root); }

  ~Tree234() {
    std::function<void(Node *)> deleteNode = [&](Node *node) {
      if (!node)
        return;
      for (Node *child : node->children) {
        deleteNode(child);
      }
      delete node;
    };
    deleteNode(root);
  }
};

int main() {
  for (int i = 1; i < 100; i++) {
    Tree234 tree;

    std::vector<int> keys = {10, 85, 15, 70, 20, 60, 30, 50};
    for (int j = 0; j < i; j++) {
      tree.insert(j);
    }

    std::cout << i << " " << tree.count << " " << i - tree.count << '\n';
  }
  return 0;
}
