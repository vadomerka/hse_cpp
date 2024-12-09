#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cstdint>


bool isSafe(const std::vector<std::pair<int, int>>& ts, double interval, int l, double endTime) {
  double trainX1 = 0;
  double trainX2 = 0;
  double untillNext = interval;

  int64_t sInd1 = 0;
  int64_t sInd2 = 0;
  double tSeg1 = 0;
  double tSeg2 = 0;

  while (sInd1 < ts.size()) {
    double tLeftSeg1 = ts[sInd1].first - tSeg1;
    if (untillNext > 0) {  // пока второй поезд не выехал
      if (untillNext >= tLeftSeg1) {  // если можно проехать сегмент полностью - едем
        untillNext -= tLeftSeg1;
        trainX1 += ts[sInd1].second * tLeftSeg1;
        tSeg1 = 0;
        sInd1++;
      } else {  // если второй поезд вот-вот выедет, аккуратно доезжаем остаток времени
        trainX1 += ts[sInd1].second * untillNext;
        tSeg1 += untillNext;
        untillNext = 0;
        trainX2 = 0;
        if (trainX1 - trainX2 < l) {
          return false;
        }
      }
      continue;
    }

    double tLeftSeg2 = sInd2 < ts.size() ? (ts[sInd2].first - tSeg2) : 0;
    double time_step = std::min(tLeftSeg1, tLeftSeg2);

    trainX1 += ts[sInd1].second * time_step;
    if (sInd2 < ts.size()) {
      trainX2 += ts[sInd2].second * time_step;
    }

    tSeg1 += time_step;
    tSeg2 += time_step;

    if (trainX1 - trainX2 < l) {
      return false;
    }

    if (tSeg1 >= ts[sInd1].first) {
      ++sInd1;
      tSeg1 = 0;
    }
    if (tSeg2 >= ts[sInd2].first && sInd2 < ts.size()) {
      ++sInd2;
      tSeg2 = 0;
    }
  }
  return true;
}


int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = 0;
  int l = 0;
  std::cin >> l;
  std::cin >> n;
  int x = 0, y = 0;
  double endTime = 0.0;
  std::vector<std::pair<int, int>> times;
  for (int i = 0; i < n; i++) {
    std::cin >> x >> y;
    times.push_back({x, y});
    endTime += x;
  }

  double lt = 0.0;
  double rt = 1000000.0;
  double mid = 0.0;

  while (rt - lt > 1e-3) {
    mid = lt + (rt - lt) / 2;
    if (isSafe(times, mid, l, endTime)) {
      rt = mid;
    } else {
      lt = mid;
    }
  }
  std::cout << std::fixed << std::setprecision(3) << rt;

  return 0;
}
