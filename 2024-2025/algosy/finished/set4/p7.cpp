#include "splay-tree.h"

#include <algorithm>

Node::Node(int key, Node *parent)
    : key(key), left(nullptr), right(nullptr), parent(parent) {}

SplayTree::SplayTree() : root(nullptr) {}

SplayTree::~SplayTree() { clear(root); }

void SplayTree::clear(Node *node) {
  if (!node)
    return;
  clear(node->left);
  clear(node->right);
  delete node;
}

void SplayTree::rotateLeft(Node *x) {
  Node *y = x->right;
  x->right = y->left;
  if (y->left) {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == nullptr) {
    root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

void SplayTree::rotateRight(Node *y) {
    Node *x = y->left;
    y->left = x->right;
    if (x->right) {
      x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == nullptr) {
      root = x;
    } else if (y == y->parent->left) {
      y->parent->left = x;
    } else {
      y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
  }

int SplayTree::splay(Node *node) {
  if (!node)
    return 0;

  int rotations = 0;
  while (node->parent) {
    Node *parent = node->parent;
    Node *grandparent = parent->parent;

    if (!grandparent) {
      // Zig rotation
      if (node == parent->left)
        rotateRight(parent);
      else
        rotateLeft(parent);
      rotations++;
    } else if (node == parent->left && parent == grandparent->left) {
      // Zig-zig (left-left)
      rotateRight(grandparent);
      rotateRight(parent);
      rotations++;
      rotations++;
    } else if (node == parent->right && parent == grandparent->right) {
      // Zig-zig (right-right)
      rotateLeft(grandparent);
      rotateLeft(parent);
      rotations++;
      rotations++;
    } else if (node == parent->right && parent == grandparent->left) {
      // Zig-zag (left-right)
      rotateLeft(parent);
      rotateRight(grandparent);
      rotations++;
    } else {
      // Zig-zag (right-left)
      rotateRight(parent);
      rotateLeft(grandparent);
      rotations++;
    }
  }

  return rotations;
}

void SplayTree::insert(int key) {
  if (!root) {
    root = new Node(key, nullptr);
    return;
  }

  Node *current = root;
  Node *parent = nullptr;

  while (current) {
    parent = current;
    if (key < current->key)
      current = current->left;
    else if (key > current->key)
      current = current->right;
    else
      return;
  }

  Node *newNode = new Node(key, parent);
  if (key < parent->key)
    parent->left = newNode;
  else
    parent->right = newNode;
}

Node *SplayTree::find(int key) const {
  Node *current = root;

  while (current) {
    if (key < current->key)
      current = current->left;
    else if (key > current->key)
      current = current->right;
    else
      return current;
  }

  return nullptr;
}

int SplayTree::getHeight() const { return root ? getHeight(root) - 1 : 0; }

int SplayTree::getHeight(Node *node) const {
  if (!node)
    return 0;
  return 1 + std::max(getHeight(node->left), getHeight(node->right));
}
