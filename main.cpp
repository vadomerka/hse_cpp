#include <cstdio>
#include <vector>
#include <queue>
#include <iostream>

struct Pos {
  int i;
  int j;
  Pos(const int i, const int j)
    : i(i)
    , j(j)
  {}
};

int main() {
  int sizeI, sizeJ;
  scanf("%d %d", &sizeI, &sizeJ);
  std::vector<std::vector<int>> a(1 + sizeI + 1, std::vector<int>(1 + sizeJ + 1, 1));
  for (int i = 1; i <= sizeI; i++) {
    for (int j = 1; j <= sizeJ; j++) {
      scanf("%d", &a[i][j]);
    }
  }
  const int UNDEF = -1;
  std::vector<std::vector<int>> len(1 + sizeI + 1, std::vector<int>(1 + sizeJ + 1, UNDEF));
  std::queue<Pos> q;
  len[1][1] = 0;
  q.push(Pos(1, 1));
  while (!q.empty()) {
    Pos cur = q.front();
    q.pop();
    if (a[cur.i][cur.j] == 2) {
      std::cout << len[cur.i][cur.j];
      return 0;
    }
    for (int di = -1; di <= 1; di++) {
      for (int dj = -1; dj <= 1; dj++) {
        if (di * di + dj * dj == 1) {
          int ni = cur.i;
          int nj = cur.j;
          while (true) {
            if (a[ni][nj] == 2) {
              break;
            }
            if (a[ni + di][nj + dj] == 1) {
              break;
            }
            ni += di;
            nj += dj;
          }
          if (len[ni][nj] == UNDEF) {
            len[ni][nj] = len[cur.i][cur.j] + 1;
            q.push(Pos(ni, nj));
          }
        }
      }
    }
  }
}