/*
#include <bits/stdc++.h>

std::vector<long long> countSort(std::vector<long long> &inputArray) {

  long long N = inputArray.size();
  long long Mx = inputArray[0];
  long long Mn = inputArray[0];

  for (long long i = 0; i < N; i++) {
    Mx = std::max(Mx, inputArray[i]);
    Mn = std::min(Mn, inputArray[i]);
  }
  long long mLen = Mx - Mn + 1;

  std::vector<long long> countArray(mLen, 0);

  for (long long i = 0; i < N; i++) {
    countArray[inputArray[i] - Mn]++;
  }
  // for (long long i = 1; i <= M; i++) {
  //   countArray[i] += countArray[i - 1];
  // }

  std::vector<long long> outputArray(N);

  long long kCArr = 0;
  for (long long i = 0; i < mLen; i++) {
    while (countArray[i] > 0) {
      outputArray[kCArr] = i + Mn;
      countArray[i]--;
      kCArr++;
    }
  }


  return outputArray;
}

// Driver code
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  long long n = 0;
  std::cin >> n;
  std::vector<long long> arr;
  long long x = 0;
  for (size_t i = 0; i < n; i++) {
    std::cin >> x;
    arr.push_back(x);
  }

  std::vector<long long> outputArray = countSort(arr);

  for (long long i = 0; i < arr.size(); i++) {
    std::cout << outputArray[i] << " ";
  }
  return 0;
}
*/