#include <iostream>
#include <exception>
#include <stdexcept>
using namespace std;

int main() {
    try {
        throw runtime_error("Test");
    } catch(runtime_error e) {
        cout << e.what() << endl;
    } catch(exception e) {
        cout << "throw a exception!" << endl;
    }
    return 0;
}
