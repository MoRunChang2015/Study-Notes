#include <iostream>
#include <list>
#include <string>
#include <vector>
using namespace std;

int main() {
    list<string> name{"A", "B", "C"};
    string* front = &name.front();
    string* back = &name.back();
    vector<const char*> oldstyle = {"1", "2"};
    name.assign(oldstyle.cbegin(), oldstyle.cend());
    cout << name.size() << endl;
    cout << oldstyle.size() << endl;
    cout << front << endl;
    cout << back << endl;
    return 0;
}
