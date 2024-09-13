#include <iostream>
#include <map>
#include <vector>

struct Graph {
 public:
  std::vector<std::vector<int>> leGraph_;

 public:
  explicit Graph(int length) : leGraph_(length) {
  }

 public:
  void AddEdge(int u, int v) {
    leGraph_[u].push_back(v);
    leGraph_[v].push_back(u);
  }

  bool HasConnection(int u, int v) {
    for (size_t i = 0; i < leGraph_[u].size(); i++) {
      if (leGraph_[u][i] == v) {
        return true;
      }
    }
    return false;
  }

  void Vertex(int u) {
    for (size_t i = 0; i < leGraph_[u].size(); i++) {
      std::cout << leGraph_[u][i] + 1 << " ";
    }
  }
};

int main(int, char**) {
  int n = 0;
  int com_number = 0;
  int command = 0;
  int u = 0;
  int v = 0;
  std::cin >> n;
  Graph g(n);
  std::cin >> com_number;
  for (int i = 0; i < com_number; i++) {
    std::cin >> command;
    if (command == 1) {
      std::cin >> u >> v;
      g.AddEdge(u - 1, v - 1);
    } else if (command == 2) {
      std::cin >> u;
      g.Vertex(u - 1);
    }
  }
}
