#include <iostream>
#include <string>
using namespace std;
int main() {
    string s = "123";
    int n = -1;
    if (s.size() < n) {
        cout << "s.size() < n" << endl;
    } else {
        cout << "s.size() >= n" << endl;
    }
    return 0;
}
