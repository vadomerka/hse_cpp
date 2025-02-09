#include <iostream>
#include <vector>
#include <cmath>
#include <random>

const int m = 20;
const int M = std::pow(2, m);
const int NULL_VALUE = -1;
const int ERASED = -2;
int c1 = 1;
int c2 = 1;
int c3 = 1;
int probe_count = 0;

std::vector<int> table(M, NULL_VALUE);

int hash(int key) { return key % M; }

int probe(int pind, int i) { 
  probe_count++;
  if (i == 0) return (pind + 1) % M;
  return (pind + c1 * i + c2 * i * i) % M;  //   + c3 * i * i * i
}

void INSERT(int key) {
  int ind = hash(key) % M;
  int i = 0;
  while (table[ind] != NULL_VALUE && i < table.size()) {
    if (table[ind] == key) return;
    ind = probe(ind, i);
    if (ind < 0) {
      return;
    }
    i++;
  }

  table[ind] = key;
}


// Поиск ключа
int SEARCH(int key) {
  int ind = hash(key) % M;
  int i = 0;
  while (table[ind] != NULL_VALUE && i < table.size()) {
    if (table[ind] == key)
      return ind;
    ind = (ind + 1) % M;
    i++;
  }
  return -1;
}

void DELETE(int key) {
  if (SEARCH(key) == -1) return;

  int idx = SEARCH(key);
  table[idx] = NULL_VALUE;
  int prev = idx;
  for (int i = 1; i < table.size(); i++) {
    idx = (idx + 1) % table.size();
    if (table[idx] == NULL_VALUE) {
      return;
    } else if (idx == hash(table[idx])) {
      continue;
    } else {
      std::swap(table[prev], table[idx]);
      prev = idx;
    }
  }
  return;
}


std::pair<int, double> clusterLenCount() {
  int ml = 0;
  int cl = 0;
  int sl = 0;
  int countl = 0;
  for (int i = 0; i < table.size(); i++) {
    if (table[i] == NULL_VALUE) {
      ml = std::max(cl, ml);
      sl += cl;
      countl++;
      cl = 0;
    } else {
      cl++;
    }
  }
  return {ml, countl};
}

// Тестирование
int main() {
  std::random_device rd;
  std::mt19937 rng{rd()};
  std::uniform_int_distribution<int> uid(0, M);
  int mp = 0;
  int sp = 0;
  int kloop = 5000;
  int max_cluster = 0;
  double av_cluster = 0;
  for (int i = 0; i < kloop; i++) {
    probe_count = 0;
    int filled = M;
    for (int i = 0; i < filled; i++) {
      int x = uid(rng);
      INSERT(x);
    }
    auto ccount = clusterLenCount();
    // std::cout << probe_count << " " << ccount.first << " " << ccount.second << '\n';
    max_cluster = std::max(max_cluster, ccount.first);
    av_cluster += ccount.second;
    mp = std::max(probe_count, mp);
    sp += probe_count;
    table = std::vector<int>(M, NULL_VALUE);
  }
  std::cout << "max probes: " << mp << '\n';
  std::cout << "average probes: " << (double)sp / kloop << '\n';
  std::cout << "max cluster: " << max_cluster << '\n';
  std::cout << "cluster count: " << (double)av_cluster / kloop << '\n';
  return 0;
}
