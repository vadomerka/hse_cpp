#include "btree.h"
#include <algorithm>
#include <cstdint>
#include <functional>
#include <stdexcept>

Node::Node(int t) : key(), children(), parent(nullptr), isLeaf(true), t(t) {}

BTree::BTree(int t) {
  t_ = t;
  size_ = 0;
  root = nullptr;
}

void deleteTree(Node *node) {
  if (!node)
    return;
  for (Node *child : node->children) {
    deleteTree(child);
  }
  delete node;
}

BTree::~BTree() { deleteTree(root); }

int64_t getSum(Node *node) {
  if (!node) {
    return 0;
  }
  int64_t res = 0;
  if (node->isLeaf) {
    for (int key : node->key) {
      res += key;
    }
    return res;
  }
  for (Node *child : node->children) {
    res += getSum(child);
  }
  return res;
}

int64_t BTree::sum() const { return root ? getSum(root) : 0; }

int64_t nodeSize(const Node *node) {
  int64_t res = 1;
  for (int i = 0; i < node->children.size(); i++) {
    res += nodeSize(node->children[i]);
  }
  return res;
}

size_t BTree::size() const { return root ? nodeSize(root) : 0; }

void splitChild(Node *parent, int i) {
  Node *child = parent->children[i];
  Node *newChild = new Node(child->t);
  newChild->isLeaf = child->isLeaf;

  newChild->key.assign(child->key.begin() + parent->t, child->key.end());
  child->key.resize(parent->t - 1);

  if (!child->isLeaf) {
    newChild->children.assign(child->children.begin() + parent->t, child->children.end());
    child->children.resize(parent->t);
  }

  parent->children.insert(parent->children.begin() + i + 1, newChild);
  parent->key.insert(parent->key.begin() + i, child->key[parent->t - 1]);
}

int insertNonFull(Node *node, int key) {
  int i = node->key.size() - 1;
  int ssize = 0;
  if (node->isLeaf) {
    node->key.push_back(0);
    while (i >= 0 && node->key[i] > key) {
      node->key[i + 1] = node->key[i];
      i--;
    }
    node->key[i + 1] = key;
  } else {
    while (i >= 0 && node->key[i] > key) {
      i--;
    }
    i++;

    if (node->children[i]->key.size() == 2 * node->t - 1) {
      splitChild(node, i);
      ssize++;
      if (key > node->key[i]) {
        i++;
      }
    }
    ssize += insertNonFull(node->children[i], key);
  }

  return ssize;
}

void BTree::insert(int key) {
  if (!root) {
    root = new Node(t_);
    root->key.push_back(key);
    size_ = 1;
    return;
  }

  Node* current = root;
  while (current) {
    if (std::find(current->key.begin(), current->key.end(), key) != current->key.end()) return;  
    
    if (current->isLeaf) break;
    size_t i = 0;
    while (i < current->key.size() && key > current->key[i]) ++i;
    current = current->children[i];
  }

  if (root->key.size() == 2 * t_ - 1) {
    Node *newRoot = new Node(t_);
    newRoot->isLeaf = false;
    newRoot->children.push_back(root);
    splitChild(newRoot, 0);
    size_ += 2;
    root = newRoot;
  }
  size_ += insertNonFull(root, key);
}
