#include <iostream>
#include <queue>

struct TreeNode {
  int value;
  TreeNode *left = nullptr;
  TreeNode *right = nullptr;
  TreeNode *parent = nullptr;
  int height = 1;

  TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

TreeNode* insert(TreeNode* root, int val) {
  if (!root) {
    return new TreeNode(val);
  }
  TreeNode* left = root->left;
  TreeNode* right = root->right;

  if (val < root->value) {
    root->left = insert(left, val);
  } else if (val > root->value) {
    root->right = insert(right, val);
  } else {
    return root;
  }
  root->height = std::max(root->left ? root->left->height : 0, 
                          root->right ? root->right->height : 0) + 1;
  return root;
}

// Функция для обхода дерева по уровням слева направо
void levelOrderTraversal(TreeNode *root) {
  if (!root)
    return;

  std::queue<TreeNode *> q;
  q.push(root);

  while (!q.empty()) {
    TreeNode *current = q.front();
    q.pop();

    std::cout << "[" << current->value << " " << current->height << "] ";

    if (current->left) {
      q.push(current->left);
    }
    if (current->right) {
      q.push(current->right);
    }
  }
}

int balance(TreeNode* root) {
  if (!root) return 0;
  int l = 0;
  int r = 0;
  int ll = 0;
  int rr = 0;
  if (root->left) {
    l = root->left->height;
    ll = balance(root->left);
  } 
  if (root->right) {
    r = root->right->height;
    rr = balance(root->right);
  }
  if (l && r) {
    return std::max(std::max(std::abs(l - r), ll), rr);
  }
  return std::max(std::max(l + r, ll), rr);
}

int main() {

  int n = 0;
  TreeNode* root = nullptr;
  std::cin >> n;
  while (n != 0) {
    if (!root) {
      root = new TreeNode(n);
    } else {
      insert(root, n);
    }
    std::cin >> n;
  }
  // levelOrderTraversal(root);
  int res = balance(root);
  if (res < 2) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }

  return 0;
}