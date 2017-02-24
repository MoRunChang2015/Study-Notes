#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <string>

using namespace std;

ostream& print(ostream &os, const string &s, char c) {
    return os << s << c;
}

int main() {
    vector<string> v = {"ABC", "DEF", "G"};
    for_each(v.begin(), v.end(), bind(print, ref(cout), placeholders::_1, '*'));
    cout << endl;
    return 0;
}
