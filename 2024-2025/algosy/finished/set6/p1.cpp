#include <iostream>
#include <set>
#include <stack>
#include <vector>
#include <functional>

std::vector<std::vector<int>> vs;
std::vector<int> visited;
std::vector<int> low, scc_id;

std::stack<size_t> stackSCC;
std::vector<bool> onStack;

size_t curId = 0, sccCount = 0;

void DFS(size_t vert) {
  stackSCC.push(vert);
  onStack[vert] = true;
  visited[vert] = low[vert] = ++curId;

  for (auto neigh : vs[vert]) {
    if (visited[neigh] == -1) {
      DFS(neigh);
      low[vert] = std::min(low[vert], low[neigh]);
    } else if (onStack[neigh]) {
      low[vert] = std::min(low[vert], low[neigh]);
    }
  }

  int node = 0;
  if (low[vert] == visited[vert]) {
    while (stackSCC.top() != vert) {
      node = stackSCC.top();
      onStack[node] = false;
      stackSCC.pop();
      scc_id[node] = sccCount;
    }
    node = stackSCC.top();
    onStack[node] = false;
    stackSCC.pop();
    scc_id[node] = sccCount;
    sccCount++;
    // size_t node = stackSCC.back();
    // stackSCC.pop_back();
    // while (node != vert) {
    //   node = stackSCC.back();
    //   stackSCC.pop_back();
    // }
  }
}

void replace(std::vector<int> &v, int w, int k) {
  for (int i = 0; i < v.size(); i++) {
    if (v[i] == w) {
      v[i] = k;
    }
  }
}

int main(int argc, char *argv[]) {
  int n = 0;
  int m = 0;
  int x = 0;
  int y = 0;
  std::cin >> n >> m;

  vs.resize(n);
  visited.resize(n, -1);
  low.resize(n, n);
  onStack.resize(n, false);
  scc_id.assign(n, -1);

  for (int i = 0; i < m; i++) {
    std::cin >> x >> y;
    vs[--x].push_back(--y);
  }

  for (size_t i = 0; i < n; i++) {
    if (visited[i] == -1) {
      DFS(i);
    }
  }

  std::set<int> strongV;
  for (int i = 0; i < n; i++) {
    strongV.insert(low[i]);
  }

  int k = 1;
  // for (int i = 0; i < n; i++) {
  //   for (int j = 0; j < vs[i].size(); j++) {
  //     if (low[vs[i][j]] < low[i]) {
  //       strongV.erase(low[vs[i][j]]);
  //       strongV.insert(n + k);
  //       replace(low, low[vs[i][j]], n + k);
  //       k++;
  //     }
  //   }
  // }

  // Построение DAG по SCC
  std::vector<std::vector<int>> dag(sccCount);
  std::vector<int> in_degree(sccCount, 0);

  for (int v = 0; v < n; v++) {
    for (int u : vs[v]) {
      if (scc_id[v] != scc_id[u]) {
        dag[scc_id[v]].push_back(scc_id[u]);
        in_degree[scc_id[u]]++;
      }
    }
  }

  // Топологическая сортировка SCC
  std::vector<int> order;
  std::vector<bool> visited_scc(sccCount, false);

  std::function<void(int)> topo_sort = [&](int v) {
    visited_scc[v] = true;
    for (int u : dag[v]) {
      if (!visited_scc[u]) {
        topo_sort(u);
      }
    }
    order.push_back(v);
  };

  for (int i = 0; i < sccCount; i++) {
    if (!visited_scc[i])
      topo_sort(i);
  }

  std::reverse(order.begin(), order.end());

  // Перенумерация SCC
  std::vector<int> new_scc_num(sccCount);
  for (size_t i = 0; i < order.size(); i++) {
    new_scc_num[order[i]] = i + 1;
  }

  std::cout << sccCount << "\n";
  for (int i = 0; i < n; i++) {
    std::cout << new_scc_num[scc_id[i]] << " ";
  }
  std::cout << "\n";

  // auto it = strongV.begin();
  // k = 1;
  // while (it != strongV.end()) {
  //   replace(low, *it, k);
  //   ++it;
  //   k++;
  // }
  // std::cout << strongV.size() << "\n";
  // for (int i = 0; i < n; i++) {
  //   // for (int j = 0; j < vs[i].size(); j++) {
  //   //   std::cout << vs[i][j] << " ";
  //   // }
  //   std::cout << low[i] << " ";
  //   // std::cout << '\n';
  // }

  return 0;
}

/*
8 13
1 2
2 1
1 3
3 4
2 4
5 3
5 6
5 7
4 5
4 6
7 6
6 8
8 7
*/
/*
1 0
0 1
2 0
3 2
3 1
2 4
5 4
6 4
4 3
5 3
5 6
7 5
6 7
*/