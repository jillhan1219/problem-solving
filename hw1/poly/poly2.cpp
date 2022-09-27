#include<iostream>
#include<sstream>
#include<list>
#include<string>
#include<iomanip>
#include "Polynomial.h"
#include "Polynomial.cpp"

using namespace std;

int main(){
    Polynomial poly;
    if(!poly.getPoly()){
        cout<<"error";
        return 0;
    }
    poly.mySort();
    poly.simplify();
    double ans;
    double x;
    cin>>x;
    ans=poly.calculation(x);
    cout<<fixed<<setprecision(4)<<keep(ans);
    return 0;
}