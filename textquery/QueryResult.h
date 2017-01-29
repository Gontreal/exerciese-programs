#ifndef QUERY_RESULT_H
#define QUERY_RESULT_H
#include<iostream>
#include<map>
#include<set>
#include<memory>
#include<vector>
#include"TextQuery.h"
//#include"StrVec.h"
using namespace std;
//class StrVec;
class QueryResult
{
friend ostream& print(ostream&,const QueryResult &);

public:
	using line_no=size_t;
	using StrVec=vector<string>;
	QueryResult(string s,shared_ptr<set<line_no>> lines, shared_ptr<StrVec> file):
	sought(s),file(file),lines(lines) {}
	//return iter for the set
	set<line_no>::const_iterator begin() const {return lines->cbegin();}
	set<line_no>::const_iterator end() const {return lines->cend();}
	shared_ptr<StrVec> get_file() const {return file;}
private:
	string sought;
	shared_ptr<StrVec> file;
	shared_ptr<set<line_no>> lines;
};

#endif
