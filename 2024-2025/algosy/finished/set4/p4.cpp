#include "rbtree.h"
#include <algorithm>
#include <functional>
#include <stdexcept>

Node::Node(int key)
    : key(key), height(1), size(1), left(nullptr), right(nullptr),
      parent(nullptr), color(Color::RED) {}

RBTree::RBTree() : root(nullptr) {}

RBTree::RBTree(std::initializer_list<int> list) : root(nullptr) {
  for (int key : list) {
    insert(key);
  }
}

void deleteTree(Node *node) {
  if (!node) return;
  deleteTree(node->left);
  deleteTree(node->right);
  delete node;
}

void updateSize(Node* node) {
  node->size = 1;
  if (node->left) node->size += node->left->size;
  if (node->right) node->size += node->right->size;
}

void updateAncestorsSize(Node *node) {
  while (node) {
    updateSize(node);
    node = node->parent;
  }
}

RBTree::~RBTree() {
  deleteTree(root);
}

bool RBTree::empty() const { return root == nullptr; }

int RBTree::size() const { return root ? root->size : 0; }

int *RBTree::find(int key) {
  Node *current = root;
  while (current) {
    if (key == current->key) return &current->key;
    if (key < current->key)
      current = current->left;
    else
      current = current->right;
  }
  return nullptr;
}

int *RBTree::lowerBound(int key) {
  Node *current = root;
  Node *result = nullptr;
  while (current) {
    if (current->key >= key) {
      result = current;
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return result ? &result->key : nullptr;
}

Node *rotateLeft(Node *root, Node *node) {
  Node *rightChild = node->right;
  node->right = rightChild->left;
  if (rightChild->left)
    rightChild->left->parent = node;
  rightChild->parent = node->parent;
  if (!node->parent)
    root = rightChild;
  else if (node == node->parent->left)
    node->parent->left = rightChild;
  else
    node->parent->right = rightChild;
  rightChild->left = node;
  node->parent = rightChild;
  updateSize(node);
  updateSize(rightChild);
  return root;
}

Node *rotateRight(Node *root, Node *node) {
  Node *leftChild = node->left;
  node->left = leftChild->right;
  if (leftChild->right)
    leftChild->right->parent = node;
  leftChild->parent = node->parent;
  if (!node->parent)
    root = leftChild;
  else if (node == node->parent->left)
    node->parent->left = leftChild;
  else
    node->parent->right = leftChild;
  leftChild->right = node;
  node->parent = leftChild;
  updateSize(node);
  updateSize(leftChild);
  return root;
}

Node* fixInsert(Node *root, Node *node) {
  while (node->parent && node->parent->color == Color::RED) {
    Node *grandparent = node->parent->parent;
    if (node->parent == grandparent->left) {
      Node *uncle = grandparent->right;
      if (uncle && uncle->color == Color::RED) {
        // Case 1: Uncle is red
        node->parent->color = Color::BLACK;
        uncle->color = Color::BLACK;
        grandparent->color = Color::RED;
        node = grandparent;
      } else {
        if (node == node->parent->right) {
          // Case 2: Node is right child
          node = node->parent;
          root = rotateLeft(root, node);
        }
        // Case 3: Node is left child
        node->parent->color = Color::BLACK;
        grandparent->color = Color::RED;
        root = rotateRight(root, grandparent);
      }
    } else {
      Node *uncle = grandparent->left;
      if (uncle && uncle->color == Color::RED) {
        // Case 1: Uncle is red
        node->parent->color = Color::BLACK;
        uncle->color = Color::BLACK;
        grandparent->color = Color::RED;
        node = grandparent;
      } else {
        if (node == node->parent->left) {
          // Case 2: Node is left child
          node = node->parent;
          root = rotateRight(root, node);
        }
        // Case 3: Node is right child
        node->parent->color = Color::BLACK;
        grandparent->color = Color::RED;
        root = rotateLeft(root, grandparent);
      }
    }
  }
  if (node->parent) updateSize(node->parent);
  if (node->parent && node->parent->parent) updateSize(node->parent->parent);
  root->color = Color::BLACK;
  updateSize(root);
  return root;
}

void RBTree::insert(int key) {
  Node *newNode = new Node(key);
  if (!root) {
    root = newNode;
    root->color = Color::BLACK;
    return;
  }

  Node *parent = nullptr;
  Node *current = root;
  while (current) {
    parent = current;
    if (key < current->key)
      current = current->left;
    else if (key > current->key)
      current = current->right;
    else {
      return;
    }
  }

  newNode->parent = parent;
  if (key < parent->key)
    parent->left = newNode;
  else
    parent->right = newNode;
  
  int sizeOld = root->size;
  updateAncestorsSize(newNode);
  root = fixInsert(root, newNode);
}
