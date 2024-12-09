#include <iostream>

int unpack(std::string str, int start = 0) {
  int num = str[start] - 48;
  int i = 0;
  int brC = 0;
  for (size_t _ = 0; _ < num; _++) {
    i = start + 1;
    while(brC >= 0 && i < str.size()) {
      if (48 <= str[i] && str[i] <= 58) {
        i = unpack(str, i);
      } else if (str[i] == '[') {
        brC++;
        i++;
        continue;
      } else if (str[i] == ']') {
        brC--;
        i++;
        continue;
      } else {
        std::cout << str[i];
        i++;
      }
    }
  }
  return i;
}

int main() {
  // std::string input = "";
  // std::cin >> input;
  std::
  unpack(input);
  std::cout << '\n';
  /*
  1[
    3[
      2[
        1[a]
      ]
      2[n]
    ]
  ]
  */
  return 0;
}