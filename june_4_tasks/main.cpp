#include <algorithm>
#include <ctime>
#include <iostream>
#include <map>
#include <random>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#pragma region Exercise 1

// Ex 1.2
std::vector<int> generateVector(size_t n, int rangeStart, int rangeEnd) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distr(rangeStart, rangeEnd - 1);

  std::vector<int> res;
  for (size_t i = 0; i < n; i++) {
    res.push_back(distr(gen));
  }
  return res;
}

// Ex 1.3
void printVec(const std::vector<int>& vecInt) {
  for (size_t i = 0; i < vecInt.size(); i++) {
    std::cout << vecInt[i] << " ";
  }
  std::cout << '\n';
}

// Ex 1.5.1
void printMap(const std::map<int, size_t>& mapInt) {
  for (std::pair<int, size_t> el : mapInt) {
    std::cout << el.first << ", " << el.second << "; ";
  }
  std::cout << '\n';
}

// Ex 1.5.2
void Increase(std::map<int, size_t>::const_iterator& it, std::map<int, size_t>::const_iterator end, int t) {
  for (int i = 0; i < t && it != end; i++) {
    ++it;
  }
}

// Ex 1.5.2
void printMapTth(int t, const std::map<int, size_t>& mapInt) {
  for (auto it = mapInt.begin(); it != mapInt.end(); Increase(it, mapInt.end(), t)) {
    std::cout << it->first << ", " << it->second << "; ";
  }
  std::cout << '\n';
}

// Ex 1.5.3
bool query(const std::map<int, size_t>& m, int k, size_t& element) {
  std::map<int, size_t>::const_iterator it = m.find(k);
  if (it != m.end()) {
    element = it->second;
    return true;
  } else {
    return false;
  }
}

bool query(const std::map<int, size_t>& m, int k, std::pair<int, size_t>& element) {
  std::map<int, size_t>::const_iterator it = m.find(k);
  if (it != m.end()) {
    element = *it;
    return true;
  } else {
    return false;
  }
}

// Ex 1.5.4
void increaseMapBy(int t, std::map<int, size_t>& mapInt) {
  for (auto it = mapInt.begin(); it != mapInt.end(); ++it) {
    it->second += t;
  }
}

// Ex 1.5.5
void eraseNegative(std::map<int, size_t>& mapInt) {
  for (auto it = mapInt.begin(); it != mapInt.end();) {
    if (it->first < 0)
      it = mapInt.erase(it);
    else
      ++it;
  }
}

#pragma endregion

#pragma region Exercise 2

// Exercise 2.1.
std::map<int, bool> Convert(const std::map<int, size_t>& m, int r, int q) {
  std::map<int, bool> res;
  for (int i = r; i < q; ++i) {
    res[i] = m.find(i) != m.end();
  }
  return res;
  // Complexity: (q - r) * O(log(n)) ?
}

// Exercise 2.2.
bool Contains(const std::map<int, bool>& m, int key) {
  return m.find(key) != m.end();
}

// Exercise 2.3.
std::set<int> Convert(const std::map<int, size_t>& m) {
  std::set<int> res;
  for (auto& item : m) {
    res.insert(item.first);
  }
  return res;
}

// Exercise 2.4.
void Print(const std::set<int>& s) {
  for (int item : s) {
    std::cout << item << ' ';
  }
  std::cout << '\n';
}

// Exercise 2.5.
bool Contains(const std::set<int>& s, int key) {
  return s.find(key) != s.end();
}

#pragma endregion

#pragma region Exercise 3

std::multimap<int, size_t> makeMultiMap(std::vector<int> rand_vect) {
  std::multimap<int, size_t> newMap;
  for (int i = 0; i < rand_vect.size(); i++) {
    std::map<int, size_t>::iterator it = newMap.find(rand_vect[i]);
    if (it != newMap.end()) {
      it->second += 1;
    } else {
      newMap.insert({rand_vect[i], 1});
    }
  }
  return newMap;
}

