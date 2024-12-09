#include <iostream>
#include <vector>

struct Frac {
 public:

  Frac() {}

  Frac(int xx, int yy) : x(xx) { 
    if (yy != 0) {
      y = yy;
    }
  }

  bool operator<=(const Frac& other) const {
    return x * other.y <= y * other.x;
  }

  int x = 0;
  int y = 1;
};

void merge(std::vector<Frac> &arr, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  std::vector<Frac> L(n1), R(n2);

  for (int i = 0; i < n1; i++)
    L[i] = arr[left + i];
  for (int j = 0; j < n2; j++)
    R[j] = arr[mid + 1 + j];

  int i = 0, j = 0;
  int k = left;

  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }
}

void mergeSort(std::vector<Frac> &arr, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = 0;
  std::cin >> n;
  std::vector<Frac> pos;
  int x = 0;
  int y = 0;
  char skip;
  for (size_t i = 0; i < n; i++) {
    std::cin >> x >> skip >> y;
    pos.push_back({x, y});
  }
  if (pos.size() != 0) {
    mergeSort(pos, 0, pos.size() - 1);
  }

  for (int i = 0; i < pos.size(); i++) {
    std::cout << pos[i].x << '/' << pos[i].y << " ";
  }
  return 0;
}