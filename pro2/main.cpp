#include"PolynomialRegression.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>

using namespace std;

double results(vector<double>& coffes,int& order,int& x)
{
    int i=1;
    double result=0;
    for(int j=0;j<=order;++j)
    {
        result+=coffes[j]*i;
        i*=x;
    }
    return result;
}

int main()
{
    vector<double> data;
    vector<double> max_temp;
    vector<double> min_temp;

    ifstream ifs;
    ifs.open("data.txt",ios::in);
    if(!ifs.is_open())
    {
        cout<<"fail"<<endl;
        return 0;
    }

    string input;

    vector<double> date;
    double index=0;

    while(getline(ifs,input))
    {
        int pos=input.find(" ");
        istringstream iss(input.substr(pos+1));
        int maxT,minT;
        iss>>maxT>>minT;
        date.push_back(index++);
        max_temp.push_back(maxT);
        min_temp.push_back(minT);
    }

    int order;
    cin>>order;

    vector<double> coeffs_max;
    vector<double> coeffs_min;
    PolynomialRegression<double> predict_max;
    PolynomialRegression<double> predict_min;
    predict_max.fitIt(date,max_temp,order,coeffs_max);
    predict_min.fitIt(date,min_temp,order,coeffs_min);

    ofstream ofs;
    ofs.open("output.txt",ios::app);
    ofs<<order<<endl;

    for(int i=59;i<=66;++i)
    {
        ofs<<i<<" ";
        double tmax=results(coeffs_max,order,i);
        double tmin=results(coeffs_min,order,i);
        ofs<<tmax<<" "<<tmin<<endl;
    }
    for(int i=-3;i<=-1;++i)
    {
        ofs<<i<<" ";
        double tmax=results(coeffs_max,order,i);
        double tmin=results(coeffs_min,order,i);
        ofs<<tmax<<" "<<tmin<<endl;
    }

    ifs.close();
    ofs.close();
    return 0;
}