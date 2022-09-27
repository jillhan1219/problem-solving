#include"MyClass1.h"
#include"MyClass1.cpp"
#include<iostream>
#include<sstream>
#include<string>
using namespace::std;

//请根据自己需求定义MyClass1和MyClass2
//定义main函数
int main()
{
    /********** Begin **********/
    //读取测试输入

    int inputLen;
    ostringstream convert;
    MyClass1 gau;
    inputLen=gau.getEquations();
    gau.pritnLegal(convert);
    gau.getMatrix();
    gau.solve(convert);
    gau.pritnIllegal(convert);
    string output=convert.str();
    int outputLen=output.length();

    //请打印输出运算结果

    cout<<inputLen<<":"<<outputLen<<endl;
    cout<<output;

	/********** End **********/
  	return 0;
}

