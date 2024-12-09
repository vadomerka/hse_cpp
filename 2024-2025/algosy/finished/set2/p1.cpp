#include <iostream>
#include <vector>
#include <string>
#include <ios>
#define ll long long

struct Interval {
  ll left;
  ll right;

  Interval() : left(0), right(-1) {}

  Interval(ll nLeft, ll nRight) : left(nLeft), right(nRight) {}

  Interval(const Interval& other) : left(other.left), right(other.right) {}

  ll length() {
    return right - left + 1;
  }

  Interval overlap(const Interval &other) const {
    ll nLeft = std::max(left, other.left);
    ll nRight = std::min(right, other.right);
    if (nLeft > nRight) {
      return Interval {1, 0};
    }
    return Interval(nLeft, nRight);
  }

  std::string toString() {
    return std::to_string(left) + " " + std::to_string(right);
  }

  bool operator>(const Interval& other) {
    if (left > other.left) {
      return true;
    } else if (left == other.left) {
      if (right > other.right) {
        return true;
      }
    }
    return false;
  }
};

void invSort(std::vector<Interval> &invs, ll start, ll end) {
  if (start + 1 == end) {
    return;
  }
  if (end - start == 2) {
    if (invs[start] > invs[end - 1]) {
      std::swap(invs[start], invs[end - 1]);
    }
    return;
  }

  ll mid = start + (end - start) / 2;
  invSort(invs, start, mid);
  invSort(invs, mid, end);
  std::vector<Interval> res1 {invs.begin() + start, invs.begin() + mid};
  std::vector<Interval> res2 {invs.begin() + mid, invs.begin() + end};
  ll i1 = 0;
  ll i2 = 0;

  while (i1 < res1.size() && i2 < res2.size()) {
    if (res1[i1] > res2[i2]) {
      invs[start + i1 + i2] = res2[i2];
      i2++;
    } else {
      invs[start + i1 + i2] = res1[i1];
      i1++;
    }
  }

  for (i1 = i1; i1 < res1.size(); i1++) {
    invs[start + i1 + i2] = res1[i1];
  }
  for (ll j = i2; j < res2.size(); j++) {
    invs[start + i1 + j] = res2[j];
  }
  
}


int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);        
  
  std::vector<Interval> ivs{};
  ll n = 0;
  ll l = 0;
  ll r = 0;
  std::cin >> n;
  for (ll i = 0; i < n; i++) {
    std::cin >> l;
    std::cin >> r;
    ivs.push_back(Interval(l, r));
  }
  if (ivs.size() <= 1) {
    std::cout << 0;
    return 0;
  }
  // Interval res = naiive(ivs);
  invSort(ivs, 0, n);

  ll maxInd = 0;
  Interval result;
  for (ll i = 1; i < ivs.size(); i++) {
    Interval tmp (ivs[i].overlap(ivs[maxInd]));
    if (tmp.length() > result.length()) {
      result = tmp;
    }

    if (ivs[i].right > ivs[maxInd].right) {
      maxInd = i;
    }
  }
  if (result.length() == 0) {
    std::cout << result.length();
  } else {
    std::cout << result.length() << '\n';
    std::cout << result.toString();
  }
  return 0;
}