#include <iostream>
using namespace std;

class Base {
    public:
        int pub;
    protected:
        int pro;
    private:
        int pri;
};

class D: public Base {
    public:
        int fun() {
            pri = 0;
            pro = 0;
            pub = 0;
        }
};

int main() {
    return 0;
}
