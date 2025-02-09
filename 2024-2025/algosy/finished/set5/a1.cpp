#include <iostream>
#include <vector>

const int M = 5;
const int NULL_VALUE = -1;
const int ERASED = -2;

std::vector<int> table(M, NULL_VALUE);

int hash(int key) { return key % M; }

void INSERT(int key) {
  int ind = hash(key) % M;
  int i = 0;
  while (table[ind] != NULL_VALUE && i < table.size()) {
    if (table[ind] == key) return;
    ind = (ind + 1) % M;
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


// Тестирование
int main() {
  std::vector<int> nums {1, 2, 3, 33, 5, 7};
  for (size_t i = 0; i < nums.size(); i++) {
    INSERT(nums[i]);
  }
  // for (size_t i = 0; i < nums.size(); i++) {
  //   DELETE(nums[i]);
  // }

  // INSERT(6);
  DELETE(3);
  for (size_t i = 0; i < nums.size(); i++) {
    std::cout << SEARCH(nums[i]) << " ";
  }
  return 0;
}
