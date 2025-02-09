#include <cstdint>
#include <string>
#include <vector>
#include <unordered_set>

class BloomFilter {
public:
    BloomFilter(size_t, size_t);
 
    void add(const std::string&);
 
    bool verify(const std::string&);
    
    double getFPRate() const;
 
    size_t numberOfHashFunctions() const ;
 
    size_t numberOfBits() const;
    
private:
    inline size_t _get_hash(int, const std::string &) const;
    
    size_t _hashes;
    size_t _bits;
    
    int cnt = 0, false_positive_cnt = 0;
    
    std::hash<std::string> hasher{};
    std::vector<bool> _filter;
    std::unordered_set<std::string> _raw_set;
};









// #include "bloom_filter.h"
#include <iostream>
 
 
BloomFilter::BloomFilter(size_t k, size_t m) : _hashes(k), _bits(m) {
  _filter.resize(_bits, false);
}

// BloomFilter::~BloomFilter() {

// }
 
 
void BloomFilter::add(const std::string & inf) {
  _raw_set.insert(inf);  // hasher(inf)
  _filter[hasher(inf) % _bits] = true;
  for (int i = 1; i < _hashes; i++) {
    _filter[hasher(inf + std::to_string(i)) % _bits] = true;
  }
}

 
bool BloomFilter::verify(const std::string & inf) {
  cnt++;
  if (!_filter[hasher(inf) % _bits]) return false;
  for (int i = 1; i < _hashes; i++) {
    if (!_filter[hasher(inf + std::to_string(i)) % _bits]) {
      return false;
    }
  }
  if (_raw_set.find(inf) == _raw_set.end()) {
    false_positive_cnt++;
  }
  return true;
}
 
 
double BloomFilter::getFPRate() const {
  double ans = false_positive_cnt;
  return cnt ? ans / cnt : 0;
}
 
 
size_t BloomFilter::numberOfHashFunctions() const {
  return _hashes;
}
 
 
size_t BloomFilter::numberOfBits() const {
  return _bits;
}
 
 
inline size_t BloomFilter::_get_hash(int i, const std::string &inf) const {
  return hasher(inf + std::to_string(i)) % _bits;
}



// int main() {
//   BloomFilter bf(4, 5);
//   bf.add("abc");
//   std::cout << bf.getFPRate() << '\n';

//   return 0;
// }