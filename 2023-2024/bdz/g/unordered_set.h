#ifndef UNORDERED_SET_H
#define UNORDERED_SET_H

#include <iterator>
#include <list>
#include <vector>

template <typename KeyT>
class UnorderedSet {
 public:
  UnorderedSet() : n_elements_(0){};

  explicit UnorderedSet(size_t count) : n_elements_(0), db_(count) {
  }

  template <class Iterator, class = std::enable_if_t<std::is_base_of_v<
                                std::forward_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>>>
  UnorderedSet(Iterator begin, Iterator end) {
    n_elements_ = 0;
    db_.resize(std::distance(begin, end));
    for (Iterator it = begin; it != end; ++it) {
      Insert(*it);
    }
  }

  UnorderedSet(const UnorderedSet& other) : n_elements_(other.n_elements_), db_(other.db_) {
  }

  UnorderedSet& operator=(const UnorderedSet& other) {
    if (this == &other) {
      return *this;
    }

    n_elements_ = other.n_elements_;
    db_ = other.db_;
    return *this;
  }

  UnorderedSet(UnorderedSet&& other) : n_elements_(other.n_elements_), db_(std::move(other.db_)) {
    other.n_elements_ = 0;
  }

  UnorderedSet& operator=(UnorderedSet&& other) {
    if (this == &other) {
      return *this;
    }

    n_elements_ = other.n_elements_;
    db_ = std::move(other.db_);
    other.n_elements_ = 0;
    return *this;
  }

 public:
  size_t Size() const {
    return n_elements_;
  }

  bool Empty() const {
    return !n_elements_;
  }

  void Clear() {
    n_elements_ = 0;
    db_.clear();
  }

  void Insert(const KeyT& key) {
    if (db_.empty()) {
      db_.resize(1);
    } else if (Find(key)) {
      return;
    }

    if (LoadFactor() >= 1) {
      Rehash(n_elements_ * 2);
    }
    size_t ind = Bucket(key);
    db_[ind].push_back(key);
    n_elements_++;
  }

  void Insert(KeyT&& key) {
    if (db_.empty()) {
      db_.resize(1);
    } else if (Find(key)) {
      return;
    }

    if (LoadFactor() >= 1) {
      Rehash(n_elements_ * 2);
    }
    size_t ind = Bucket(key);
    db_[ind].push_back(std::move(key));
    n_elements_++;
  }

  void Erase(const KeyT& key) {
    if (!n_elements_) {
      return;
    }
    std::list<KeyT>& row = db_[Bucket(key)];
    for (auto it = row.begin(); it != row.end(); ++it) {
      if (*it == key) {
        row.erase(it);
        n_elements_--;
        break;
      }
    }
  }

  void Rehash(size_t new_bucket_count) {
    if (new_bucket_count < n_elements_) {
      return;
    }
    std::vector<std::list<KeyT>> ndb(new_bucket_count);
    for (size_t i = 0; i < db_.size(); i++) {
      while (!db_[i].empty()) {
        auto it = db_[i].begin();
        size_t hhash = Bucket(*it, new_bucket_count);
        std::list<KeyT>& new_list = ndb[hhash];
        new_list.splice(new_list.end(), db_[i], it);
      }
    }
    db_.swap(ndb);
  }

  void Reserve(size_t new_bucket_count) {
    if (new_bucket_count <= db_.size()) {
      return;
    }
    Rehash(new_bucket_count);
  }

  bool Find(const KeyT& key) const {
    if (!n_elements_) {
      return false;
    }
    for (auto it : db_[Bucket(key)]) {
      if (it == key) {
        return true;
      }
    }
    return false;
  }

  size_t BucketCount() const {
    return db_.size();
  }

  size_t BucketSize(size_t id) const {
    return id < db_.size() ? db_[id].size() : 0;
  }

  size_t Bucket(const KeyT& key) const {
    return db_.empty() ? 0 : std::hash<KeyT>()(key) % db_.size();
  }

  size_t Bucket(const KeyT& key, size_t new_size) const {
    return new_size ? std::hash<KeyT>()(key) % new_size : 0;
  }

  double LoadFactor() const {
    if (db_.empty()) {
      return 0;
    }
    return static_cast<float>(n_elements_) / db_.size();
  }

 private:
  size_t n_elements_;
  std::vector<std::list<KeyT>> db_;
};

#endif