#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main() {
    string pattern("[^c]ei");
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    regex r(pattern);
    smatch result;

    string test_str = "receipt freind theif receive";

    if (regex_search(test_str, result, r)) cout << result.str() << endl;

    for (sregex_iterator it(test_str.begin(), test_str.end(), r), end_it;
         it != end_it; ++it) {
        cout << it->str() << endl;
    }
    return 0;
}
