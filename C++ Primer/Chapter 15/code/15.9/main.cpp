#include <iostream>
#include <fstream>
#include "query.hpp"

using namespace std;


int main(int argc, char* args[]) {
    if (argc == 1) {
        cout << "Please enter the text file!" << endl;
        return 0;
    }

    ifstream in(args[1]);
    if (!in.good()) {
        cout << "Error! Can't open the text file!" << endl;
        return 0;
    }

    TextQuery tq(in);

    while (true) {
        cout << "enter word to look for, or q to quit: ";
        string s;
        if (!(cin >> s) || s == "q") break;
        cout << Query(s).eval(tq) << endl;
    }
    return 0;
}
