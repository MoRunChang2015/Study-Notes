#include <algorithm>
#include <iostream>
using namespace std;
int main() {
    vector<int> v = {0, -2, 3, 4, 5, -6, -7, 78};
    transform(v.begin(), v.end(), v.begin(), [](int i) {
        if (i < 0)
            return -i;
        else
            return i;
    });
    for_each(v.begin(), v.end(), [](int i) { cout << i << " "; });
    cout << endl;
    return 0;
}
