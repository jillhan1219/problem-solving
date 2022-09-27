#include "Polynomial.h"
#include<list>
#include<iostream>
#include<sstream>
#include<algorithm>
#include<string>
#include<iomanip>
#include<cmath>
#include<vector>

using namespace std;

bool Polynomial::getPoly(){
   string str;
    getline(cin,str);
    istringstream ss(str);
    int ex=-1;
    double co=-1;
    int len=str.length(),i=0;
    char ch;
    if(str[i]>='0'&&str[i]<='9'){
        ss>>co;
        while(str[i]=='.'||(str[i]>='0'&&str[i]<='9'))
            i++;
        ex=0;
        if(str[i]=='x'){
            ss>>ch;
            ex=1;
            i++;
        }
    }
    else if(str[i]=='x'){
        co=1;
        ex=1;
        ss>>ch;
        i++;
    }
    if(str[i]=='^'){
        ss>>ch;
        ss>>ex;
        i+=2;
    }
    if(co!=-1&&ex!=-1){
        node tmp={co,ex};
        insertNode(tmp);
    }
    while(i<len){
        ex=1;
        switch (str[i])
        {
        case 'x':
            co=1.0;
            i++;
            ss>>ch;
            break;
        case '+':
            if(str[++i]=='x'){
                co=1.0;
                i++;
                ss>>ch;
                ss>>ch;
            }
            else{
                ss>>co;
                while(str[i]=='.'||(str[i]>='0'&&str[i]<='9'))
                    i++;
                if(str[i]=='x'){
                    i++;
                    ss>>ch;
                }
                else
                    ex=0;
            }
            break;
        case '-':
            if(str[++i]=='x'){
                co=-1.0;
                i++;
                ss>>ch;
                ss>>ch;
            }
            else{
                ss>>co;
                while(str[i]=='.'||(str[i]>='0'&&str[i]<='9'))
                    i++;
                if(str[i]=='x'){
                    i++;
                    ss>>ch;
                }
                else
                    ex=0;
            }
            break;
        case '^':
            break;
        default:
            return false;
        }
        if(str[i]=='^'){
            ss>>ch;
            ss>>ex;
            i+=2;
        }
        node tmp={co,ex};
        insertNode(tmp);
    }
    return true;
}

bool cmp(node& a,node& b){
    return a.exp>b.exp;
}
void Polynomial::mySort(){
    poly.sort(cmp);
}

void Polynomial::simplify(){
    auto it2=++poly.begin();
    auto it=poly.begin();
    while(it2!=poly.end()){
        if((*it).exp==(*it2).exp){
            (*it).coef+=(*it2).coef;
            it2=poly.erase(it2);
        }
        else{
            it2++;
            it++;
        }
    }
}

double keep(double x)
{
    int flag=x>=0;
    if(flag) return floor(x * 10000.000f) / 10000.000f;
    else return -(floor(abs(x) * 10000.000f+0.1 ) / 10000.000f);
}
void Polynomial::printPoly(ostringstream& convert){
    auto it=poly.begin();
    if(it==poly.end()){
        convert<<fixed<<setprecision(4)<<0.0000;
        return;
    }
    for(;it!=poly.end();++it){
        if((*it).coef>0&&(it!=poly.begin())){
            convert<<'+';
        }
        convert<<fixed<<setprecision(4)<<keep((*it).coef);
        if((*it).exp>0){
            convert<<'x';
            if((*it).exp>1){
                convert<<'^'<<(*it).exp;
            }
        }
    }
}

Polynomial sub(Polynomial& beSub,Polynomial& sub){
    Polynomial ans;
    node tmp;
    auto it1=beSub.poly.begin();
    auto it2=sub.poly.begin();
    while(it1!=beSub.poly.end()&&it2!=sub.poly.end()){
        if((*it2).exp==(*it1).exp){
            tmp.coef=(*it1).coef-(*it2).coef;
            tmp.exp=(*it1).exp;
            if(tmp.coef!=0){
                ans.insertNode(tmp);
            }
            it1++;
            it2++;
        }
        else if((*it2).exp>(*it1).exp){
            tmp.coef=-(*it2).coef;
            tmp.exp=(*it2).exp;
            ans.insertNode(tmp);
            it2++;
        }
    }
    if(it1!=beSub.end()){
        while(it1!=beSub.end()){
            node temp=*it1;
            ans.insertNode(temp);
            it1++;
        }
    }
    if(it2!=sub.end()){
        while(it2!=sub.end()){
            node temp;
            temp.coef=-(*it2).coef;
            temp.exp=-(*it2).exp;
            ans.insertNode(temp);
            it2++;
        }
    }
    return ans;
}
Polynomial mul(Polynomial &bemul,node &mul){
    Polynomial ans;
    for(auto it=bemul.poly.begin();it!=bemul.poly.end();++it){
        node tmp;
        tmp.coef=(*it).coef*mul.coef;
        tmp.exp=(*it).exp+mul.exp;
        ans.insertNode(tmp);
    }
    return ans;
}
pair<Polynomial,Polynomial> div(Polynomial& bedi,Polynomial& di){
    Polynomial ans;//商
    Polynomial rem;//余数
    node mu;//乘数
    Polynomial d;//除数
    rem=bedi;
    auto it1=rem.begin();
    auto it2=di.begin();
    while ((it1!=rem.end())&&((*it1).exp>=(*it2).exp))
    {
        /* code */
        mu.exp=(*it1).exp-(*it2).exp;
        mu.coef=(*it1).coef/((*it2).coef);
        ans.insertNode(mu);
        d=mul(di,mu);
        rem=sub(rem,d);
        it1=rem.begin();
    }
    return make_pair(ans,rem);
}

double Polynomial::calculation(double x){
    auto it=poly.begin();
    int expMax=(*it).exp;
    double tmp=1;
    vector<double> pow;
    while(expMax-->=0){
        pow.push_back(tmp);
        tmp*=x;
    }
    double ans=0;
    for(auto& item:poly){
        ans+=item.coef*pow[item.exp];
    }
    return ans;
}