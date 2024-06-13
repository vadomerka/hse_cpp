#include <iostream>
#include "unordered_set.h"

int main(int, char**) {
  std::vector<int> input {1, 2, 3, 4, 5};
  UnorderedSet<int> us;
  for (size_t i = 0; i < us.Size(); i++) {
    std::cout << us.Find(input[i]);
  }
}
