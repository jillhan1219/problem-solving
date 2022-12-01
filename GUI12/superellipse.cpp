#include"superellipse.h"
#include"std_lib_facilities.h"
#include<assert.h>
#include<vector>
#include<iostream>

#define PI acos(-1)

int sgn(double a)
{
    if(a==0) return 0;
    if(a<0) return -1;
    return 1;
}

superellipse::superellipse(double a,double b,double m,double n,double N)
    :a(a),b(b),m(m),n(n),N(N)
{
   //利用极坐标形式，即有N个点，取极坐标theta的间隔为2*PI/N
    vector<double> thetas;
    double gap=2*PI/N;
    double theta=0;
    for(int i=0;i<N;++i)
    {
        thetas.push_back(theta);
        theta+=gap;
    }
    
    for(int i=0;i<N;++i)
    {
        double tmp_x=pow(abs(cos(thetas[i])),2/m)*a*sgn(cos(thetas[i]));
        double tmp_y=pow(abs(sin(thetas[i])),2/n)*b*sgn(sin(thetas[i]));
        se_points.push_back(Point(tmp_x+300,tmp_y+200));
    }
    
}

void superellipse::getStar()
{
    for(int i=0;i<N;++i)
    {
        for(int j=i+1;j<N;++j)
        {
            //fl_line(se_points[i].x,se_points[i].y,se_points[j].x,se_points[j].y);
            star.add(se_points[i],se_points[j]);
        }
    }
}

void superellipse::draw_lines() const
{
    if(color().visibility())
        Shape::draw_lines();
}


