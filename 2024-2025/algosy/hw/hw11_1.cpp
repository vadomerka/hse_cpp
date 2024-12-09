#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;

template <typename T> class AVLNode {
public:
  T key;
  AVLNode *left;
  AVLNode *right;
  int height;

  AVLNode(T k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

template <typename T> class AVLTree {
private:
  size_t countt = 0;

  AVLNode<T> *root;

  int height(AVLNode<T> *node) {
    if (node == nullptr)
      return 0;
    return node->height;
  }

  int balanceFactor(AVLNode<T> *node) {
    if (node == nullptr)
      return 0;
    return height(node->left) - height(node->right);
  }

  AVLNode<T> *rightRotate(AVLNode<T> *y) {
    countt++;
    AVLNode<T> *x = y->left;
    AVLNode<T> *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
  }

  AVLNode<T> *leftRotate(AVLNode<T> *x) {
    countt++;
    AVLNode<T> *y = x->right;
    AVLNode<T> *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
  }

  AVLNode<T> *insert(AVLNode<T> *node, T key) {
    if (node == nullptr)
      return new AVLNode<T>(key);

    if (key < node->key)
      node->left = insert(node->left, key);
    else if (key > node->key)
      node->right = insert(node->right, key);
    else
      return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = balanceFactor(node);

    if (balance > 1 && key < node->left->key)
      return rightRotate(node);

    if (balance < -1 && key > node->right->key)
      return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }

    return node;
  }

  AVLNode<T> *minValueNode(AVLNode<T> *node) {
    AVLNode<T> *current = node;
    while (current->left != nullptr)
      current = current->left;
    return current;
  }

  AVLNode<T> *deleteNode(AVLNode<T> *root, T key) {
    if (root == nullptr)
      return root;

    if (key < root->key)
      root->left = deleteNode(root->left, key);
    else if (key > root->key)
      root->right = deleteNode(root->right, key);
    else {
      if ((root->left == nullptr) || (root->right == nullptr)) {
        AVLNode<T> *temp = root->left ? root->left : root->right;
        if (temp == nullptr) {
          temp = root;
          root = nullptr;
        } else
          *root = *temp;
        delete temp;
      } else {

        AVLNode<T> *temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
      }
    }

    if (root == nullptr)
      return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = balanceFactor(root);

    if (balance > 1 && balanceFactor(root->left) >= 0)
      return rightRotate(root);

    if (balance > 1 && balanceFactor(root->left) < 0) {
      root->left = leftRotate(root->left);
      return rightRotate(root);
    }

    if (balance < -1 && balanceFactor(root->right) <= 0)
      return leftRotate(root);

    if (balance < -1 && balanceFactor(root->right) > 0) {
      root->right = rightRotate(root->right);
      return leftRotate(root);
    }

    return root;
  }

  void inorder(AVLNode<T> *root) {
    if (root != nullptr) {
      inorder(root->left);
      cout << root->key << " ";
      inorder(root->right);
    }
  }

  void levelOrderTraversal(AVLNode<T> *root) {
    if (!root)
      return;

    std::queue<AVLNode<T> *> q;
    q.push(root);

    while (!q.empty()) {
      AVLNode<T> *current = q.front();
      q.pop();

      std::cout << current->key << " ";

      if (current->left) {
        q.push(current->left);
      }
      if (current->right) {
        q.push(current->right);
      }
    }
  }

  bool search(AVLNode<T> *root, T key) {
    if (root == nullptr)
      return nullptr;
    if (root->key == key)
      return root;
    if (key < root->key)
      return search(root->left, key);
    return search(root->right, key);
  }

public:
  AVLTree() : root(nullptr) {}

  void insert(T key) { root = insert(root, key); }

  void remove(T key) { root = deleteNode(root, key); }

  bool search(T key) { return search(root, key); }

  size_t getCount() {
    return countt;
  }

  void printInorder() {
    levelOrderTraversal(root);
    cout << endl;
  }
};

int main() {
  for (size_t j = 0; j < 129; j++) {
    AVLTree<int> avl;

    for (int i = 0; i < j; i++) {
      avl.insert(i);
    }

    int funny = std::log2(j) + 1;
    std::cout << j << " " << j - avl.getCount() << " " << avl.getCount() << " " << j - funny << '\n';
  }

  return 0;
}