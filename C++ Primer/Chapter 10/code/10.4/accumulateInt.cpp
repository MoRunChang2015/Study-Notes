#include <iostream>
#include <iterator>
#include <algorithm>
using namespace std;
int main() {
    //istream_iterator<int> in(cin), eof;
    cout << accumulate(istream_iterator<int>(cin), istream_iterator<int>(), 0) << endl;
    return 0;
}
