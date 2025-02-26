// C++ program for Union by Size with Path Compression
#include <iostream>
#include <set>
#include <stack>
#include <vector>

class Edge {
public:
  int src, dest;

  friend bool operator<(const Edge &l, const Edge &r) {
    return l.src < r.src;
  }
};

struct Command {
  std::string type;
  int x;
  int y;
};

class Graph {
public:
  int V, E;
  std::vector<Edge> edges;
  Graph(int V, int E) {
    this->V = V;
    this->E = E;
  }
  void addEdge(int u, int v) { edges.push_back({u, v}); }

  Edge removeEdge(int u, int v) {
    for (auto it = edges.begin(); it != edges.end(); ++it) {
      if (((*it).src == u && (*it).dest == v) ||
          ((*it).src == v && (*it).dest == u)) {
        int rx = (*it).src, ry = (*it).dest;
        edges.erase(it);
        return {rx, ry};
      }
    }
    return {-1, -1};
  }
};

class Subset {
public:
  int parent;
  int rank;
};

int find(std::vector<Subset> subsets, int i) {
  if (subsets[i].parent != i)
    subsets[i].parent = find(subsets, subsets[i].parent);
  return subsets[i].parent;
}

void Union(std::vector<Subset> &subsets, int x, int y) {
  int xroot = find(subsets, x);
  int yroot = find(subsets, y);
  if (xroot == yroot) {
    return;
  }
  if (subsets[xroot].rank < subsets[yroot].rank) {
    std::swap(xroot, yroot);
  }
  subsets[yroot].parent = xroot;
  subsets[xroot].rank += subsets[yroot].rank;
}

std::string ask(std::vector<Subset> &subsets, int x, int y) {
  if (find(subsets, x) == find(subsets, y)) {
    return "YES";
  } else {
    return "NO";
  }
}

// bool compare(Edge e1, Edge e2) { return e1.weight < e2.weight; }

// std::vector<Subset> KruskalMST(Graph &graph, Edge &eIgnore) {
//   std::vector<Edge> result;
//   int V = graph.V;
//   // sort(graph.edges.begin(), graph.edges.end(), compare);

//   std::vector<Subset> subsets(V);
//   // std::vector<int> parents(V);
//   for (int v = 0; v < V; ++v) {
//     subsets[v].parent = v;
//     // parents[v] = v;
//     subsets[v].rank = 0;
//   }

//   int e = 0;
//   int i = 0;
//   while (e < V - 1 && i < graph.edges.size()) {
//     Edge next_edge = graph.edges[i++];
//     if (next_edge.src == eIgnore.src && next_edge.dest == eIgnore.dest) {
//       continue;
//     }
//     int x = find(subsets, next_edge.src);
//     int y = find(subsets, next_edge.dest);
//     if (x != y) {
//       result.push_back(next_edge);
//       Union(subsets, x, y);
//       e++;
//     }
//   }
//   return subsets;
// }

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int V = 5, E = 7, K = 7;
  std::cin >> V >> E >> K;
  Graph graph(V, E);
  std::set<Edge> remEdges;
  int x = 0, y = 0, w = 0;
  for (int i = 0; i < E; i++) {
    std::cin >> x >> y;
    // graph.addEdge(--x, --y);
    // remEdges.insert({--x, --y});
  }

  // std::cout << '\n';
  // for (size_t i = 0; i < V; i++) {
  //   std::cout << i << " " << res[i].parent << " " << find(res, i) << '\n';
  // }
  std::string com = "";
  std::stack<Command> cStack;
  for (size_t i = 0; i < K; i++) {
    std::cin >> com;
    std::cin >> x >> y;
    x--;
    y--;
    cStack.push({com, x, y});
  }
  std::vector<Subset> res;
  std::vector<std::string> co;
  while (!cStack.empty()) {
    Command c = cStack.top();
    if (c.type == "ask") {
      co.push_back(ask(res, c.x, c.y));
    } else {
      Union(res, c.x, c.y);
    }
    cStack.pop();
  }

  for (int i = co.size() - 1; i > -1; i--) {
    std::cout << co[i] << '\n';
  }

  /*
  6 5
  1 2 0
  3 2 0
  2 4 0
  5 6 0
  3 5 0
  */
  // int ms = 2000000000;
  // for (int k = 0; k < res.size(); k++) {
  //   ei = res[k];
  //   auto res1 = KruskalMST(graph, ei);
  //   s1 = 0;
  //   for (int i = 0; i < res1.size(); ++i)
  //     s1 += res1[i].weight;
  //   ms = std::min(ms, s1);
  // }
  // std::cout << ms;

  return 0;
}
