#ifndef DERIVED_QUERY_H
#define	DERIVED_QUERY_H

#include"Query.h"

class WordQuery:public Query_base
{
friend class Query;
WordQuery(const string& s):query_word(s) {}

QueryResult eval(const TextQuery& t ) const
{return t.query(query_word);}

string rep() const {return query_word;}

string query_word;
};


class NotQuery:public Query_base
{
friend Query operator ~(const Query&);

NotQuery(const Query& q):query(q) {}

string rep() const {return "~("+query.rep()+")";}

QueryResult eval(const TextQuery& ) const;

Query query;
};
inline Query operator~ (const Query& operand)
{ return shared_ptr<Query_base>(new NotQuery(operand));}

class AndQuery:public BinaryQuery
{
friend Query operator &(const Query&,const Query&);

AndQuery(const Query& lhs,const Query& rhs):BinaryQuery(lhs,rhs,"&") {}

QueryResult eval(const TextQuery&) const;
};

inline Query operator &(const Query& lhs,const Query& rhs)
{return shared_ptr<Query_base>(new AndQuery(lhs,rhs));}

class OrQuery:public BinaryQuery
{
friend Query operator |(const Query&, const Query&);

OrQuery(const Query& lhs,const Query & rhs):BinaryQuery(lhs,rhs,"|") {}

QueryResult eval(const TextQuery&) const;
};

inline Query operator |(const Query& lhs,const Query& rhs)
{return shared_ptr<Query_base>(new OrQuery(lhs,rhs));}


#endif
