#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
using namespace std;
int main() {
    istream_iterator<int> in_iter(cin), eof;
    vector<int> v(in_iter, eof);
    for_each(v.begin(), v.end(), [](const int& a) {cout << a << " ";});
    cout << endl;
    return 0;
}
