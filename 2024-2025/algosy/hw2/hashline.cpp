#include <iostream>
#include <vector>

class HashLPTable {
private:
  std::vector<int> table;
  int size;
  int capacity;

  int hash(int key) { return key % capacity; }

public:
  HashLPTable(int capacity) : capacity(capacity), size(0) {
    table.resize(capacity, -1);
  }

  bool insert(int key) {
    if (size == capacity) {
      std::cout << "Hash Table is full\n";
      return false;
    }

    int idx = hash(key);
    while (table[idx] != -1) {
      idx = (idx + 1) % capacity;
    }

    table[idx] = key;
    size++;
    return true;
  }

  int search(int key) {
    int idx = hash(key) % capacity;
    for (int i = 0; i < capacity; i++) {
      if (table[idx] == -1) return -1;
      if (table[idx] == key) return idx;
      idx = (idx + 1) % capacity;
    }
    return -1;
  }

  bool deleteKey(int key) {
    if (search(key) == -1) return false;

    int idx = search(key);
    table[idx] = -1;
    size--;
    int prev = idx;
    for (int i = 1; i < capacity; i++) {
      idx = (idx + 1) % capacity;
      if (table[idx] == -1) {
        return true;
      } else if (idx == hash(table[idx])) {
        continue;
      } else {
        std::swap(table[prev], table[idx]);
        prev = idx;
      }
    }
    return true;
  }

  void printTable() {
    for (int i = 0; i < capacity; ++i) {
      if (table[i] != -1) {
        // std::cout << "Index " << i << ": " << table[i] << std::endl;
      }
      std::cout << table[i] << ' ';
    }
    std::cout << '\n';
  }
};

int main() {
  HashLPTable hashTable(10);

  // Вставка элементов
  hashTable.insert(12);
  hashTable.insert(22);
  hashTable.insert(32);
  hashTable.insert(33);
  hashTable.insert(36);
  hashTable.insert(47);
  hashTable.insert(58);

  hashTable.printTable();

  std::cout << hashTable.search(12) << '\n';
  std::cout << hashTable.deleteKey(12) << '\n';
  std::cout << hashTable.search(12) << '\n';

  hashTable.printTable();

  return 0;
}
