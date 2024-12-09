#include "avl_tree.h"
#include <cmath>

Node::Node(int value)
    : value(value), left(nullptr), right(nullptr), height(1) {}

Node::~Node() {
  delete left;
  delete right;
}

AVLTree::AVLTree() {
  root_ = nullptr;
  size_ = 0;
}

AVLTree::AVLTree(int value) {
  root_ = new Node(value);
  size_ = 1;
}

int AVLTree::getHeight() { return getNodeHeight(root_); }

void AVLTree::insert(int value) { root_ = insertNode(root_, value); }

void AVLTree::erase(int value) { root_ = removeNode(root_, value); }

int *AVLTree::find(int value) {
  if (!root_)
    return nullptr;
  Node *res = findNode(root_, value);
  return (res ? new int(res->value) : nullptr);
}

int *AVLTree::traversal() {
  if (!root_)
    return nullptr;
  int *res = new int[size_];
  int ind = 0;
  traversalInternal(root_, res, &ind);
  return res;
}

int *AVLTree::lowerBound(int value) {
  if (!root_)
    return nullptr;
  Node *res = lowerBoundInternal(root_, value);
  return (res ? &(res->value) : nullptr);
}

bool AVLTree::empty() { return root_ == nullptr; }

Node *AVLTree::getRoot() { return root_; }

int AVLTree::getSize() { return size_; }

AVLTree::~AVLTree() { delete root_; }

int AVLTree::getNodeHeight(Node *node) { return node ? node->height : 0; }

int AVLTree::balanceFactor(Node *node) {
  if (node == nullptr)
    return 0;
  return getNodeHeight(node->left) - getNodeHeight(node->right);
}

void AVLTree::balanceHeight(Node *node) {}

Node *AVLTree::rotateRight(Node *node) {
  Node *y = node;
  Node *x = y->left;
  Node *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = std::max(getNodeHeight(y->left), getNodeHeight(y->right)) + 1;
  x->height = std::max(getNodeHeight(x->left), getNodeHeight(x->right)) + 1;

  return x;
}

Node *AVLTree::rotateLeft(Node *node) {
  Node *x = node;
  Node *y = x->right;
  Node *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = std::max(getNodeHeight(x->left), getNodeHeight(x->right)) + 1;
  y->height = std::max(getNodeHeight(y->left), getNodeHeight(y->right)) + 1;

  return y;
}

Node *AVLTree::balanceNode(Node *node) {}

Node *AVLTree::insertNode(Node *node, int value) {
  if (node == nullptr) {
    size_++;
    return new Node(value);
  }

  if (value < node->value)
    node->left = insertNode(node->left, value);
  else if (value > node->value)
    node->right = insertNode(node->right, value);
  else
    return node;

  node->height =
      1 + std::max(getNodeHeight(node->left), getNodeHeight(node->right));

  int balance = balanceFactor(node);

  if (balance > 1 && value < node->left->value)
    return rotateRight(node);
  if (balance < -1 && value > node->right->value)
    return rotateLeft(node);
  if (balance > 1 && value > node->left->value) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
  }
  if (balance < -1 && value < node->right->value) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
  }

  return node;
}

Node *AVLTree::findMinNode(Node *node) {}

Node *AVLTree::removeMinNode(Node *node) {}

Node *AVLTree::removeNode(Node *node, int value) {
  if (node == nullptr)
    return node;

  if (value < node->value)
    node->left = removeNode(node->left, value);
  else if (value > node->value)
    node->right = removeNode(node->right, value);
  else {
    if ((node->left == nullptr) || (node->right == nullptr)) {
      Node *temp = node->left ? node->left : node->right;
      if (temp == nullptr) {
        temp = node;
        node = nullptr;
      } else
        *node = *temp;
      size_--;
      delete temp;
    } else {

      Node *temp = node->right; // node->right ? node->right->left : 0;
      while (temp->left != nullptr) {
        temp = temp->left;
      }
      node->value = temp->value;
      node->right = removeNode(node->right, temp->value);
    }
  }

  if (node == nullptr)
    return node;

  // Update height of the current node
  node->height =
      1 + std::max(getNodeHeight(node->left), getNodeHeight(node->right));

  // Get the balance factor of this node
  int balance = balanceFactor(node);

  // If this node becomes unbalanced, then there are 4
  // cases

  // Left Left Case
  if (balance > 1 && balanceFactor(node->left) >= 0)
    return rotateRight(node);

  // Left Right Case
  if (balance > 1 && balanceFactor(node->left) < 0) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
  }

  // Right Right Case
  if (balance < -1 && balanceFactor(node->right) <= 0)
    return rotateLeft(node);

  // Right Left Case
  if (balance < -1 && balanceFactor(node->right) > 0) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
  }

  return node;
}

Node *AVLTree::findNode(Node *node, int value) {
  if (node == nullptr)
    return nullptr;
  if (node->value == value)
    return node;
  if (value < node->value)
    return findNode(node->left, value);
  return findNode(node->right, value);
}

void AVLTree::traversalInternal(Node *node, int *array, int *index) {
  if (node->left) {
    traversalInternal(node->left, array, index);
  }
  array[(*index)++] = node->value;
  if (node->right) {
    traversalInternal(node->right, array, index);
  }
}

Node *AVLTree::lowerBoundInternal(Node *current, int value) const {
  if (current == nullptr) {
    return nullptr; // Если узел пустой, возвращаем nullptr
  }
  if (current->value >= value) {
    // Если текущее значение >= заданного, то это кандидат
    Node *leftResult = lowerBoundInternal(current->left, value);
    return leftResult ? leftResult
                      : current; // Возвращаем более подходящий (минимальный)
  } else {
    // Иначе продолжаем поиск в правом поддереве
    return lowerBoundInternal(current->right, value);
  }
}