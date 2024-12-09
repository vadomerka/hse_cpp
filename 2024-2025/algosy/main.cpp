// C++ Program to Implement AVL Tree
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;

// Template class representing a node in the AVL tree
template <typename T> class AVLNode {
public:
  T key;          // The value of the node
  AVLNode *left;  // Pointer to the left child
  AVLNode *right; // Pointer to the right child
  int height;     // Height of the node in the tree

  // Constructor to initialize a node with a given key
  AVLNode(T k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

// Template class representing the AVL tree
template <typename T> class AVLTree {
private:
  size_t countt = 0;

  // Pointer to the root of the tree
  AVLNode<T> *root;

  // function to get the height of a node
  int height(AVLNode<T> *node) {
    if (node == nullptr)
      return 0;
    return node->height;
  }

  // function to get the balance factor of a node
  int balanceFactor(AVLNode<T> *node) {
    if (node == nullptr)
      return 0;
    return height(node->left) - height(node->right);
  }

  // function to perform a right rotation on a subtree
  AVLNode<T> *rightRotate(AVLNode<T> *y) {
    countt++;
    AVLNode<T> *x = y->left;
    AVLNode<T> *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
  }

  // function to perform a left rotation on a subtree
  AVLNode<T> *leftRotate(AVLNode<T> *x) {
    countt++;
    AVLNode<T> *y = x->right;
    AVLNode<T> *T2 = y->left;

    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
  }

  // function to insert a new key into the subtree rooted
  // with node
  AVLNode<T> *insert(AVLNode<T> *node, T key) {
    // Perform the normal BST insertion
    if (node == nullptr)
      return new AVLNode<T>(key);

    if (key < node->key)
      node->left = insert(node->left, key);
    else if (key > node->key)
      node->right = insert(node->right, key);
    else
      return node;

    // Update height of this ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // Get the balance factor of this ancestor node
    int balance = balanceFactor(node);

    // If this node becomes unbalanced, then there are 4
    // cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
      return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
      return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }

    return node;
  }

  // function to find the node with the minimum key value
  AVLNode<T> *minValueNode(AVLNode<T> *node) {
    AVLNode<T> *current = node;
    while (current->left != nullptr)
      current = current->left;
    return current;
  }

  // function to delete a key from the subtree rooted with
  // root
  AVLNode<T> *deleteNode(AVLNode<T> *root, T key) {
    // Perform standard BST delete
    if (root == nullptr)
      return root;

    if (key < root->key)
      root->left = deleteNode(root->left, key);
    else if (key > root->key)
      root->right = deleteNode(root->right, key);
    else {
      // Node with only one child or no child
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

    // Update height of the current node
    root->height = 1 + max(height(root->left), height(root->right));

    // Get the balance factor of this node
    int balance = balanceFactor(root);

    // If this node becomes unbalanced, then there are 4
    // cases

    // Left Left Case
    if (balance > 1 && balanceFactor(root->left) >= 0)
      return rightRotate(root);

    // Left Right Case
    if (balance > 1 && balanceFactor(root->left) < 0) {
      root->left = leftRotate(root->left);
      return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && balanceFactor(root->right) <= 0)
      return leftRotate(root);

    // Right Left Case
    if (balance < -1 && balanceFactor(root->right) > 0) {
      root->right = rightRotate(root->right);
      return leftRotate(root);
    }

    return root;
  }

  // function to perform inorder traversal of the tree
  void inorder(AVLNode<T> *root) {
    if (root != nullptr) {
      inorder(root->left);
      cout << root->key << " ";
      inorder(root->right);
    }
  }

  // Функция для обхода дерева по уровням слева направо
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

  // function to search for a key in the subtree rooted
  // with root
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
  // Constructor to initialize the AVL tree
  AVLTree() : root(nullptr) {}

  // Function to insert a key into the AVL tree
  void insert(T key) { root = insert(root, key); }

  // Function to remove a key from the AVL tree
  void remove(T key) { root = deleteNode(root, key); }

  // Function to search for a key in the AVL tree
  bool search(T key) { return search(root, key); }

  size_t getCount() {
    return countt;
  }

  // Function to print the inorder traversal of the AVL
  // tree
  void printInorder() {
    // inorder(root);
    levelOrderTraversal(root);
    cout << endl;
  }
};

int main() {
  for (size_t j = 1; j < 1000; j++) {
    AVLTree<int> avl;

    // Insert nodes into the AVL tree
    // std::vector<int> a {1, 2, 3, 4, 5, 6, 7, 8};
    for (int i = 0; i < j; i++) {
      avl.insert(i);
    }

    // Print the inorder traversal of the AVL tree
    // cout << "Inorder traversal of the AVL tree: ";
    // avl.printInorder();

    // Remove a node from the AVL tree
    int funny = std::log2(j) + 1;
    std::cout << j << " " << j - avl.getCount() << " " << avl.getCount() << " " << j - funny << '\n';
  }

  return 0;
}