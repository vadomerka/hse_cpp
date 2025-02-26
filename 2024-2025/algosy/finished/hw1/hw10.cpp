#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <iterator>
#include <cstddef>

struct TreeNode;

TreeNode *treeMax(TreeNode *root);
TreeNode *treeMin(TreeNode *root);
TreeNode *treePredecessor(TreeNode *root);
TreeNode *treeSuccessor(TreeNode *root);

// Структура для узла дерева
struct TreeNode {
  int value;
  TreeNode *left = nullptr;
  TreeNode *right = nullptr;
  TreeNode *parent = nullptr;

  TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}

  TreeNode* getRoot() {
    if (!parent) {
      return this;
    }
    return parent->getRoot();
  }

  struct Iterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = TreeNode;
    using pointer = TreeNode *;   // or also value_type*
    using reference = TreeNode &; // or also value_type&

    // Iterator(pointer ptr) : m_ptr(ptr) {}
    Iterator(TreeNode* ptr) : m_ptr(ptr) {}

    reference operator*() const { return *m_ptr; }
    pointer operator->() { return m_ptr; }

    // Prefix increment
    Iterator& operator++() { m_ptr = treeSuccessor(m_ptr); return *this; }

    // Postfix increment
    Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

    friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
    friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };   

    private:
      // pointer m_ptr;
      TreeNode* m_ptr;
  };

  Iterator begin() { return Iterator(treeMin(getRoot())); }
  Iterator end()   { return Iterator(nullptr); }  // treeSuccessor(treeMax(getRoot()))
};

// Функция для создания полного бинарного дерева из отсортированного массива
TreeNode *createCompleteBST(const std::vector<int> &sortedArray, int start,
                            int end) {
  if (start > end) {
    return nullptr;
  }

  // Выбираем средний элемент как корень текущего поддерева
  int mid = start + (end - start) / 2;
  TreeNode *root = new TreeNode(sortedArray[mid]);

  // Рекурсивно строим левое и правое поддеревья
  root->left = createCompleteBST(sortedArray, start, mid - 1);
  root->right = createCompleteBST(sortedArray, mid + 1, end);

  return root;
}

// Вспомогательная функция для создания полного BST из неотсортированного
// массива
TreeNode *createBSTFromArray(std::vector<int> &array) {
  // Сортируем массив
  std::sort(array.begin(), array.end());

  // Создаем полное бинарное дерево поиска
  return createCompleteBST(array, 0, array.size() - 1);
}

// Функция для печати дерева (обход в порядке инордер)
void inorderTraversal(TreeNode *root) {
  if (!root)
    return;

  inorderTraversal(root->left);
  std::cout << root->value << " ";
  inorderTraversal(root->right);
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

    std::cout << current->value << " ";

    if (current->left) {
      q.push(current->left);
    }
    if (current->right) {
      q.push(current->right);
    }
  }
}

TreeNode *treeMax(TreeNode *root) {
  if (!root->right) {
    return root;
  }
  return treeMax(root->right);
}

TreeNode *treeMin(TreeNode *root) {
  if (!root->left) {
    return root;
  }
  return treeMin(root->left);
}

TreeNode *treePredecessor(TreeNode *root) {
  if (root->left) {
    return treeMax(root->left);
  }
  TreeNode *parent = root->parent;
  while (parent && parent->left == root) {
    root = parent;
    parent = parent->parent;
  }
  return parent;
}

TreeNode *treeSuccessor(TreeNode *root) {
  if (root->right) {
    return treeMin(root->right);
  }
  TreeNode *parent = root->parent;
  while (parent && parent->right == root) {
    root = parent;
    parent = parent->parent;
  }
  return parent;
}

int main() {
  // Исходный неотсортированный массив
  std::vector<int> array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  // Создаем полное бинарное дерево поиска
  // TreeNode* root = createBSTFromArray(array);

  TreeNode *root = new TreeNode(20);
  TreeNode *node10 = new TreeNode(10);
  TreeNode *node30 = new TreeNode(30);
  TreeNode *node5 = new TreeNode(5);
  TreeNode *node15 = new TreeNode(15);
  TreeNode *node40 = new TreeNode(40);

  // Устанавливаем связи
  root->left = node10;
  root->right = node30;
  node10->parent = root;
  node30->parent = root;

  node10->left = node5;
  node10->right = node15;
  node5->parent = node10;
  node15->parent = node10;

  node30->right = node40;
  node40->parent = node30;

  // std::cout << treeSuccessor(node10)->value << " ";
  // std::cout << treeSuccessor(node15)->value << " ";
  // std::cout << treeSuccessor(root)->value << " ";
  // std::cout << treeSuccessor(node30)->value << " ";
  // std::cout << treeMin(root)->value;

  // std::cout << 
  for (auto i: *root) {
    std::cout << i.value << " ";
  }
  // std::cout << node10->end();
  

  return 0;
}
