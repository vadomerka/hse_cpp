#include <cstddef>
#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
  bool is_terminal = false;
  vector<Node *> sons;
  int words_after = 0;
  Node() { sons = vector<Node *>(26, NULL); }
};

class Boris {
public:
  Node *root;
  string alphabet = "abcdefghijklmnopqrstuvwxyz";
  int cur_sum;

  Boris() {
    root = new Node;
    cur_sum = 0;
  }

  void AddWord(string st) {
    Node *cur_node = root;
    for (char i : st) {
      if (cur_node->sons[i - 'a'] == NULL) {
        cur_node->sons[i - 'a'] = new Node;
      }
      cur_node = cur_node->sons[i - 'a'];
      ++cur_node->words_after;
    }
    cur_node->is_terminal = true;
  }

  void KthWord(int k, Node *cur_node, string ans) {
    if (cur_node->is_terminal && cur_sum == k - 1) {
      cout << ans;
      return;
    }
    for (int i = 0; i < 26; ++i) {
      if (cur_node->sons[i] != NULL) {
        cur_sum += cur_node->sons[i]->words_after;
        if (cur_sum >= k) {
          cur_sum -= cur_node->sons[i]->words_after;
          KthWord(k, cur_node->sons[i], ans + alphabet[i]);
        }
      }
    }
  }
};

int main() {
  int n, command, num;
  string st;
  Boris Dic;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> command;
    if (command == 1) {
      cin >> st;
      Dic.AddWord(st);
    } else {
      cin >> num;
      Dic.cur_sum = 0;
      Dic.KthWord(num, Dic.root, "");
    }
  }
}
