#ifndef TEXT_QUERY_H
#define TEXT_QUERY_H
#include<unordered_map>
#include<unordered_set>
#include<memory>
#include<fstream>
#include<vector>
#include<iostream>
#include"QueryResult.h"
//#include"StrVec.h"
using namespace std;
class QueryResult;
//class StrVec;
class TextQuery
{
public:
	using line_no=size_t;
	using StrVec=vector<string>;
	TextQuery(ifstream&);
	QueryResult query(const string &) const;
private:
	shared_ptr<StrVec> file;
	unordered_map<string,shared_ptr<unordered_set<line_no>>> word_map;
	string cleanup_str(const string&);
};
#endif
