#ifndef QUERY_H
#define QUERY_H

#include"TextQuery.h"

#include"QueryResult.h"
#include<string>
#include<memory>

class Query_base
{
friend class Query;
protected:
	using line_no=TextQuery::line_no;
	virtual ~Query_base()=default;
private:
	virtual QueryResult eval(const TextQuery &) const=0;
	virtual string rep() const=0;
};

class Query
{
friend Query operator ~(const Query &);
friend Query operator |(const Query &,const Query &);
friend Query operator &(const Query &,const Query &);
public:
	Query(const string&);//build WordQUery
	QueryResult eval(const TextQuery& t) const {return q->eval(t);}
	string rep() const {return q->rep();}
private:
	//private constructor, no intend to be used by users
	Query(shared_ptr<Query_base> query):q(query) {}
	shared_ptr<Query_base> q;
};

class BinaryQuery:public Query_base
{
protected:
	BinaryQuery(const Query& l,const Query &r,string s):lhs(l),rhs(r),opSym(s) {}
	string rep() const {return "("+lhs.rep()+" "+opSym+" "+rhs.rep()+")";}
	
	Query lhs,rhs;
	string opSym;

};

#endif
