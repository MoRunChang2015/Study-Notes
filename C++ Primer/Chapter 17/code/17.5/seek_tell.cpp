#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    fstream file("text.txt", fstream::ate|fstream::in|fstream::out);
    if (!file) {
        cerr << "Error" << endl;
        return EXIT_FAILURE;
    }
    auto end_mark = file.tellg();
    file.seekg(0, fstream::beg);
    size_t cnt = 0;
    string line;
    while (file && file.tellg() != end_mark && getline(file, line)) {
        cnt += line.size() + 1;
        auto mark = file.tellg();
        file.seekp(0, fstream::end);
        file << cnt;
        if (mark != end_mark)
            file << " ";
        file.seekg(mark);
    }
    file.seekp(0, fstream::end);
    file << "\n";
    return 0;
}
