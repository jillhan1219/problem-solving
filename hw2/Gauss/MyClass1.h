#ifndef MYCLASS1_H
#define MYCLASS1_H

#include<map>
#include<sstream>
#include<string>
#include<vector>
using namespace std;

class MyClass1{
private:
    map<string,vector<pair<int,double>>> equations;
    double** matrix;
    int variableNum;
    vector<string> legal;
    vector<string> illegal;
    vector<double> rhs;
    double keep(double x);
public:
    int getEquations();
    bool validEquation(string& line);
    void getMatrix();
    void pritnLegal(ostringstream& convert);
    void solve(ostringstream& convert);
    void pritnIllegal(ostringstream& convert);
};
#endif