#include"MyClass1.h"
#include<map>
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<cmath>
#include<iomanip>
#include<ctype.h>
#include<unordered_set>
using namespace std;

double MyClass1::keep(double x)
{
    int flag=x>=0;
    if(flag) return floor(x * 10000.000f) / 10000.000f;
    else return -(floor(abs(x) * 10000.000f+0.1 ) / 10000.000f);
}

bool MyClass1::validEquation(string& line){
    int len=line.length();
    int i=0;
    unordered_set<string> seen;
    while(i<len){
        char ch=line[i];
        if(isdigit(ch)){
            int j=i+1;
            while (line[j]!='*')
            {
                if(isdigit(line[j])||line[j]=='.')
                    ++j;
                else return false;
            }
            string variable;
            if(islower(line[++j])) {variable+=line[j];}
            else return false;

            j++;
            int cnt=2;
            while(isdigit(line[j])){
                cnt--;
                variable+=line[j];
                ++j;
            }
            if(cnt<0) return false;
            i=j;
        }
        else if(islower(ch)){
            string variable;
            variable+=ch;
            int j=i+1;
            int cnt=2;
            while(isdigit(line[j])){
                cnt--;
                variable+=line[j];
                ++j;
            }
            if(cnt<0) return false;
            if(seen.count(variable)) return false;
            seen.insert(variable);
            i=j;
        }
        else if(ch=='-'||ch=='+') i++;
        else if(ch=='=') {
            int j=i+1;
            if(line[j]=='-') j++;
            while(j<len){
                if(isdigit(line[j])||line[j]=='.') ++j;
                else return false;
            }
            i=j;
        }
        else return false;
    }
    return true;
}

int MyClass1::getEquations(){
    string line;
    int inputLen=0;
    int cnt=0, cntV=0;
    while(getline(cin,line)){
        inputLen+=line.length();
        cnt++;
        if(!validEquation(line)){
            illegal.push_back(line);
            continue;
        }
        legal.push_back(line);
        istringstream ss(line);
        char ch;
        int i=0;
        int tmpLen=line.length();
        while(i<tmpLen){
            if(line[i]>='a'&&line[i]<='z'){
                string variable;
                while((line[i]>='a'&&line[i]<='z')||(line[i]>='0'&&line[i]<='9')){
                    variable+=line[i];
                    ss>>ch;
                    i++;
                }
                equations[variable].push_back({cntV,1.0});
                continue;
            }
            else if(line[i]>='0'&&line[i]<='9'){
                double coef;
                ss>>coef;
                while(line[i]!='*')
                    i++;
                i++;
                ss>>ch;
                string variable;
                while((line[i]>='a'&&line[i]<='z')||(line[i]>='0'&&line[i]<='9')){
                    variable+=line[i];
                    ss>>ch;
                    i++;
                }
                equations[variable].push_back({cntV,coef});
                continue;
            }
            else if(line[i]=='+'||line[i]=='-'){
                double coef;
                bool flag;
                if(line[i]=='+') flag=true;
                else flag=false;
                if(line[i+1]>='0'&&line[i+1]<='9'){
                    ss>>coef;
                    while(line[i]!='*'){//避免.死循环
                        i++;
                    }
                    i++;
                    ss>>ch;
                }
                else{
                    i++;
                    ss>>ch;
                    if(flag) coef=1.0;
                    else coef=-1.0;
                }
                string variable;
                while((line[i]>='a'&&line[i]<='z')||(line[i]>='0'&&line[i]<='9')){
                    variable+=line[i];
                    ss>>ch;
                    i++;
                }
                equations[variable].push_back({cntV,coef});
                continue;
            }
            else if(line[i]=='='){
                ss>>ch;
                double tmp;
                ss>>tmp;
                rhs.push_back(tmp);
                break;
            }
        }
        cntV++;
    }
    return inputLen+cnt-1;
}

void MyClass1::getMatrix(){
    variableNum=equations.size();
    matrix=new double*[variableNum];
    for(int i=0;i<variableNum;++i){
        matrix[i]=new double[variableNum+1];
        for(int j=0;j<variableNum+1;++j)
            matrix[i][j]=0;
    }
    int i=0;
    for(auto& var:equations){
        for(auto& equ:var.second){
            matrix[equ.first][i]=equ.second;
        }
        i++;
    }
    i=0;
    for(auto it:rhs){
        matrix[i++][variableNum]=it;
    }
}

void MyClass1::pritnLegal(ostringstream& convert){
    convert<<"Legal Equations:"<<"\n";
    for(auto& str:legal){
        convert<<str<<"\n";
    }
}
void MyClass1::pritnIllegal(ostringstream& convert){
    convert<<"Illegal Equations:";
    for(auto it=illegal.begin();it!=illegal.end();++it){
        convert<<"\n";
        convert<<*it;
    }
}

void MyClass1::solve(ostringstream& convert){
    int nwline=0;
    for(int k=0;k<variableNum;++k){
        int maxi=nwline;
        for(int i=nwline+1;i<variableNum;++i){
            if(abs(matrix[i][k])>abs(matrix[maxi][k]))
                maxi=i;
        }
        if(abs(matrix[maxi][k])<1e-9)
            continue;
        for(int j=0;j<variableNum+1;++j)
            swap(matrix[nwline][j],matrix[maxi][j]);
        for(int i=0;i<variableNum;++i){
            if(i==nwline)
                continue;
            double mul=matrix[i][k]/matrix[nwline][k];
            for(int j=k+1;j<variableNum+1;++j)
            matrix[i][j]-=matrix[nwline][j]*mul;
        }
        ++nwline;
    }
    try{
        if(nwline<variableNum){
            while(nwline<variableNum){
                if(matrix[nwline++][variableNum]!=0)
                    throw 1;
            }
            throw '2';
        }
        int i=0;
        for(auto& equ:equations){
            convert<<equ.first<<":";
            double tmp=matrix[i][variableNum]/matrix[i][i];
            convert<<fixed<<setprecision(4)<<keep(tmp)<<"\n";
            i++;
        }
    }
    catch(int e1){
        convert<<"error1"<<"\n";
    }
    catch(char e2){
        convert<<"error2"<<"\n";
    }
}