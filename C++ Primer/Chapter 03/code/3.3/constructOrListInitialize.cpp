#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main() {
    vector<int> v1{10, 1};
    vector<int> v2(10, 1);
    cout << "v1.size() = " << v1.size() << endl;
    cout << "v2.size() = " << v2.size() << endl;

    vector<string> v3{"hi"};
    vector<string> v4{10, "hi"};
    cout << "v3.size() = " << v3.size() << endl;
    cout << "v4.size() = " << v4.size() << endl;
    return 0;
}
