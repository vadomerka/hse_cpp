#include <algorithm>
#include <iostream>
#include <vector>

struct Solver {
  int id_ = 0;
  int tasks_ = 0;
  int time_ = 0;

  Solver(int id, int tasks, int time) : id_(id), tasks_(tasks), time_(time) {
  }
};

bool Comparator(const Solver &s1, const Solver &s2) {
  if (s1.tasks_ != s2.tasks_) {
    return s1.tasks_ > s2.tasks_;
  }
  if (s1.time_ != s2.time_) {
    return s1.time_ < s2.time_;
  }
  return s1.id_ < s2.id_;
}

int main() {
  int n = 0;
  std::cin >> n;

  std::vector<Solver> ss;

  int taskss = 0;
  int times = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> taskss >> times;
    ss.emplace_back(i + 1, taskss, times);
  }

  std::sort(ss.begin(), ss.end(), Comparator);

  for (const auto &s : ss) {
    std::cout << s.id_ << "\n";
  }

  return 0;
}