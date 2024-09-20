#include <bits/stdc++.h>

using namespace std;

class LoneNumber {
public:
    LoneNumber (string data) {
    if (data[0] == '-') {
        znak = false;
        data.erase(0, 1);
    }
    for (char i : data) {
        num *= 10;
        num += i - 48;
    }
}
public:
    bool znak = true;
    int num = 0;
    int mod = 1000000007;
};

long long NumInPowerMod (long long num, int power, int mod) {
    if (power == 0) {
        return 1;
    }
    if (power % 2 == 1) {
        return (NumInPowerMod(num, power - 1, mod) * num ) % mod;
    }
    long long dbl = NumInPowerMod(num, power / 2, mod) % mod;
    return (dbl * dbl) % mod;
}

bool IsOne(LoneNumber ln, LoneNumber power) {
    if (power.num == 0) return true;
    if (ln.num == 1) {
        if (ln.znak) {
            return true;
        } else if (power.num % 2 == 0) {
            return true;
        }
    }
    return false;
}

bool IsPos(LoneNumber ln, LoneNumber power) {
    if (IsOne(ln, power)) return true;
    if (ln.znak) return true;
    if (power.num % 2 == 0) return true;
    return false;
}

int main() {
    string cur_input;
    cin >> cur_input;
    LoneNumber num1(cur_input);
    cin >> cur_input;
    LoneNumber power1(cur_input);
    cin >> cur_input;
    LoneNumber num2(cur_input);
    cin >> cur_input;
    LoneNumber power2(cur_input);

    if (IsOne(num1, power1) && IsOne(num2, power2)) {
        cout << "correct";
        return 0;
    }
    if (IsOne(num1, power1) || IsOne(num2, power2)) {
        cout << "incorrect";
        return 0;
    }

    if ((IsPos(num1, power1) && IsPos(num2, power2)) 
        || (!IsPos(num1, power1) && !IsPos(num2, power2))) {
        if (NumInPowerMod(num1.num, power1.num, 1000000007) 
            != NumInPowerMod(num2.num, power2.num, 1000000007)) {
            cout << "incorrect";
            return 0;
        }
        cout << "correct";
        return 0;
    }
    cout << "incorrect";
    return 0;
}
