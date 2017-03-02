#include <iostream>
using namespace std;

void f1() {
    try {
        throw exception();
    } catch (exception e) {
        cout << "catch in f1" << endl;
        throw;
    } catch (...) {
        cout << "catch in f1" << endl;
    }
}

int main() {
    try {
        f1();
    } catch (...) {
        cout << "main" << endl;
    }
    return 0;
}
