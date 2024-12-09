#include <iostream>
#include <vector>

long long getMax(std::vector<long long> &arr) {
  long long mx = arr[0];
  for (long long i = 1; i < arr.size(); i++)
    if (arr[i] > mx)
      mx = arr[i];
  return mx;
}

std::vector<long long> countSort(std::vector<long long> &arr, int exp) {
  long long N = arr.size();
  std::vector<long long> count(10, 0);

  for (long long i = 0; i < N; i++) {
    count[(arr[i] / exp) % 10]++;
  }

  std::vector<long long> output(N);

  // long long kCArr = 0;
  // for (long long i = 0; i < mLen; i++) {
  //   while (count[i] > 0) {
  //     outputArray[kCArr] = i + Mn;
  //     countArray[i]--;
  //     kCArr++;
  //   }
  // }
  for (long long i = 1; i < 10; i++)
    count[i] += count[i - 1];

  // Build the output array
  for (long long i = N - 1; i >= 0; i--) {
    output[count[(arr[i] / exp) % 10] - 1] = arr[i];
    count[(arr[i] / exp) % 10]--;
  }

  // Copy the output array to arr[],
  // so that arr[] now contains sorted
  // numbers according to current digit
  for (long long i = 0; i < N; i++)
    arr[i] = output[i];

  return output;
}

void radixsort(std::vector<long long> &arr) {
  long long m = getMax(arr);

  for (long long exp = 1; m / exp > 0; exp *= 10)
    countSort(arr, exp);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  long long n = 0;
  std::cin >> n;
  std::vector<long long> pos;
  std::vector<long long> neg;
  long long x = 0;
  for (size_t i = 0; i < n; i++) {
    std::cin >> x;
    if (x >= 0) {
      pos.push_back(x);
    } else { 
      neg.push_back(abs(x));
    }
  }
  if (pos.size() != 0) {
    radixsort(pos);
  }
  if (neg.size() != 0) {
    radixsort(neg);
  }

  for (long long i = 0; i < neg.size(); i++) {
    std::cout << -1 * neg[neg.size() - i - 1] << " ";
  }
  for (long long i = 0; i < pos.size(); i++) {
    std::cout << pos[i] << " ";
  }
  return 0;
}