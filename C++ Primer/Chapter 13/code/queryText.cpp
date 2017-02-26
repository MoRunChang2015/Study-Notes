#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class QueryResult;
class TextQuery {
   public:
    using line_no = vector<string>::size_type;
    TextQuery(ifstream&);
    QueryResult query(const string&) const;

   private:
    shared_ptr<vector<string>> file;
    map<string, shared_ptr<map<line_no, int>>> wm;
};

ostream& operator<<(ostream&, const QueryResult&);

class QueryResult {
    friend ostream& operator<<(ostream&, const QueryResult&);

   public:
    QueryResult(string s, shared_ptr<map<TextQuery::line_no, int>> p,
                shared_ptr<vector<string>> f)
        : word(s), lines(p), file(f), total(0) {
        for (auto& r : *lines) {
            total += r.second;
        };
    };

   private:
    string word;
    int total;
    shared_ptr<map<TextQuery::line_no, int>> lines;
    shared_ptr<vector<string>> file;
};

TextQuery::TextQuery(ifstream& in) : file(new vector<string>) {
    string text;
    while (getline(in, text)) {
        file->push_back(text);
        int line = file->size() - 1;
        string word;
        stringstream ss(text);
        while (ss >> word) {
            auto& lines = wm[word];
            if (!lines) {
                lines.reset(new map<line_no, int>);
            }
            (*lines)[line]++;
        }
    }
}

QueryResult TextQuery::query(const string& s) const {
    static shared_ptr<map<line_no, int>> nodata(new map<line_no, int>);
    auto it = wm.find(s);
    if (it == wm.end())
        return QueryResult(s, nodata, file);
    else
        return QueryResult(s, it->second, file);
}

ostream& operator<<(ostream& os, const QueryResult& qr) {
    os << qr.word << " occurs " << qr.total << " "
       << (qr.total >= 2 ? "times" : "time") << endl;
    for (auto p : *qr.lines)
        os << "\t(line " << p.first + 1 << ") " << *(qr.file->begin() + p.first)
           << endl;
    return os;
}

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
        cout << tq.query(s) << endl;
    }
    return 0;
}
