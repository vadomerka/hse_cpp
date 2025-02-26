#include <algorithm>
#include <iostream>
#include <vector>
#include <limits.h>
#include "../../../../../../../msys64/mingw32/include/limits.h"

class Edge {
public:
  size_t src, dest, weight;
};

std::vector<std::vector<size_t>> FloydWarshell(std::vector<Edge> &graph, size_t v) {
  std::vector<std::vector<size_t>> dist(v, std::vector<size_t>(v, LONG_LONG_MAX));
  std::vector<std::vector<size_t>> path(v, std::vector<size_t>(v, -1));
  for (size_t i = 0; i < v; i++) {
    dist[i][i] = 0;
    path[i][i] = i;
  }
  for (auto e: graph) {
    dist[e.src][e.dest] = std::min(dist[e.src][e.dest], e.weight);
    path[e.src][e.dest] = e.src;
  }

  for (size_t k = 0; k < v; k++) {
    for (size_t i = 0; i < v; i++) {
      for (size_t j = 0; j < v; j++) {
        if (dist[i][k] == LONG_LONG_MAX || dist[k][j] == LONG_LONG_MAX) continue;
        if (dist[i][k] + dist[k][j] < dist[i][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
          path[i][j] = path[k][j];
        }
      }
    }
  }
  
  return dist;
}

int main() {
  int V = 0, E = 0;
  std::cin >> V >> E;

  std::vector<Edge> graph;

  size_t x = 0, y = 0, w = 0;
  for (int i = 0; i < E; i++) {
    std::cin >> x >> y >> w;
    graph.push_back({x, y, w});
  }

  auto res = FloydWarshell(graph, V);

  for (size_t i = 0; i < V; i++) {
    for (size_t j = 0; j < V; j++) {
      if (i == j) continue;
      std::cout << i << " " << j << " ";
      if (res[i][j] == LONG_LONG_MAX) std::cout << -1 << '\n';
      else std::cout << res[i][j] << '\n';
    }
  }

  return 0;
}
