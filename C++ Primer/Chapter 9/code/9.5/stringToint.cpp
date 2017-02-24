#include <iostream>
#include <string>
using namespace std;
int main() {
    string s("37w2");
    size_t n = 0;
    size_t* p = &n;
    cout << stoi(s, p) << endl;
    cout << n << endl;
    cout << stoi(s, p, 8) << endl;
    return 0;
}
