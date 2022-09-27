#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include<list>
#include<sstream>
using namespace std;

struct node{
    double coef;
    int exp;
};
class Polynomial
{
friend Polynomial sub(Polynomial &beSub,Polynomial &sub);
friend Polynomial mul(Polynomial &beMul,node &mul);
friend pair<Polynomial,Polynomial> div(Polynomial &beDi,Polynomial &di);

private:
    /* data */
    list<node> poly;

public:
    bool getPoly();
    void insertNode(node& tmp){
        poly.push_back(tmp);
    }
    void printPoly(ostringstream& convert);
    void mySort();
    void simplify();
    auto begin(){
        return poly.begin();
    }
    auto end(){
        return poly.end();
    }
    double calculation(double x);
};


#endif