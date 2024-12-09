#include <iostream>
#include <vector>
#include <functional>

enum Color { RED, BLACK };

struct Node {
  int key;
  Color color;
  Node *left;
  int leftInd = -1;
  Node *right;
  int rightInd = -1;
  Node *parent;

  Node(int key)
      : key(key), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
public:
  int count = 0;
private:
  Node *root;
  Node *NIL;

  void leftRotate(Node *x) {
    count++;
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NIL) {
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

  void rightRotate(Node *y) {
    count++;
    Node *x = y->left;
    y->left = x->right;
    if (x->right != NIL) {
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

  void insertFixup(Node *z) {
    while (z->parent && z->parent->color == RED) {
      if (z->parent == z->parent->parent->left) {
        Node *y = z->parent->parent->right;
        if (y->color == RED) {
          z->parent->color = BLACK;
          y->color = BLACK;
          z->parent->parent->color = RED;
          z = z->parent->parent;
        } else {
          if (z == z->parent->right) {
            z = z->parent;
            leftRotate(z);
          }
          z->parent->color = BLACK;
          z->parent->parent->color = RED;
          rightRotate(z->parent->parent);
        }
      } else {
        Node *y = z->parent->parent->left;
        if (y->color == RED) {
          z->parent->color = BLACK;
          y->color = BLACK;
          z->parent->parent->color = RED;
          z = z->parent->parent;
        } else {
          if (z == z->parent->left) {
            z = z->parent;
            rightRotate(z);
          }
          z->parent->color = BLACK;
          z->parent->parent->color = RED;
          leftRotate(z->parent->parent);
        }
      }
    }
    root->color = BLACK;
  }

  void print(Node *node, int indent = 0) const {
    if (node == NIL)
      return;

    print(node->right, indent + 4);
    std::cout << std::string(indent, ' ') << node->key
              << (node->color == RED ? "(R)" : "(B)") << std::endl;
    print(node->left, indent + 4);
  }

public:
  RedBlackTree() {
    NIL = new Node(0);
    NIL->color = BLACK;
    root = NIL;
  }

  void insert(int key) {
    Node *z = new Node(key);
    Node *y = nullptr;
    Node *x = root;

    while (x != NIL) {
      y = x;
      if (z->key < x->key) {
        x = x->left;
      } else {
        x = x->right;
      }
    }

    z->parent = y;
    if (y == nullptr) {
      root = z;
    } else if (z->key < y->key) {
      y->left = z;
    } else {
      y->right = z;
    }

    z->left = NIL;
    z->right = NIL;
    z->color = RED;

    insertFixup(z);
  }

  void display() const { print(root); }

  ~RedBlackTree() {
    std::function<void(Node *)> deleteNode = [&](Node *node) {
      if (node == NIL)
        return;
      deleteNode(node->left);
      deleteNode(node->right);
      delete node;
    };
    deleteNode(root);
    delete NIL;
  }
};

int main() {
  int n = 0;
  std::cin >> n;
  if (!n) {
    std::cout << 0;
    return 0;
  }
  int rootInd = 0;
  std::cin >> rootInd;
  rootInd--;

  std::vector<Node*> tree (n, 0);
  int number = 0;
  int key = 0;
  std::string left;
  std::string right;
  std::string color;
  for (int i = 0; i < n; i++) {
    std::cin >> number;
    std::cin >> key;
    Node* inputNode = new Node(key);
    std::cin >> left;
    if (left != "null") {
      inputNode->leftInd = std::stoi(left) - 1;
    }
    std::cin >> right;
    if (right != "null") {
      inputNode->rightInd = std::stoi(right) - 1;
    }
    std::cin >> color;
    if (color == "B") {
      inputNode->color = BLACK;
    }
    tree[number - 1] = inputNode;
  }

  for (size_t i = 0; i < n; i++) {
    if (tree[i]->leftInd != -1) {
      tree[i]->left = tree[tree[i]->leftInd];
    }
    if (tree[i]->rightInd != -1) {
      tree[i]->right = tree[tree[i]->rightInd];
    }
  }
  

  return 0;
}