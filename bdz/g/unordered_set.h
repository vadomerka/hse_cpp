#ifndef UNORDERED_SET_H
#define UNORDERED_SET_H

#include <iterator>
#include <list>
#include <vector>

template <typename KeyT>
class UnorderedSet {
 public:
  UnorderedSet() = default;

  UnorderedSet(size_t count) : db_(count) {
  }

  template <class Iterator, class = std::enable_if_t<std::is_base_of_v<
                              std::forward_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>>>
  UnorderedSet(Iterator begin, Iterator end) {
    size_t count = std::distance(end, begin);
    db_.resize(count);
    n_elements_ = count;
    n_buckets_ = count;
    for (std::iterator it = begin; it != end; ++it) {
      size_t ind = BucketKey(*it);
      db_[ind].push_back(*it);
    }
  }

 public:
  size_t Size() const {
    return n_elements_;
  }

  bool Find(const KeyT& key) {
    for (auto it : db_[BucketKey(key)]) {

    }
    return false;
  }

  size_t BucketKey(const KeyT& key) {
    size_t hassh = std::hash<KeyT>(key);
    return hassh % n_buckets_;
  }

 private:
  int n_buckets_;
  int n_elements_;
  std::vector<std::list<KeyT>> db_;
};

#endif