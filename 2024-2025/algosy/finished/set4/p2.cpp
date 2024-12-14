#include <functional>
#include <iostream>
#include <vector>

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

Node *NIL = new Node(0);

void print(Node *node, int indent = 0) {
  if (node == NIL)
    return;

  print(node->right, indent + 4);
  std::cout << std::string(indent, ' ') << node->key
            << (node->color == RED ? "(R)" : "(B)") << std::endl;
  print(node->left, indent + 4);
}

bool bstColorCheck(Node *node, int minKey, int maxKey) {
  if (node == NIL) return true;
  if (node->key <= minKey || node->key >= maxKey) return false;
  if (node->color == RED) {
    if ((node->left->color == RED) || (node->right->color == RED)) {
      return false;
    }
  }
  return bstColorCheck(node->left, minKey, node->key) &&
         bstColorCheck(node->right, node->key, maxKey);
}

int blackHeightCheck(Node *node, int minKey, int maxKey) {
  if (node == NIL) return 1;
  if (node->key <= minKey || node->key >= maxKey) return -1;
  if (node->color == RED) {
    if ((node->left->color == RED) || (node->right->color == RED)) {
      return -1;
    }
  }
  int leftHC = blackHeightCheck(node->left, minKey, node->key);
  int rightHC = blackHeightCheck(node->right, node->key, maxKey);
  if (leftHC == -1 || rightHC == -1 || leftHC != rightHC) {
    return -1;
  }
  return leftHC + (node->color == BLACK ? 1 : 0);
}

bool fullCheck(Node* root) {
  if (root == nullptr) return true;
  if (root->color == RED) return false;
  // if (!bstColorCheck(root, INT_MIN, INT_MAX)) return false;
  // if (!colorCheck(root)) return false;
  if (blackHeightCheck(root, INT_MIN, INT_MAX) == -1) return false;
  return true;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  NIL->color = BLACK;
  int n = 0;
  std::cin >> n;
  if (n == 0) {
    std::cout << "NO";
    return 0;
  }
  int rootInd = 0;
  std::cin >> rootInd;
  rootInd--;

  std::vector<Node *> tree(n, 0);
  int number = 0;
  int key = 0;
  std::string left;
  std::string right;
  std::string color;
  for (int i = 0; i < n; i++) {
    std::cin >> number;
    std::cin >> key;
    Node *inputNode = new Node(key);
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

  if (tree[rootInd]->color != BLACK) {
    std::cout << "NO";
    return 0;
  }

  for (size_t i = 0; i < n; i++) {
    if (tree[i]->leftInd != -1) {
      tree[i]->left = tree[tree[i]->leftInd];
    } else {
      tree[i]->left = NIL;
    }
    if (tree[i]->rightInd != -1) {
      tree[i]->right = tree[tree[i]->rightInd];
    } else {
      tree[i]->right = NIL;
    }
  }

  // print(tree[rootInd]);
  if (fullCheck(tree[rootInd])) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }

  /*
  5 1
  1 2 2 4 B
  2 0 null 3 R
  3 1 null null B
  4 3 null 5 R
  5 4 null null B
  */

  return 0;
}