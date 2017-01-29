#include"Query.h"
#include"Derived_Query.h"
#include<iostream>
#include<algorithm>
#include"QueryResult.h"
class QueryResult;

ostream& operator <<(ostream& os,const Query &query)
{
	return os<<query.rep();
}

inline Query::Query(const string &s):q(new WordQuery(s)) {}

QueryResult OrQuery:: eval(const TextQuery& text) const
{
auto right=rhs.eval(text),left=lhs.eval(text);

auto ret_line=make_shared<set<line_no>>(left.begin(),left.end());

ret_line->insert(right.begin(),right.end());

return QueryResult(rep(),ret_line,left.get_file());
}



QueryResult AndQuery::eval(const TextQuery& text) const
{
auto right=rhs.eval(text),left=lhs.eval(text);

auto ret_line=make_shared<set<line_no>>();

set_intersection(right.begin(),right.end(),left.begin(),left.end(),inserter(*ret_line,ret_line->begin()));

return QueryResult(rep(),ret_line,left.get_file());
}


QueryResult NotQuery::eval(const TextQuery& text) const
{
auto result=query.eval(text);

auto ret_line=make_shared<set<line_no>>();

auto beg=result.begin(),end=result.end();

auto sz=result.get_file()->size();

for(size_t n=0;n!=sz;++n)
{
	if(beg==end || *beg!=n)
		ret_line->insert(n);
	else if(beg!=end)
		++beg;
}

return QueryResult(rep(),ret_line,result.get_file());
}
