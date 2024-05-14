#include <iostream>
using namespace std;

class MyCustomException : public std::exception {
    public:
char * what () {
        return "Custom C++ Exception";
    }
};

int main() {
    try {
        throw MyCustomException();
    } catch (MyCustomException mce) {
        cout << "Caught MyCustomException" << endl;
        cout << mce.what();
    }
}