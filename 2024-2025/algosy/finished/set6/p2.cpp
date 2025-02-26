// C++ Program to Implement Minimum Spanning Tree using
// Kruskal's Algorithm
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Edge {
public:
  int src, dest, weight;
};

class Graph {
public:
  int V, E;
  vector<Edge> edges;
  Graph(int V, int E) {
    this->V = V;
    this->E = E;
  }
  void addEdge(int u, int v, int w) { edges.push_back({u, v, w}); }

  void removeEdge(int u, int v, int w) { 
    for (auto it = edges.begin(); it != edges.end(); ++it) {
      if ((*it).src == u && (*it).dest == v) {
        edges.erase(it);
        return;
      }
    }
  }
};

class Subset {
public:
  int parent, rank;
};

// Find the parent of a subset (with path compression)
int find(Subset subsets[], int i) {
  if (subsets[i].parent != i)
    subsets[i].parent = find(subsets, subsets[i].parent);
  return subsets[i].parent;
}

// Union of two subsets (with rank-based optimization)
void Union(Subset subsets[], int x, int y) {
  int xroot = find(subsets, x);
  int yroot = find(subsets, y);
  if (subsets[xroot].rank < subsets[yroot].rank)
    subsets[xroot].parent = yroot;
  else if (subsets[xroot].rank > subsets[yroot].rank)
    subsets[yroot].parent = xroot;
  else {
    subsets[yroot].parent = xroot;
    subsets[xroot].rank++;
  }
}

// Comparator function for sorting edges by weight
bool compare(Edge e1, Edge e2) { return e1.weight < e2.weight; }

// Kruskal's MST algorithm
vector<Edge> KruskalMST(Graph &graph, Edge& eIgnore) {
  vector<Edge> result;
  int V = graph.V;
  sort(graph.edges.begin(), graph.edges.end(), compare);

  Subset *subsets = new Subset[V];
  for (int v = 0; v < V; ++v) {
    subsets[v].parent = v;
    subsets[v].rank = 0;
  }

  int e = 0;
  int i = 0;
  while (e < V - 1 && i < graph.edges.size()) {
    Edge next_edge = graph.edges[i++];
    if (next_edge.src == eIgnore.src && next_edge.dest == eIgnore.dest) {
      continue;
    }
    int x = find(subsets, next_edge.src);
    int y = find(subsets, next_edge.dest);
    if (x != y) {
      result.push_back(next_edge);
      Union(subsets, x, y);
      e++;
    }
  }
  return result;
}

int main() {
  int V = 5, E = 7;
  std::cin >> V >> E;
  Graph graph(V, E);
  int x = 0, y = 0, w = 0;
  for (int i = 0; i < E; i++) {
    std::cin >> x >> y >> w;
    graph.addEdge(--x, --y, w);
  }

  Edge ei {-1, -1, -1};
  auto res = KruskalMST(graph, ei);
  int s1 = 0;
  for (int i = 0; i < res.size(); ++i)
    s1 += res[i].weight;
  std::cout << s1 << " ";

  int ms = 2000000000;
  for (int k = 0; k < res.size(); k++) {
    ei = res[k];
    auto res1 = KruskalMST(graph, ei);
    s1 = 0;
    for (int i = 0; i < res1.size(); ++i)
      s1 += res1[i].weight;
    ms = std::min(ms, s1);
  }
  std::cout << ms;

  return 0;
}
