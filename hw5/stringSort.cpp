#include <algorithm>
#include <set>
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include<algorithm>
using namespace std;

struct Cmp
{
    bool operator()(string const& tmp_a,string const& tmp_b)const
    {
        if(tmp_a==tmp_b)
            return false;
        string a=tmp_a;
        string b=tmp_b;
        transform(a.begin(),a.end(),a.begin(),::toupper);
        transform(b.begin(),b.end(),b.begin(),::toupper);
        return a>=b;
    }
};


int main()
{
    /********** Begin **********/
    //读取测试输入
    set<string> ruleA;
    set<string,Cmp> ruleB;
    string input;
    while(getline(cin,input))
    {
        ruleA.insert(input);
        ruleB.insert(input);
    }

    //请打印输出结果
    cout<<"rule a:";
    for(auto& it:ruleA)
    {
        cout<<"\n"<<it;
    }

    cout<<"\n";

    cout<<"rule b:";
    for(auto& it:ruleB)
    {
        cout<<"\n"<<it;
    }

	/********** End **********/
  	return 0;
}