#include <iostream>
#include <vector>
#include <string>
using namespace std;
vector<int> next_s;
void get_next(string s) {
    int i = 0, j = -1;
    next_s.resize(s.length() + 1);
    next_s[0] = -1;
    while (i < s.length()) {
        if (j == -1 || s[i] == s[j]) {
            ++i;
            ++j;
            next_s[i] = j;
        } else {
           j = next_s[j];
        }
    }
}

int main() {
    cout << "Please enter the pattern string: " << flush;
    string p, str;
    cin >> p;
    get_next(p);
    cout << "Please enter the test string (^D For end)" << endl;
    vector<int> ans;
    while (cin >> str) {
        ans.clear();
        int i = 0, j = 0;
        while (i < str.length()) {
            if (j == -1 || str[i] == p[j]) {
                ++j;
                ++i;
                if (j == p.length()) {
                    j = next_s[j];
                    ans.push_back(i - p.length());
                }
            } else {
                j = next_s[j];
            }
        }
        for (auto & index: ans) {
            for (int i = 0; i < index; i++)
                cout << " ";
            cout << p << endl;
        }
    }
    return 0;
}
