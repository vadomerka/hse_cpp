#ifndef TEMPLATE_H
#define TEMPLATE_H
 
#include <initializer_list>
#include <iostream>

enum class Color { RED, BLACK };
 
struct Node {
    int key;
    int height;
    int size;
    Node *left;
    Node *right;
    Node *parent;
    Color color;
 
    explicit Node(int key);
};
 
class RBTree {
public:
    RBTree();
 
    RBTree(std::initializer_list<int> list);
 
    ~RBTree();
 
    void insert(int key);
    
    int *find(int key);
    
    int size() const;
 
    int *lowerBound(int key);
 
    bool empty() const;
 
    void erase(int key);
 
    int height() const;
 
    Node *root = nullptr;

    void print(Node *node, int indent) {
      if (!node)
        return;

      print(node->right, indent + 4);
      std::cout << std::string(indent, ' ') << node->key
                << (node->color == Color::RED ? "(R)" : "(B)") << std::endl;
      print(node->left, indent + 4);
    }
 
};
 
#endif