// Ex 3.2
void printMap(const std::multimap<int, size_t>& mmapInt) {
  for (std::pair<int, size_t> el : mmapInt) {
    std::cout << el.first << " - " << el.second << "; ";
  }
  std::cout << '\n';
}

// Ex 3.3.1
void printRange(std::multimap<int, size_t> mm, int start, int end) {
  for (auto it = mm.lower_bound(start); it != mm.upper_bound(end); ++it) {
    std::cout << it->first << " - " << it->second << "; ";
  }
  std::cout << '\n';
}

// Ex 3.3.2
void printRange(std::multimap<int, size_t> mm, int key) {
  for (auto it = mm.equal_range(key).first; it != mm.equal_range(key).second; ++it) {
    std::cout << it->first << " - " << it->second << "; ";
  }
  std::cout << '\n';
}

#pragma endregion

#pragma region Exercise 4

std::unordered_map<int, size_t> Convert(const std::vector<int>& arr) {
  std::unordered_map<int, size_t> res;
  for (int item : arr) {
    ++res[item];
  }
  return res;
}

void Print(const std::unordered_map<int, size_t>& m) {
  for (auto& item : m) {
    std::cout << '{' << item.first << ", " << item.second << "}; ";
  }
  std::cout << '\n';
}

std::unordered_map<int, size_t> ModifiedConvert(const std::vector<int>& arr) {
  std::unordered_map<int, size_t> res;
  for (int item : arr) {
    ++res[item];
    std::cout << "Add " << item << '\n';
    std::cout << "bucket_count: " << res.bucket_count() << '\n';
    std::cout << "max_bucket_count: " << res.max_bucket_count() << '\n';
    std::cout << "bucket_size: " << res.bucket_size(res.bucket(item)) << '\n';
    std::cout << "bucket: " << res.bucket(item) << '\n';
    std::cout << "load_factor: " << res.load_factor() << '\n';
  }
  return res;
}

#pragma endregion

int main() {
#pragma region Exercise 1

  std::cout << "Exercise 1\n";
  std::cout << "Enter three integers: n, r, q\n";
  int n, r, q;

  std::cin >> n >> r >> q;  // Ex 1.1
  std::vector<int> rand_vect = generateVector(n, r, q);
  printVec(rand_vect);

  std::map<int, size_t> map;
  for (size_t i = 0; i < rand_vect.size(); i++) {
    std::map<int, size_t>::iterator it = map.find(rand_vect[i]);
    if (it != map.end()) {
      it->second += 1;
    } else {
      map[rand_vect[i]] = 1;
    }
  }
  printMap(map);

  printMapTth(3, map);
  size_t res1 = 0;
  std::pair<int, size_t> res2 = {0, 0};
  std::cout << res1 << ": " << query(map, 3, res1) << '\n';
  std::cout << '{' << res2.first << ", " << res2.second << "}: " << query(map, 3, res2) << '\n';

  increaseMapBy(2, map);
  printMap(map);

  eraseNegative(map);
  printMap(map);

#pragma endregion

#pragma region Exercise 2

  std::cout << "\n\nExercise 2\n";
  auto m = Convert(map, r, q);
  for (auto& item : m)
    std::cout << item.first << ": " << item.second << '\n';

  std::cout << map.begin()->first << ": " << Contains(m, map.begin()->first) << '\n';
  std::cout << r - 1 << ": " << Contains(m, r - 1) << '\n';

  std::set<int> set = Convert(map);
  Print(set);

  std::cout << *set.begin() << ": " << Contains(m, *set.begin()) << '\n';
  std::cout << r - 1 << ": " << Contains(m, r - 1) << '\n';

#pragma endregion

#pragma region Exercise 3

  std::cout << "\n\nExercise 3\n";
  std::multimap<int, size_t> mmap = makeMultiMap(rand_vect);

  printMap(mmap);
  printRange(mmap, 1, 3);
  printRange(mmap, 2);

#pragma endregion

#pragma region Exercise 4

  std::cout << "\n\nExercise 4\n";
  auto m2 = Convert(rand_vect);
  Print(m2);
  ModifiedConvert(rand_vect);

#pragma endregion

  return 0;
}