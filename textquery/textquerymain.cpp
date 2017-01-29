
#include"TextQuery.h"
#include"TextQuery.cc"
//#include"StrVec.h"
#include<iostream>
#include<fstream>
#include"Query.h"
#include"Derived_Query.h"
#include"Query.cc"
#include<sstream>
using namespace std;
void runqueries(ifstream& input)
{
	TextQuery tq(input);
	while(true)
	{
		cout<<" tell the word you are looking for or q to quit"<<endl;
		string word;
		if(!(cin>>word)||word=="q") break;
		//print(cout,tq.query(word))<<endl;
	}
}

int main(int argc,char **argv)
{
	ifstream input;
	if(argc<2||!(input.open(argv[1]),input))
	{
 		cerr<<"no input file."<<endl;
		return -1;
	}
	runqueries(input);
	return 0;
}
