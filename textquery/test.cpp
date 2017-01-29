#include"TextQuery.h"
#include"TextQuery.cc"
#include<iostream>
#include<fstream>
#include"Query.h"
#include"Derived_Query.h"
#include"Query.cc"
#include<sstream>
using namespace std;

int main()
{

ifstream input("storyDataFile");

TextQuery text(input);

Query q1("daddy");
const auto r1=q1.eval(text);
Query q3=~q1;
const auto r3=q3.eval(text);
cout<<q1<<endl;
print(cout,r1);
cout<<q3<<endl;
print(cout,r3);
Query q2=Query("her")&Query("bird")|Query("wind");
const auto r2=q2.eval(text);
cout<<q2<<endl;
print(cout,r2);
Query q4=Query("her")&Query("bird");
const auto r4=q4.eval(text);
print(cout,r4);

return 0;
}
