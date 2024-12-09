#include <iostream>
#include <string>
#include <stack>


int main() {
  std::string input = "";
  std::getline(std::cin, input);

  std::stack<std::string> strs;
  std::stack<int> ints;
  std::string curStr = "";
  int curInt = 0;
  int i = 0;
  while (i < input.size()) {
    if (input[i] == '[') { 
      ints.push(curInt);
      curInt = 0;
      strs.push(curStr);
      curStr = "";
    } else if (input[i] == ']') { 
      std::string curcur = curStr;
      curInt = ints.top();
      ints.pop();
      curStr = strs.top();
      strs.pop();
      while(curInt) {
        curStr += curcur;
        curInt--;
      }
    } else if (isdigit(input[i])) { 
      curInt += curInt * 10 + (input[i] - '0');
    } else {
      curStr += input[i];
    }
    i++;
  }
  std::cout << curStr;
  return 0;
}