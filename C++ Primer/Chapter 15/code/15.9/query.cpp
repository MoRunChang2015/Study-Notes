#include "query.hpp"
#include <sstream>

using namespace std;

bool is_letter(char c) {
    if (c >= 'a' && c <= 'z') return true;
    if (c >= 'A' && c <= 'Z') return true;
    return false;
}

string& rmPunctuation(string& str) {
    size_t i = 0;
    while (!is_letter(str[i])) ++i;
    str.erase(0, i);
    i = str.size();
    while (!is_letter(str[i])) --i;
    str.erase(i + 1, str.size() - i);
    return str;
}

TextQuery::TextQuery(ifstream& in) : file(new vector<string>) {
    string text;
    while (getline(in, text)) {
        file->push_back(text);
        int line = file->size() - 1;
        string word;
        stringstream ss(text);
        while (ss >> word) {
            word = rmPunctuation(word);
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
    if (s[0] == '(' && s[s.size() - 1] == ')') {
        return Query(s.substr(1, s.size() - 2)).eval(*this);
    }
    if (s.find("|") != string::npos) {
        return (Query(s.substr(0, s.find("|"))) |
                Query(s.substr(s.find("|") + 1)))
            .eval(*this);
    }
    if (s.find("&") != string::npos) {
        return (Query(s.substr(0, s.find("&"))) &
                Query(s.substr(s.find("&") + 1)))
            .eval(*this);
    }
    if (s[0] == '~') {
        return (~Query(s.substr(1))).eval(*this);
    }
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

ostream& operator<<(ostream& os, const Query& q) { return os << q.rep(); }

inline Query::Query(const string& s) : q(new WordQuery(s)) {}

inline Query operator~(const Query& operand) {
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}

inline Query operator&(const Query& lhs, const Query& rhs) {
    return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

inline Query operator|(const Query& lhs, const Query& rhs) {
    return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

QueryResult OrQuery::eval(const TextQuery& text) const {
    auto right = rhs.eval(text), left = lhs.eval(text);
    auto ret_lines = make_shared<map<line_no, int>>(left.get_lines()->begin(),
                                                    left.get_lines()->end());

    for (auto& p : *right.get_lines()) (*ret_lines)[p.first] += p.second;

    return QueryResult(rep(), ret_lines, left.get_file());
}

QueryResult AndQuery::eval(const TextQuery& text) const {
    auto left = lhs.eval(text), right = rhs.eval(text);
    auto ret_lines = make_shared<map<line_no, int>>();

    for (auto& p : *left.get_lines())
        if (right.get_lines()->find(p.first) != right.get_lines()->end()) {
            (*ret_lines)[p.first] = p.second + (*right.get_lines())[p.first];
        }

    return QueryResult(rep(), ret_lines, left.get_file());
}

QueryResult NotQuery::eval(const TextQuery& text) const {
    auto result = query.eval(text);
    auto ret_lines = make_shared<map<line_no, int>>();
    auto sz = result.get_file()->size();
    auto begin = result.get_lines()->begin(), end = result.get_lines()->end();
    for (size_t n = 0; n != sz; n++) {
        if (begin == end || begin->first != n)
            (*ret_lines)[n] = 0;
        else
            ++begin;
    }

    return QueryResult(rep(), ret_lines, result.get_file());
}
