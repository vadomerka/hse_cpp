#include <algorithm>
#include <iostream>
#include <vector>

class Edge {
public:
  int src, dest, weight;
};

std::vector<int> bellmanFord(std::vector<Edge> &graph, int vertices, int source) {
  std::vector<int> dist(vertices, INT_MAX);
  dist[source] = 0;

  for (size_t i = 0; i < vertices - 1; i++) {
    for (const Edge& e: graph) {
      if (dist[e.src] != INT_MAX &&
          dist[e.src] + e.weight < dist[e.dest]) {
        dist[e.dest] = dist[e.src] + e.weight;
      }
    }
  }
  for (size_t i = 0; i < vertices; i++) {
    for (const Edge& e: graph) {
      if (dist[e.src] != INT_MAX &&
          dist[e.src] + e.weight < dist[e.dest]) {
        dist[e.dest] = INT_MIN;
      }
      if (dist[e.src] == INT_MIN) {
        dist[e.dest] = INT_MIN;
      }
    }
  }

  return dist;
}

int main() {
  int V = 0, E = 0;
  std::cin >> V >> E;

  std::vector<Edge> graph;

  int x = 0, y = 0, w = 0;
  for (int i = 0; i < E; i++) {
    std::cin >> x >> y >> w;
    graph.push_back({x, y, w});
  }

  auto res = bellmanFord(graph, V, 0);

  for (size_t i = 1; i < res.size(); i++) {
    if (res[i] == INT_MIN) {
      std::cout << "-inf" << '\n';
    } else {
      std::cout << res[i] << '\n';
    }
  }
  

  return 0;
}
