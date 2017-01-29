#include"TextQuery.h"
#include"QueryResult.h"
#include<sstream>
//#include"StrVec.h"
//constructor
TextQuery::TextQuery(ifstream &is):file(make_shared<StrVec>())
{
	string text;
	while(getline(is,text))
	{
		file->push_back(text);
		int n=file->size()-1;//maching-friendly for index of the file
		istringstream line(text);
		string word;
		while(line>>word)
		{	
			word=cleanup_str(word);
			auto &lines=word_map[word];
			if(!lines)//it's null_ptr when we first creat it
				lines.reset(new set<line_no>);
			lines->insert(n);
		}
	}
}

string TextQuery::cleanup_str(const string& s)
{
	string ret;
	for(auto iter=s.begin();iter!=s.end();++iter)
	{
		if(!ispunct(*iter))//if ispunct() true, skip that punctuation character
			ret+=tolower(*iter);//make it case insensitive
	}
	return ret;
}

QueryResult TextQuery:: query(const string &sought) const
{
	static shared_ptr<set<line_no>> nodata(new set<line_no>);//local static dealing with no search result
	auto map_it=word_map.find(sought);
	if(map_it!=word_map.cend())
		return QueryResult(sought,map_it->second,file);
	else
		return QueryResult(sought,nodata,file);//not found
}

ostream &print(ostream &os,const QueryResult &qr)
{
	os<<qr.sought<<" occurs "<<qr.lines->size()<<" times."<<endl;//qr.lines is a shared_ptr so use -> to fetch menber function size()
	if(qr.lines->size())
	{
		for(auto num:*qr.lines)
			os<<"\t lines: "<<(num+1)<<" "<<(*qr.file)[num]<<endl;
	}
	else
		os<<"\t not in the text."<<endl;
	return os;
}
