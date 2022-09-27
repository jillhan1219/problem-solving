#include<iostream>
#include<sstream>
#include<list>
#include<string>
#include "Polynomial.h"
#include "Polynomial.cpp"

using namespace std;

//¶¨Òåmainº¯Êý
int main() 
{		
   bool exercise1=false;
    if(exercise1)    {
    //第一关执行代码
    string str;          
    getline(cin,str);    
   
    }   else     {
    //第二关执行代码
    Polynomial beDiv;
    Polynomial di;
    if((!beDiv.getPoly())||(!di.getPoly())){
        cout<<"error";
        for(int i=0;i<3;++i){
            cout<<"\n"<<"error";
        }
        return 0;
    }
    
    ostringstream convert;
    beDiv.mySort();
    beDiv.simplify();
    beDiv.printPoly(convert);
    convert<<"\n";
    //cout<<convert.str();
    di.mySort();
    di.simplify();
    auto it=di.begin();
    if((*it).coef==0){
        cout<<"error";
        for(int i=0;i<3;++i){
            cout<<"\n"<<"error";
        }
        return 0;
    }
    di.printPoly(convert);
    convert<<"\n";
    //cout<<convert.str();
    auto res=div(beDiv,di);
    Polynomial ans=res.first;
    Polynomial rem=res.second;
    
    ans.printPoly(convert);
    convert<<"\n";
    rem.printPoly(convert);
    cout<<convert.str();
    }
    
    
	/********** End **********/
  	return 0;
}