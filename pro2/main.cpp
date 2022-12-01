#include"PolynomialRegression.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>

using namespace std;

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

    vector<double> coeffs_max;
    vector<double> coeffs_min;
    PolynomialRegression<double> predict_max;
    PolynomialRegression<double> predict_min;
    predict_max.fitIt(date,max_temp,2,coeffs_max);
    predict_min.fitIt(date,min_temp,2,coeffs_min);

    for(int i=61;i<=66;++i)
    {
        double tmax=coeffs_max[2]*i*i+coeffs_max[1]*i+coeffs_max[0];
        double tmin=coeffs_min[2]*i*i+coeffs_min[1]*i+coeffs_min[0];
        cout<<tmax<<" "<<tmin<<endl;
    }

    //cout<<max_temp[60]<<min_temp [60]<<endl;
    //for(int i=0;i<n;++i)
    //{
        //x.push_back(i+1);
        //double temp;
        //cin>>temp;
        //y.push_back(temp);
    //}
    //vector<double> results;
    //PolynomialRegression<double> test;
    //test.fitIt(x,y,2,results);
    //for(auto& it:results)
    //cout<<it<<" ";
    //cout<<endl;
    return 0;
}