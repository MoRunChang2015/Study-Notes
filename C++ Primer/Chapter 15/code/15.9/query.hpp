#ifndef QUERY_HPP
#define QUERY_HPP
#include <fstream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

class QueryResult;
class TextQuery {
   public:
    using line_no = std::vector<std::string>::size_type;
    TextQuery(std::ifstream &);
    QueryResult query(const std::string &) const;

   private:
    std::shared_ptr<std::vector<std::string>> file;
    std::map<std::string, std::shared_ptr<std::map<line_no, int>>> wm;
};

class QueryResult {
    friend std::ostream &operator<<(std::ostream &, const QueryResult &);

   public:
    QueryResult(std::string s,
                std::shared_ptr<std::map<TextQuery::line_no, int>> p,
                std::shared_ptr<std::vector<std::string>> f)
        : word(s), lines(p), file(f), total(0) {
        for (auto &r : *lines) {
            total += r.second;
        };
    };

    std::shared_ptr<std::map<TextQuery::line_no, int>> get_lines() const {
        return lines;
    }

    std::shared_ptr<std::vector<std::string>> get_file() const { return file; }

   private:
    std::string word;
    int total;
    std::shared_ptr<std::map<TextQuery::line_no, int>> lines;
    std::shared_ptr<std::vector<std::string>> file;
};

class Query_base {
    friend class Query;

   protected:
    using line_no = TextQuery::line_no;
    virtual ~Query_base() = default;

   private:
    virtual QueryResult eval(const TextQuery &) const = 0;
    virtual std::string rep() const = 0;
};

class Query {
    friend Query operator~(const Query &);
    friend Query operator|(const Query &, const Query &);
    friend Query operator&(const Query &, const Query &);

   public:
    Query(const std::string &);
    QueryResult eval(const TextQuery &t) const { return q->eval(t); };
    std::string rep() const { return q->rep(); }

   private:
    Query(std::shared_ptr<Query_base> query) : q(query){};
    std::shared_ptr<Query_base> q;
};

Query operator~(const Query &);
Query operator|(const Query &, const Query &);
Query operator&(const Query &, const Query &);

std::ostream &operator<<(std::ostream &, const Query &);

class WordQuery : public Query_base {
    friend class Query;
    WordQuery(const std::string &s) : query_word(s) {}
    QueryResult eval(const TextQuery &t) const { return t.query(query_word); }
    std::string rep() const { return query_word; }
    std::string query_word;
};

class NotQuery : public Query_base {
    friend Query operator~(const Query &);
    NotQuery(const Query &q) : query(q){};
    std::string rep() const { return "~(" + query.rep() + ")"; }
    QueryResult eval(const TextQuery &) const;
    Query query;
};

class BinaryQuery : public Query_base {
   protected:
    BinaryQuery(const Query &l, const Query &r, std::string s)
        : lhs(l), rhs(r), opSym(s) {}
    std::string rep() const {
        return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";
    }

    Query lhs, rhs;
    std::string opSym;
};

class AndQuery : public BinaryQuery {
    friend Query operator&(const Query &, const Query &);
    AndQuery(const Query &left, const Query &right)
        : BinaryQuery(left, right, "&") {}

    QueryResult eval(const TextQuery &) const;
};

class OrQuery : public BinaryQuery {
    friend Query operator|(const Query &, const Query &);
    OrQuery(const Query &left, const Query &right)
        : BinaryQuery(left, right, "|") {}

    QueryResult eval(const TextQuery &) const;
};
#endif
