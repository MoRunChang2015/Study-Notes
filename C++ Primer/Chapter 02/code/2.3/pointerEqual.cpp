#include <iostream>
using namespace std;

int main() {
    int temp = 0;
    void* a = &temp;
    int* b = &temp;
    if (a == b) {
        cout << "a == b" << endl;
    } else {
        cout << "a != b" << endl;
    }
    return 0;
}
