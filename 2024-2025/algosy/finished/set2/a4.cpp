#include <iostream>
#include <vector>

using namespace std;

int merge_and_count(vector<int> &arr, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  vector<int> leftArr(n1), rightArr(n2);

  for (int i = 0; i < n1; i++)
    leftArr[i] = arr[left + i];
  for (int i = 0; i < n2; i++)
    rightArr[i] = arr[mid + 1 + i];

  int i = 0, j = 0, k = left;
  int inversion_count = 0;

  while (i < n1 && j < n2) {
    if (leftArr[i] <= rightArr[j]) {
      arr[k] = leftArr[i];
      i++;
    } else {
      arr[k] = rightArr[j];
      j++;
      inversion_count += (n1 - i); // Все оставшиеся элементы в leftArr больше
    }
    k++;
  }

  while (i < n1) {
    arr[k] = leftArr[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = rightArr[j];
    j++;
    k++;
  }

  return inversion_count;
}

int merge_and_count_significant(vector<int> &arr, int left, int mid,
                                int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  vector<int> leftArr(n1), rightArr(n2);

  for (int i = 0; i < n1; i++)
    leftArr[i] = arr[left + i];
  for (int i = 0; i < n2; i++)
    rightArr[i] = arr[mid + 1 + i];

  int i = 0, j = 0, k = left;
  int significant_inversion_count = 0;

  // Считаем количество значительно инвертированных пар
  for (i = 0; i < n1; i++) {
    while (j < n2 && leftArr[i] > 2 * rightArr[j]) {
      j++;
    }
    significant_inversion_count += j;
  }

  // Теперь выполняем обычное слияние, как в сортировке слиянием
  i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    if (leftArr[i] <= rightArr[j]) {
      arr[k] = leftArr[i];
      i++;
    } else {
      arr[k] = rightArr[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = leftArr[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = rightArr[j];
    j++;
    k++;
  }

  return significant_inversion_count;
}

int count_inversions(vector<int> &arr, int left, int right) {
  int inversion_count = 0;
  if (left < right) {
    int mid = left + (right - left) / 2;

    inversion_count += count_inversions(arr, left, mid);
    inversion_count += count_inversions(arr, mid + 1, right);
    inversion_count += merge_and_count_significant(arr, left, mid, right);
  }
  return inversion_count;
}

int main() {
  vector<int> arr = {5, 4, 3, 2, 1};
  int arr_size = arr.size();

  cout << "Исходный массив: \n";
  for (int i = 0; i < arr_size; i++)
    cout << arr[i] << " ";
  cout << endl;

  cout << count_inversions(arr, 0, arr_size - 1);

  return 0;
}