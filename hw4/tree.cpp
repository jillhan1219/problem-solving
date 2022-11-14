#include"std_lib_facilities.h"
#include"tree.h"
using namespace std;

int main()
{
    string input1,input2;
    string input;
    char ch;
    while((ch=cin.get())!=EOF)
        input.push_back(ch);
    istringstream is;
    is.str(input);
    is>>input1;
    is>>input2;
    ostringstream convert;
    
    Tree t1=Tree(input1);
    Tree t2=Tree(input2);

    bool flag1=t1.isValid();
    bool flag2=t2.isValid();

    if(flag1&&flag2)
    {
        t1.buildTree();
        t2.buildTree();
        string code1=t1.getCode();
        string code2=t2.getCode();
        if(code1.compare(code2)==0)
            convert<<input1<<" and "<<input2<<" are isomorphic";
        else
            convert<<input1<<" and "<<input2<<" are non-isomorphic";
    }
    else
    {
        convert<<"invalid tree(s):";
        if(!flag1)
            convert<<" "<<input1;
        if(!flag2)
            convert<<" "<<input2;
    }

    string output=convert.str();
    cout<<(input.length()-1)<<":"<<output.length()<<"\n";
    cout<<output;
    return 0;

}